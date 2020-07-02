/*
 * main.cpp
 * 
 * Decklist analyzer runner.
 * 
 * Bryant Pong
 * 7/2/20
 */
#include <iostream>

int main(int argc, char **argv) {
  // Ensure a directory containing the decklists exists
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <directory containing decklists>" << std::endl;
    return -1;
  } 

 return 0;
}
