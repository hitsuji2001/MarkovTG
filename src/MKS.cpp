#include "../header/MKS.hpp"

namespace markov {
  void MKS_Trim(std::string& input) {
    MKS_Ltrim(input);
    MKS_Rtrim(input);
  }

  void MKS_Rtrim(std::string& input) {
    int i;
    for (i = input.length() - 1; i >= 0; i--)
      if (!std::isspace(input.at(i))) break;
    input = input.substr(0, i + 1);
  }

  void MKS_Ltrim(std::string& input) {
    size_t i;
    for (i = 0; i < input.length(); ++i) 
      if (!std::isspace(input.at(i))) break;
    input = input.substr(i);
  }

  void MKS_Substitute(std::string& input, const std::string& delim, const std::string& replace) {
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
    input = result;
  }

  std::vector<std::string> MKS_SplitWordByDelim(std::string& input, const char delim, size_t count) {
    std::vector<std::string> result;
    std::string string;
    size_t index;

    if (count > 0) {
      size_t c = 0;
      for (index = 0; index < input.length(); ++index) {
	if (input.at(index) == delim) {
	  string += delim;
	  c++;
	}
	else if (input.at(index) != delim) string += input.at(index);
	if (c == count) break;
      }
      input = input.substr(index);
      MKS_Trim(string);
      MKS_Trim(input);
      result.push_back(string);
    } else if (count == 0) {
      for (index = 0; index < input.length(); ++index) {
	if (input.at(index) == delim) {
	  result.push_back(string);
	  string = "";
	} else string += input.at(index);
      }
      if (!string.empty()) result.push_back(string);
    }

    return result;
  }

  void MKS_ToLowercase(std::string& input) {
    for (size_t i = 0; i < input.length(); ++i)
      input.at(i) = std::tolower(input.at(i));
  }

  bool MKS_EndsWith(const std::string& input, const std::string& suffix) {
    if (input.length() >= suffix.length()) 
      return input.compare(input.length() - suffix.length(), suffix.length(), suffix) == 0;

    return false;
  }
}
