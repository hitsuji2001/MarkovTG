#ifndef __MARKOV_STRING_MANIPULATION__
#define __MARKOV_STRING_MANIPULATION__

#include <string>

namespace markov {
  std::string MKS_Substitute(const std::string& input, const std::string& delim, const std::string& replace);
  std::string MKS_ToLowercase(const std::string& input);
  std::string MKS_Trim(const std::string& input);
  std::string MKS_Ltrim(const std::string& input);
  std::string MKS_Rtrim(const std::string& input);
  std::string MKS_SplitWordByDelim(const std::string& input, const char delim, size_t count);
  std::string MKS_CutLeftByDelim(const std::string& input, const char delim, size_t count);
}

#endif // __MARKOV_STRING_MANIPULATION__
