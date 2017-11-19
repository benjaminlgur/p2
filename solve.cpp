/*
  Author: <Benjamin Gur>
  Course: {135}
  Instructor: <Prof. Pajela>
  Assignment: <Project 2>

  This program will implement Project 2. It currently only accomplishes a better solve time by instead of brute forcing a-z it uses letter prevalence in the English language. 
*/

#include "solve.h"

const char brute[26] = {'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'j', 'x', 'q', 'z'}; //array populated based on order of letter prevalence in English.

const char titanium[8] = {'t','i','t','a','n','i','u','m'};

using namespace std;

// Brute-force search for one letter
void guess(Puzzle &puzzle, int row, int col){
    for (int i = 0; i < 26; i++){
        bool success = puzzle.guess(row, col, brute[i]);
        if (success){
            break; // search until letter is found
        }
    }
}

/*void titaniumWord(Puzzle &puzzle, int r, int c){
    puzzle.guess(r, c + 1, 'a');
    puzzle.guess(r, c + 2, 'n');
    puzzle.guess(r, c + 3, 'i');
    puzzle.guess(r, c + 4, 'u');
    puzzle.guess(r, c + 5, 'm');
}*/

/* The main function solving the crossword puzzle */
void solve(Puzzle &puzzle){
    int wordSize = 0;
    int soFar = 0;
    for (int r = 0; r < puzzle.height; r++){
        for (int c = 0; c < puzzle.width; c++){
            if (puzzle.get(r,c) == '?'){
                wordSize++;
            }
            if (puzzle.get(r,c) == ' '){
                wordSize = 0;
            }
            if (c + 1 > puzzle.width){
                wordSize = 0;
            }
            if (wordSize < 5){
                guess(puzzle, r, c);
                puzzle.print();
            }
            if (wordSize >= 3){
                //Start
                cout << "Word size " << wordSize << endl;
                for(int a = 0; a < puzzle.numWords; a++){
                    if(puzzle.get(r , c - 1) == puzzle.words[a][2] && puzzle.get(r , c - 2) == puzzle.words[a][1] && puzzle.get (r, c - 3) == puzzle.words[a][0]){
                        for(int i = 3; i < puzzle.words[a].length(); i++){
                            puzzle.guess(r, c, puzzle.words[a][i]);
                            puzzle.print();
                            c++;
                        }
                        wordSize = 0;
                    }
                }
            }      
        }
    }
    // Just in case.
    /*
    for (int r = 0; r < puzzle.height; r++) {
        for (int c = 0; c < puzzle.width; c++) {
            if (puzzle.get(r,c) == '?') {
                // find the letter if it's a question mark
                guess(puzzle, r, c);
                // print the picture
                puzzle.print();
            }
        }
    }
    */
}
