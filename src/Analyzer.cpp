/*
 * Analyzer.cpp
 *
 * Class implementation of the Decklist Analyzer.
 *
 * Bryant Pong
 * 7/2/20 
 */
#include "Analyzer.h"

#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

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
        const std::string FULL_DECKLIST_PATH(dir_ + "/" +  std::string(pDirent->d_name));
        std::cout << "Processing decklist: " << FULL_DECKLIST_PATH << std::endl;
        std::ifstream next_deck(FULL_DECKLIST_PATH);
        if (next_deck.is_open()) {
          // Process next entry in decklist
          std::string next_entry;
          while (std::getline(next_deck, next_entry)) {
            if (next_entry.empty())
              continue;

            // Remove trailing carriage return (if it exists)
            const size_t LAST_CHARACTER_POS = next_entry.length() - 1;
            if (next_entry[LAST_CHARACTER_POS] == '\r') {
              next_entry.erase(LAST_CHARACTER_POS);
            }
            
            /*
             * Card entries are of the form <Number of Copies> <Name of Card>.
             * We need to extract the number of copies from the line, which is
             * all the text before the first space.
             */
            const size_t FIRST_SPACE = next_entry.find(" ");

            // Ensure a space is found; otherwise invalid entry
            if (FIRST_SPACE != std::string::npos) {
              // Extract number of copies and card name
              std::string temp = next_entry.substr(0, FIRST_SPACE);
              const int NUM_COPIES = atoi(next_entry.substr(0, FIRST_SPACE).c_str());
              const int NAME_LENGTH = next_entry.length() - FIRST_SPACE - 1;
              const std::string CARD_NAME = next_entry.substr(FIRST_SPACE + 1, NAME_LENGTH);

              // Add information to map
              Analyzer::CardMap::iterator findItr = cardCount_.find(CARD_NAME);
              if (findItr == cardCount_.end()) {
                // Card doesn't exist; add a new entry
                cardCount_.insert(std::make_pair(CARD_NAME, NUM_COPIES));
              } else {
                // Entry exists.  Add new copies.
                findItr->second += NUM_COPIES;
              }
            }
          }      

          next_deck.close();
        } else {
          std::cerr << "WARNING: Could not open decklist: " << FULL_DECKLIST_PATH << std::endl;
        }
      } 
    }
    closedir(pDir);
  } else {
    // ERROR: Could not open directory of decklists
    std::cerr << "ERROR: Could not open directory " << dir_ << " because of error: " << strerror(errno) << std::endl;
    success = false;
  }

  return success;
}

// Analyzer::GetMostPlayedCards()
std::string Analyzer::GetMostPlayedCards(const size_t numCards) {
  // Ensure cardCount_ is populated:
  if (cardCount_.empty()) {
    std::cerr << "ERROR: cardCount_ is empty.  Did you call BuildCardMap()?" << std::endl;
    return "";
  }

  std::string output("Most-Played Cards:\n");

  // Sort by number of occurrences
  typedef std::pair<std::string, int> CardPair;

  std::vector<CardPair> vec;
  std::copy(cardCount_.begin(), cardCount_.end(), std::back_inserter<std::vector<CardPair>>(vec));

  std::sort(vec.begin(), vec.end(), [](const CardPair &card1, const CardPair &card2) {
  if (card1.second != card2.second)
    return card1.second > card2.second;
  else {
    return card1.first < card2.first;
  }});

  const size_t NUM_CARDS_TO_DISPLAY = (numCards <= 0) ? vec.size() : numCards;

  for (size_t i = 0; i < NUM_CARDS_TO_DISPLAY; ++i) {
    output += (vec[i].first + ": " + std::to_string(vec[i].second) + "\n");
  }

  return output;
}
