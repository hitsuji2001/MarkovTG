#ifndef __MARKOV_STRING_MANIPULATION__
#define __MARKOV_STRING_MANIPULATION__

#include <string>
#include <vector>

namespace markov {
  void MKS_Substitute(std::string& input, const std::string& delim, const std::string& replace);
  void MKS_ToLowercase(std::string& input);
  void MKS_Trim(std::string& input);
  void MKS_Ltrim(std::string& input);
  void MKS_Rtrim(std::string& input);
  std::vector<std::string> MKS_SplitWordByDelim(std::string& input, const char delim, size_t count = 0);
  
  bool MKS_EndsWith(const std::string& input, const std::string& suffix);
}

#endif // __MARKOV_STRING_MANIPULATION__
