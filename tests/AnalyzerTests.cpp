/*
 * AnalyzerTests.cpp
 * 
 * Unit tests for the Analyzer class (defined in Analyzer.h/Analyzer.cpp).
 *
 * Bryant Pong
 * 7/2/20
 */
// Have Catch provide its own main
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <string>

#include "Analyzer.h"

// Analyzer class Construction tests
SCENARIO("An Analyzer object is to be created", "[Analyzer]") {
  GIVEN("A directory is provided to the Analyzer") {
    const std::string DIRECTORY("sample_dir");
    THEN("The Analyzer should be constructed without errors") {
      REQUIRE_NOTHROW(Analyzer(DIRECTORY));
    }
  } 
  GIVEN("A directory is provided to the Analyzer") {
    const std::string DIRECTORY("sample_dir");
    Analyzer analyzer(DIRECTORY);
    THEN("The Analyzer's member variables are initialized correctly") {
      REQUIRE(analyzer.GetDirectory() == DIRECTORY);
      REQUIRE(analyzer.GetNumLists() == 0);
      REQUIRE(analyzer.GetCards().size() == 0);
    }
  }
}

// Analyzer functional tests
SCENARIO("An Analyzer object is to be used", "[Analyzer]") {
  GIVEN("An Analyzer object and a non-existent directory") {
    const std::string DOES_NOT_EXIST("does_not_exist");
    Analyzer analyzer(DOES_NOT_EXIST);
    WHEN("The Analyzer attempts to examine this directory") {
      const bool RES = analyzer.BuildCardMap();
      THEN("The Analyzer fails") {
        REQUIRE(RES == false);
      }
    }
  }
  GIVEN("An Analyzer object and an empty directory") {
    const std::string EMPTY_DIR("empty_dir");
    Analyzer analyzer(EMPTY_DIR);
    WHEN("The Analyzer examines the empty directory") {
      const bool RES = analyzer.BuildCardMap();
      THEN("The card count information should be empty") {
        REQUIRE(RES == true);
        REQUIRE(analyzer.GetNumLists() == 0);
        REQUIRE(analyzer.GetCards().size() == 0);
      }
    } 
  }

  GIVEN("An Analyzer object and a directory with decklists") {
    const std::string DIRECTORY("sample_dir");
    Analyzer analyzer(DIRECTORY);
    WHEN("The Analyzer examines the decklists") {
      const bool RES = analyzer.BuildCardMap();
      THEN("The card count information is populated correctly") {
        REQUIRE(RES == true);
        REQUIRE(analyzer.GetNumLists() == 2);
        Analyzer::CardMap CARD_INFO = analyzer.GetCards();
        REQUIRE(CARD_INFO["Preordain"] == 2);
        REQUIRE(CARD_INFO["Mox Jet"] == 1);
        REQUIRE(CARD_INFO["Black Lotus"] == 11); 
        REQUIRE(CARD_INFO["Burning-Tree Emissary"] == 4);
        REQUIRE(CARD_INFO["Rancor"] == 2);
      }
    } 
  } 
} 
