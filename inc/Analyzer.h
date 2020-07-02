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

class Analyzer {
public:
  // Card count information is stored as <card name, number of cards>
  typedef std::map<std::string, size_t> CardMap;  

  Analyzer(const std::string& dir) : dir_(dir),
                                     numDecklists_(0) {}

  /**
   * @brief Iterate through the directory specified by dir_ and parse out all decklists.  Build up the cardCount_ map with the number of instances of each card.
   * @return bool: true if successful; false otherwise. 
   */
  bool BuildCardMap(); 

  // Accessors
  inline std::string GetDirectory() const { return dir_; }
  inline size_t GetNumLists() const { return numDecklists_; }
  inline CardMap GetCards() const { return cardCount_; }
    
private:
  //! Directory containing decklists to analyze (full path)
  std::string dir_;

  //! Number of decklists found in dir_
  size_t numDecklists_;

  //! Card count information
  CardMap cardCount_; 
};
#endif
