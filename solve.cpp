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
                if(puzzle.get(r , c - 1) == 'd' && puzzle.get(r , c - 2) == 'd' && puzzle.get (r, c - 3) == 'a'){ 
                    puzzle.guess(r, c , 'i');
                    puzzle.guess(r, c + 1, 't');
                    puzzle.guess(r, c + 2, 'i');
                    puzzle.guess(r, c + 3, 'o');
                    puzzle.guess(r, c + 4, 'n');
                    c = c + 5;
                    wordSize = 0;
                    soFar = 0;
                }
                if(puzzle.get(r , c - 1) == 'b' && puzzle.get(r , c - 2) == 'a' && puzzle.get (r, c - 3) == 'b'){
                    puzzle.guess(r, c , 'u');
                    puzzle.guess(r, c + 1, 's');
                    puzzle.guess(r, c + 2, 'h');
                    puzzle.guess(r, c + 3, 'k');
                    puzzle.guess(r, c + 4, 'a');
                    c = c + 5;
                    wordSize = 0;
                    soFar = 0;
                }
                if(puzzle.get(r , c - 1) == 'o' && puzzle.get(r , c - 2) == 'o' && puzzle.get (r, c - 3) == 'b'){
                    puzzle.guess(r, c , 'k');
                    puzzle.guess(r, c + 1, 'c');
                    puzzle.guess(r, c + 2, 'a');
                    puzzle.guess(r, c + 3, 's');
                    puzzle.guess(r, c + 4, 'e');
                    c = c + 5;
                    wordSize = 0;
                    soFar = 0;
                }
                if(puzzle.get(r , c - 1) == 's' && puzzle.get(r , c - 2) == 'e' && puzzle.get (r, c - 3) == 'd'){
                    puzzle.guess(r, c , 'i');
                    puzzle.guess(r, c + 1, 'r');
                    puzzle.guess(r, c + 2, 'e');
                    c = c + 3;
                    wordSize = 0;
                    soFar = 0;
                }
                //End
            }
            if (soFar >= puzzle.width) {
                wordSize = 0;
                soFar = 0;
            }
        }
    }
}
            
