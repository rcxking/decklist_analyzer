/*
 * main.cpp
 * 
 * Decklist analyzer runner.
 * 
 * Bryant Pong
 * 7/2/20
 */
#include <iostream>
#include <string>
#include "Analyzer.h" 

int main(int argc, char **argv) {
  // Ensure a directory containing the decklists exists
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <directory containing decklists>" << std::endl;
    return -1;
  } 

  // Create the Analyzer
  const std::string DIRECTORY(argv[1]);
  std::cout << "Looking at directory: " << DIRECTORY << std::endl;
  Analyzer analyzer(DIRECTORY);
  analyzer.BuildCardMap();

  std::cout << analyzer.GetMostPlayedCards() << std::endl;

 return 0;
}
