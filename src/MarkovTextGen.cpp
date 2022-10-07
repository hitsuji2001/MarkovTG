#include "./MarkovTextGen.hpp"

// TODO: Cache the input into some sort of file
// TODO: Maybe try to reading different file type
// TODO: Fix others todo

namespace markov {
  MarkovTextGen::MarkovTextGen() {
    this->m_UselessCharacters = "[,.\"'!@#$%^&*(){}?/;`~:<>+=_-\\|";
    this->a_ContextSize = 2;
  }

  MarkovTextGen::~MarkovTextGen() {
  }

  void MarkovTextGen::SlurpAllFileFromFolder(const std::string& folderPath) {
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
      if (MKS_EndsWith(entry.path(), ".txt")) this->FeedTextFromFile(entry.path());
    }
  }

  void MarkovTextGen::FeedTextFromFile(const std::string& filePath) {
    std::ifstream fileContents(filePath);
    std::string line;

    if (!fileContents) {
      std::cerr << "[ERROR]: Could not read file `" << filePath << "` " << std::endl;
      std::cerr << "         " << std::strerror(errno) << std::endl;
      exit(1);
    }

    while (std::getline(fileContents, line)) {
      line = this->CleanText(line);
      if (!line.empty()) this->ProcessLine(line);
    }

    fileContents.close();
  }

  void MarkovTextGen::PrepareModel() {
    for(auto i = this->GetMarkovModel().state.begin(); i != this->GetMarkovModel().state.end(); i++) {
      float sum = this->CalculateSumOfValues(i->second);
      for (auto j = i->second.begin(); j != i->second.end(); j++) j->second /= sum;
    }
  }

  std::string MarkovTextGen::WalkthroughModel(const std::string& start) {
    std::string result = "";
    auto iter = this->GetMarkovModel().state.find(start);
    if (iter == this->GetMarkovModel().state.end()) {
      // TODO: Fix this problem, this is not suppose to happend
      auto random_iter = std::next(std::begin(this->GetMarkovModel().state), rand() % this->GetMarkovModel().state.size());
      result = random_iter->first;
    } else {
      // TODO: implement weighted random number generator for this
      //       to properly be a Markov Chain Model
      result = this->GetWeightedRandomNumber(iter->second);
      if (result.empty()) {
	std::cerr << "[ERROR]: Unreachable. Could not random text" << std::endl;
	exit(1);
      }
    }

    return result;
  }

  const std::string MarkovTextGen::GetWeightedRandomNumber(const std::unordered_map<std::string, float>& map) {
    int scaler = 100;
    int sumOfWeight = scaler;
    int random = rand() % (int)sumOfWeight;

    for (auto i = map.begin(); i != map.end(); ++i) {
      if (random < i->second * scaler) return i->first;
      random -= i->second * scaler;
    }

    return "";
  }

  
  float MarkovTextGen::CalculateSumOfValues(const std::unordered_map<std::string, float>& map) {
    float res = 0.0f;
    for(auto i = map.begin(); i != map.end(); i++) 
      res += i->second;
    return res;
  }

  void MarkovTextGen::ProcessLine(std::string& line) {
    std::string key;
    std::string nextWord;

    while(!line.empty()) {
      key = MKS_SplitWordByDelim(line, ' ', this->GetContextSize()).at(0);
      if (line.empty()) break;
      nextWord = MKS_SplitWordByDelim(line, ' ', this->GetContextSize()).at(0);
      if (line.empty()) break;

      if (this->GetMarkovModel().state.count(key) == 0) {
	this->GetMarkovModel().state[key].insert(std::make_pair(nextWord, 1.0f));
      } else {
        auto pos = this->GetMarkovModel().state.find(key);
	if (pos == this->GetMarkovModel().state.end()) {
	  std::cerr << "[UNREACHABLE]" << std::endl;
	  std::cerr << "`" << key << "` Did not exist in the map" << std::endl;
	  exit(1);
	} else {
	  auto innerKey = pos->second.find(nextWord);
	  if (innerKey == pos->second.end()) pos->second.insert(std::make_pair(nextWord, 1.0f));
	  else innerKey->second++;
	}
      }
    }
  }

  void MarkovTextGen::LogModel() {
    for(auto i = this->GetMarkovModel().state.begin(); i != this->GetMarkovModel().state.end(); i++) {
      std::cout << "{\n";
      std::cout << "  Key: '" << i->first << "'\n" ;
      for (auto j = i->second.begin(); j != i->second.end(); j++) {
	std::cout << "  {\n";
	std::cout << "      Key: '" << j->first << "',\n";
	std::cout << "      Value: " << j->second << "\n";
	std::cout << "  },\n";
      }
      std::cout << "}\n";
      std::cout << "_________________________\n";
    }
  }

  std::string MarkovTextGen::CleanText(const std::string& text) {
    std::string result = text;
    MKS_Substitute(result, this->m_UselessCharacters, "");
    MKS_ToLowercase(result);
    MKS_Trim(result);
    
    return result;
  }

  const std::string MarkovTextGen::GenerateText(size_t wordsLimit) {
    std::string result = "";
    std::string buffer;
    size_t count = 0;

    auto random_iter = std::next(std::begin(this->GetMarkovModel().state), rand() % this->GetMarkovModel().state.size());
    buffer = random_iter->first;

    this->PrepareModel();
    while (count < wordsLimit) {
      result += buffer + " ";
      count += MKS_SplitWordByDelim(buffer, ' ').size();
      buffer = this->WalkthroughModel(buffer);
    }

    return result;
  }

  int MarkovTextGen::GetContextSize() {
    return this->a_ContextSize;
  }

  MarkovModel& MarkovTextGen::GetMarkovModel() {
    return this->m_Model;
  }

  void MarkovTextGen::SetContextSize(size_t value) {
    this->a_ContextSize = value;
  }
}
