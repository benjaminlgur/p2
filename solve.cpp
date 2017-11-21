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

int maxMatch (int arrSize, int *match){
    int max = -5;
    int place = 0;
    for (int i = 0; i < arrSize; i++){
        if (*(match + i) >= max){
            max = *(match + i);
            place = i;
        }
    }
    if (max < 0){
        return -5;
    }
    return place;
}

int maxWordSize(Puzzle &puzzle){
    int max = 0;
    for(int i = 0; i < puzzle.numWords; i++){
        if(puzzle.words[i].length() > max){
            max = puzzle.words[i].length();
        }
    }
    return max;
}

/* The main function solving the crossword puzzle */
void solve(Puzzle &puzzle){
    int tooMuch = 0;
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
    int *match = NULL;
    match = new int[puzzle.numWords + 1]; //+1 for safty.
    for(int c = 0; c < puzzle.width; c++){
        for(int r = 0; r < puzzle.height; r++){
            if(puzzle.get(r,c) != ' '){
            //initailizes array to 0.
                for(int i = 0; i <puzzle.numWords; i++){
                    *(match + i) = 0 ;
                }
                for(int b = 0; b < puzzle.numWords; b++){
                    reset = 0;
                    if(vertLength(puzzle, r, c) == puzzle.words[b].length()){
                        for(int w = 0; w < puzzle.words[b].length(); w++){
                            if(puzzle.get(r, c) == puzzle.words[b][w]){
                                r++;
                                reset++;
                                *(match + b) = *(match + b) + 1;
                            }
                            else{
                                r++;
                                reset++;
                            }
                        }
                    }
                    r = r - reset;
                }
                for (int b = 0; b < puzzle.numWords; b++){
                    reset = 0;
                    if(maxMatch(puzzle.numWords, match) == b && maxMatch(puzzle.numWords, match) >= 0){
                        for(int w = 0; w < puzzle.words[b].length(); w++){
                            works = puzzle.guess(r, c, puzzle.words[b][w]);
                            if (works == false){
                                r = r - reset;
                                reset = 0;
                                *(match + b) = -5; //Its a negetive number to not distirbe the 0 values.
                                b = 0;
                                break;
                            }
                            else{
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
    delete []match;   
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
