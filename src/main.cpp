#include <iostream>

#include "./MarkovTextGen.hpp"

int main() {
  // State, Transition Probaility 
  // In text generator
  // State = text
  // Transition Probaility = the next after it
  srand(time(NULL));

  markov::MarkovTextGen generator = markov::MarkovTextGen();
  generator.FeedTextFromFile("./training-text/more-training-text.txt");
  generator.FeedTextFromFile("./training-text/training-text.txt");

  std::cout << generator.GenerateText(100) << std::endl;

  return 0;
}
