/*
 * Analyzer.cpp
 *
 * Class implementation of the Decklist Analyzer.
 *
 * Bryant Pong
 * 7/2/20 
 */
#include "Analyzer.h"

#include <sys/types.h>
#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <string>

bool Analyzer::BuildCardMap() {
  bool success = true;

  // Reset card information
  cardCount_.clear();

  // Attempt to open the directory of decklists
  DIR *pDir = opendir(dir_.c_str());
  if (pDir != NULL) {
    // Successfully opened directory.  Begin processing decklists.
    struct dirent *pDirent;
    while ((pDirent = readdir(pDir)) != NULL) {
      // Only process text files:
      if (std::string(pDirent->d_name).find(".txt") != std::string::npos) {
        ++numDecklists_;

        // Open decklist
        const std::string FULL_DECKLIST_PATH(dir_ + "/" + std::string(pDirent->d_name));
        std::cout << "Processing decklist: " << FULL_DECKLIST_PATH << std::endl;
        std::ifstream next_deck(FULL_DECKLIST_PATH);
        if (next_deck.is_open()) {
          // Process next entry in decklist
          std::string next_entry;
          while (getline(next_deck, next_entry)) {
            std::cout << "Next entry is: " << next_entry << std::endl;

            /*
             * Card entries are of the form <Number of Copies> <Name of Card>.
             * We need to extract the number of copies from the line, which is
             * all the text before the first space.
             */
            const size_t FIRST_SPACE = next_entry.find(" "); 
            // Ensure a space is found; otherwise invalid entry
            if (FIRST_SPACE != std::string::npos) {
              // Extract number of copies and card name
              const std::string NUM_COPIES(next_entry.substr(0, FIRST_SPACE));
              const std::string CARD_NAME(next_entry.substr(FIRST_SPACE + 1, next_entry.size() - FIRST_SPACE));
              std::cout << "Number of copies: " << NUM_COPIES << std::endl; 
              std::cout << "Card name: " << CARD_NAME << std::endl;

              // Add information to map
              Analyzer::CardMap::iterator findItr = cardCount_.find(CARD_NAME);
              if (findItr == cardCount_.end()) {
                // Card doesn't exist; add a new entry
                cardCount_.insert(std::make_pair(CARD_NAME, atoi(NUM_COPIES.c_str())));
              } else {
                // Entry exists.  Add new copies.
                findItr->second += atoi(NUM_COPIES.c_str());
              }
            }
          }      

          next_deck.close();
        } else {
          std::cerr << "WARNING: Could not open decklist: " << FULL_DECKLIST_PATH << std::endl;
        }
      } 
    } 
  } else {
    // ERROR: Could not open directory of decklists
    std::cerr << "ERROR: Could not open directory " << dir_ << " because of error: " << strerror(errno) << std::endl;
    success = false;
  }

  return success;
}
