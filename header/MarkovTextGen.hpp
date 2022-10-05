#ifndef __MARKOV_TEXT_GENREATOR__
#define __MARKOV_TEXT_GENREATOR__

#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <ctime>

#include <unordered_map>
#include <fstream>

#include "./MKS.hpp"

namespace markov {
  struct MarkovModel {
    std::unordered_map <std::string, std::unordered_map<std::string, float>> state;
  };

  class MarkovTextGen {
  public:
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
