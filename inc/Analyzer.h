#ifndef __analyzer_h_
#define __analyzer_h_
/*
 * Analyzer.h
 *
 * Class definition for an object to analyze decklists and compute deck statistics.
 *
 * Bryant Pong
 * 7/2/20
 */
#include <string>
#include <map>

class Comparator {
public:
  bool operator()(std::pair<std::string, int> elem1, std::pair<std::string, int> elem2) const {
     //return elem1.second > elem2.second;
    return true;
  }
};

class Analyzer {
public:
  // Card count information is stored as <card name, number of cards>
  typedef std::map<std::string, int> CardMap;  

  Analyzer(const std::string& dir) : dir_(dir),
                                     numDecklists_(0) {}

  /**
   * @brief Iterate through the directory specified by dir_ and parse out all decklists.  Build up the cardCount_ map with the number of instances of each card.
   * @return bool: true if successful; false otherwise. 
   */
  bool BuildCardMap(); 

  /**
   * @brief Get the most-played cards.  If no argument is specified, this will
   *        print all cards in the map.  If an argument is specified, this will
   *        print the specified number of most-played cards.
   * @param numCards: Number of most-played cards to display.
   * @return std::string: Formatted output.
   */
  std::string GetMostPlayedCards(const size_t numCards=0); 

  // Accessors
  inline std::string GetDirectory() const { return dir_; }
  inline int GetNumLists() const { return numDecklists_; }
  inline CardMap GetCards() const { return cardCount_; }
 
private:
  //! Directory containing decklists to analyze (full path)
  std::string dir_;

  //! Number of decklists found in dir_
  int numDecklists_;

  //! Card count information
  CardMap cardCount_; 
};
#endif
