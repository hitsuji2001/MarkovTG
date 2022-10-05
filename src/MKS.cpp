#include "../header/MKS.hpp"

namespace markov {
  std::string MKS_Trim(const std::string& input) {
    std::string result = MKS_Ltrim(input);
    result = MKS_Rtrim(result);
    return result;
  }

  std::string MKS_Rtrim(const std::string& input) {
    std::string result = "";
    for (int i = input.length() - 1; i >= 0; i--) {
      if (std::isspace(input.at(i))) continue;
      else {
	result = input.substr(0, i + 1);
	break;
      }
    }

    return result;
  }

  std::string MKS_Ltrim(const std::string& input) {
    std::string result = "";
    for (size_t i = 0; i < input.length(); ++i) {
      if (std::isspace(input.at(i))) continue;
      else {
	result = input.substr(i);
	break;
      }
    }

    return result;
  }

  std::string MKS_Substitute(const std::string& input, const std::string& delim, const std::string& replace) {
    std::string result = "";

    for (size_t i = 0; i < input.length(); ++i) {
      bool exist = false;
      for (size_t j = 0; j < delim.length(); ++j) {
	if (delim.at(j) == input.at(i)) {
	  exist = true;
	  break;
	} else continue;
      }
      if (exist) result += replace;
      else result += input.at(i);
    }

    return result;
  }

  std::string MKS_SplitWordByDelim(const std::string& input, const char delim, size_t count) {
    std::string result = "";
    size_t c = 0;

    for (size_t i = 0; i < input.length(); ++i) {
      if (input.at(i) == delim) {
	result += delim;
	c++;
      }
      else if (input.at(i) != delim) result += input.at(i);
      if (c == count) break;
    }

    return MKS_Trim(result);
  }

  std::string MKS_CutLeftByDelim(const std::string& input, const char delim, size_t count) {
    std::string result = "";
    size_t c = 0;

    for (size_t i = 0; i < input.length(); ++i) {
      if (input.at(i) != delim) continue;
      else if (input.at(i) == delim) c++;
      if (c == count) {
	result = input.substr(i);
	break;
      }
    }

    return MKS_Trim(result);
  }

  std::string MKS_ToLowercase(const std::string& input) {
    std::string result = "";
    for (size_t i = 0; i < input.length(); ++i) {
      result += std::tolower(input.at(i));
    }

    return result;
  }
}
