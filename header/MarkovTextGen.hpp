#ifndef __MARKOV_TEXT_GENREATOR__
#define __MARKOV_TEXT_GENREATOR__

#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <ctime>

#include <fstream>
#include <filesystem>
#include <unordered_map>

#include "./MKS.hpp"

namespace markov {
  struct MarkovModel {
    std::unordered_map <std::string, std::unordered_map<std::string, float>> state;
  };

  class MarkovTextGen {
  public:
    void SlurpAllFileFromFolder(const std::string& folderPath);
    void FeedTextFromFile(const std::string& filePath);
    const std::string GenerateText(size_t wordsLimit);
    
    int GetContextSize();
    MarkovModel& GetMarkovModel();

    void SetContextSize(size_t value);

    MarkovTextGen();
    ~MarkovTextGen();

  private:
    void PrepareModel();
    std::string WalkthroughModel(const std::string& start);

    const std::string GetWeightedRandomNumber(const std::unordered_map<std::string, float>& map);

    float CalculateSumOfValues(const std::unordered_map<std::string, float>& map);
    std::string CleanText(const std::string& text);
    void ProcessLine(std::string& line);
    void LogModel();

  private:
    int         a_ContextSize;
    MarkovModel m_Model;
    std::string m_UselessCharacters;
  };
}

#endif // __MARKOV_TEXT_GENREATOR__
