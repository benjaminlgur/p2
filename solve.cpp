
#include "solve.h"

using namespace std;

// Brute-force search for one letter
void pick(Puzzle &puzzle, int row, int col) {
    char ch[26] = {'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'j', 'x', 'q', 'z'}; //array populated based on order of letter prevalence in English.
    for (int i = 0; i < 26; i++) {
        bool success = puzzle.guess(row, col, ch[i]);
        if (success){
            break; // search until letter is found
        }
    }
}

/* The main function solving the crossword puzzle */
void solve(Puzzle &puzzle) {
  
  for (int r = 0; r < puzzle.height; r++) {
    for (int c = 0; c < puzzle.width; c++) {
      if (puzzle.get(r,c) == '?') {
        // find the letter if it's a question mark
        pick(puzzle, r, c);
        // print the picture
        puzzle.print();
      }
    }
  }

}

