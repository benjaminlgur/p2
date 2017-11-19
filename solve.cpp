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
            if(puzzle.get(r,c) == '?'){
                wordSize++;
                soFar++;
            }
            if(puzzle.get(r,c) == ' '){
                soFar++;
                wordSize = 0;
            }
            if (wordSize < 4){
                guess(puzzle, r, c);
                puzzle.print();
            }
            if (wordSize >= 4){
                //Start
                if(puzzle.get(r , c - 1) == 't' && puzzle.get(r , c - 2) == 'i' && puzzle.get (r, c - 3) == 't'){
                    puzzle.guess(r, c , 'a');
                    puzzle.guess(r, c + 1, 'n');
                    puzzle.guess(r, c + 2, 'i');
                    puzzle.guess(r, c + 3, 'u');
                    puzzle.guess(r, c + 4, 'm');
                    c = c + 5;
                    wordSize = 0;
                    soFar = 0;
                }
                //if(puzzle.get(r, c - 1) == 
                
                //End
            }
            if (soFar >= puzzle.width) {
                wordSize = 0;
                soFar = 0;
            }
        }
    }
}
            
