#include <iostream>

#include "./MarkovTextGen.hpp"

int main() {
  srand(time(NULL));

  markov::MarkovTextGen generator = markov::MarkovTextGen();
  generator.SetContextSize(6);
  generator.SlurpAllFileFromFolder("./training-text/vietnamese");
  
  std::cout << generator.GenerateText(100) << std::endl;

  return 0;
}
