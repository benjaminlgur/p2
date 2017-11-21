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

int horLength (Puzzle &puzzle, int r, int c){
    int wordSize = 0;
    char curChar = '?';
    while (curChar != ' '){
        curChar = puzzle.get(r, c);
        if(curChar !=  ' '){
            wordSize++;
            c++;
        }
        else {
            break;
        }
    }
    return wordSize;
}

int vertLength (Puzzle &puzzle, int r, int c){
    int wordSize = 0;
    char curChar = '?';
    while (curChar != ' '){
        curChar = puzzle.get(r, c);
        if(curChar != ' '){
            wordSize++;
            r++;
        }
        else {
            break;
        }
    }
    return wordSize;
}      
    

/* The main function solving the crossword puzzle */
void solve(Puzzle &puzzle){
    //cout << "ADAD " << bull << endl; return;
    //for(int i=0; i<puzzle.numWords; i++) cout<<puzzle.words[i]<<endl; return;
    bool works;
    int reset = 0;
    for (int r = 0; r < puzzle.height; r++){
        for (int c = 0; c < puzzle.width; c++){
            if(puzzle.get(r,c) != ' '){
                for(int a = 0; a < puzzle.numWords; a++){
                    reset = 0;
                    if(horLength(puzzle, r, c) == puzzle.words[a].length()){
                        for(int l = 0; l < puzzle.words[a].length(); l++){
                            works = puzzle.guess(r, c, puzzle.words[a][l]);
                            if (works == false){
                                c = c - reset;
                                reset = 0;
                                break;
                            }
                            else {
                                puzzle.print();
                                c++;
                                reset++;
                            }
                        }
                    }
                }
            }
        }
    }
    for(int c = 0; c < puzzle.width; c++){
        for(int r = 0; r < puzzle.height; r++){
            if(puzzle.get(r,c) != ' '){
                for(int b = 0; b < puzzle.numWords; b++){
                    reset = 0;
                    if(vertLength(puzzle, r, c) == puzzle.words[b].length()){
                        for(int w = 0; w < puzzle.words[b].length(); w++){
                            if(puzzle.get(r, c) == '?'){
                                works = puzzle.guess(r, c, puzzle.words[b][w]);
                            }
                            else if(puzzle.get(r, c) == puzzle.words[b][w]){
                                works = true;
                            }
                            else if(puzzle.get(r, c) != puzzle.words[b][w] && puzzle.get(r, c) != '?'){
                                works = false;
                            }
                            if (works == false){
                                r = r - reset;
                                reset = 0;
                                break;
                            }
                            else {
                                puzzle.print();
                                r++;
                                reset++;
                            }
                        }
                    }
                }
            }
        }
    }
}
    //Just in case 
    /*
    for (int r = 0; r < puzzle.height; r++){
        for (int c = 0; c < puzzle.width; c++){
            if (puzzle.get(r,c) == '?') {
                // find the letter if it's a question mark
                guess(puzzle, r, c);
                // print the picture
                puzzle.print();
            }
        }
    }
}*/
