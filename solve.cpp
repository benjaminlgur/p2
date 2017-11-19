/*
  Author: <Benjamin Gur>
  Course: {135}
  Instructor: <Prof. Pajela>
  Assignment: <Project 2>

  This program will implement Project 2. It currently only accomplishes a better solve time by instead of brute forcing a-z it uses letter prevalence in the English language. 
*/

#include "solve.h"

const char brute[26] = {'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'j', 'x', 'q', 'z'}; //array populated based on order of letter prevalence in English.

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

/* The main function solving the crossword puzzle */
void solve(Puzzle &puzzle){
    int wordSize[100];
    int wordCount = 0;
    int spaceSize[100];
    int spaceCount = 0;
    char order[500];
    for (int i = 0; i < 500; i++){
        order[i] = 'n';
    }
    int orderNumber = 0;
    //Determining puzzle contents.
    enum Condition { start, space, letter, endline };
    Condition cond = start; 
    for (int r = 0; r < puzzle.height; r++) {
        for (int c = 0; c < puzzle.width; c++){
            if(puzzle.get(r, c) == ' '){
                if (cond == space){
                    spaceSize[spaceCount]++;
                }
                else if (cond == letter || cond == endline){
                    cond = space;
                    order[orderNumber] =  ' ';
                    orderNumber++;
                    spaceCount++;
                    spaceSize[spaceCount]++;
                }
                else if (cond == start){
                    cond = space;
                    order[orderNumber] =  ' ';
                    orderNumber++;
                    spaceSize[spaceCount]++;
                }
            }
            if(puzzle.get(r, c) == '?'){
                if(cond == letter){
                    wordSize[wordCount]++;
                }
                else if (cond == space || cond == endline){
                    cond = letter;
                    order[orderNumber] =  '?';
                    orderNumber++;
                    wordCount++;
                    wordSize[wordCount]++;
                }
                else if(cond == start){
                    cond = letter;
                    order[orderNumber] =  '?';
                    orderNumber++;
                    wordSize[wordCount]++;
                }
            }
        }
    }
    int col = 0;
    int row = 0;
    int x = 0;
    int wordPos = 0;
    int spacePos = 0;
    while(order[x] == ' '){
        for(int i = 0; i < spaceSize[spacePos]; i++){
            row++;
            if (row > puzzle.width){
                row = 0;
                col++;
            }
        }
        spacePos++;
        x++;
    }
    while(order[x] == '?'){
        if(wordSize[wordPos] < 4){
            for(int i = 0; i < wordSize[wordPos]; i++){
                guess(puzzle, row, col);
                puzzle.print();
                row++;
                if (row > puzzle.width){
                    row = 0;
                    col++;
                }
            }
        }
        wordPos++;
        x++;
    }               
}
