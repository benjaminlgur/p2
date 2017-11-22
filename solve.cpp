/*
  Author: <Benjamin Gur>
  Course: {135}
  Instructor: <Prof. Pajela>
  Assignment: <Project 2>

  This program will implement Project 2. It solves the crossword by first using the length of words to try to find a match horizontally and then vertacly using already reveled letters and length of word. Finaly doing a last check that brute forces any remaining question marks although none should remain.
*/

#include "solve.h"

const char brute[26] = {'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'j', 'x', 'q', 'z'}; //array populated based on order of letter prevalence in English.


using namespace std;

// Brute-force search for one letter
//Precondition: For puzzle for first argument, current row and column for col. Should be used in a loop.
//Postconditon: Uses puzzle.guess() function in the order of most common use of letter in English.
void guess(Puzzle &puzzle, int row, int col){
    for (int i = 0; i < 26; i++){
        bool success = puzzle.guess(row, col, brute[i]);
        if (success){
            break; // search until letter is found
        }
    }
}

//Precondition: For puzzle for first argument, r and c should be the position of a start of a horizontal word on the puzzle.
//Postcondtion: will return the length of word on puzzle.
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


//Precondition: For puzzle for first argument, r and c should be the position of a start of a vertical word on the puzzle.
//Postcondtion: will return the length of word on puzzle.
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

//Preconditon: arrSize sould be puzzle.numWords, *match should be pointer to dinamic array of matchs of revieled letters to words on puzzle.words[].
//Postcondion: Returns the position on array witch has the greatest value.
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

//Precondition: puzzle as lone argument.
//Postcondition: Returns the size of the largest word.
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
    bool works; //bool used to determin success of puzzle.guess().
    int reset = 0; //used to reset back to the begining of the word if neccessay.
    //Below finds the horisontal words using word length.
    for (int r = 0; r < puzzle.height; r++){
        for (int c = 0; c < puzzle.width; c++){//nested for loops move left to right then down one
            if(puzzle.get(r,c) != ' '){ //find word.
                for(int a = 0; a < puzzle.numWords; a++){//cycles through words.
                    reset = 0; //reset is reset at start of new word search.
                    if(horLength(puzzle, r, c) == puzzle.words[a].length()){ //checks that the length is equivilent.
                        for(int l = 0; l < puzzle.words[a].length(); l++){
                            works = puzzle.guess(r, c, puzzle.words[a][l]);
                            if (works == false){
                                c = c - reset; //If fail brings back to start of word.
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
    int *match = NULL; //making dinaminc array to hold comparison value between the revealed letters on puzzle and puzzle.words[].
    match = new int[puzzle.numWords + 1]; //+1 for safty.
    //Finds letter matches in reveled parts of the puzzle and puzzle.words[]
    //goes up to down then moves over one right.
    for(int c = 0; c < puzzle.width; c++){
        for(int r = 0; r < puzzle.height; r++){
            if(puzzle.get(r,c) != ' '){
            //initailizes array to 0.
                for(int i = 0; i <puzzle.numWords; i++){
                    *(match + i) = 0 ;
                }
                for(int b = 0; b < puzzle.numWords; b++){
                    reset = 0; //reset is reset at start of new word search.
                    if(vertLength(puzzle, r, c) == puzzle.words[b].length()){
                        for(int w = 0; w < puzzle.words[b].length(); w++){
                            if(puzzle.get(r, c) == puzzle.words[b][w]){
                                r++;
                                reset++;
                                *(match + b) = *(match + b) + 1; //increases match score, if match is found.
                            }
                            else{
                                r++;
                                reset++;
                            }
                        }
                    }
                    r = r - reset; //resets back to start of word after check.
                }
                //Guesses word 
                for (int b = 0; b < puzzle.numWords; b++){
                    reset = 0; //reset is reset at start of new word search.
                    if(maxMatch(puzzle.numWords, match) == b && maxMatch(puzzle.numWords, match) >= 0 && vertLength(puzzle, r, c) == puzzle.words[b].length()){
                        //guesses words verticly based on size and match value.
                        for(int w = 0; w < puzzle.words[b].length(); w++){
                            works = puzzle.guess(r, c, puzzle.words[b][w]);
                            if (works == false){
                                r = r - reset;
                                reset = 0;
                                *(match + b) = -5; //Its a negetive number to make it less than the 0 values.
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
    delete []match; //deletes dinamic array                                                       
    //Just in case this brute forces any remaining question marks although this should not be necessary.
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
}
