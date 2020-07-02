# decklist_analyzer
Small Utility to Analyze Trading Card Game (TCG) Decklists for Most-Played Cards

## **Overview**
When playing trading card games, players often want to know the aggregate statistics of the top-performing decks.

## **Compiling the Code**
This code was compiled using GCC and CMake.  Please use the following steps to compile this tool and the associating unit tests:

```
mkdir build
cd build
cmake ..
make
```

The executable is named `DeckAnalyzer`.  To run this program you will need to provide the directory
of the decklists:

```
DeckAnalyzer <full path to decklists>
```

The decklists are flat text files where each entry is in the form of `<number of copies> <card name>`.  For example:

```
4 Preordain
1 Black Lotus
1 Mox Sapphire
2 Dack Fayden
```
