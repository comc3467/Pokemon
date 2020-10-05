#include <iostream> 
#include "Board.h"
#include <fstream>
#include <stdlib.h>
using namespace std;

int randomNum(int max){
    int randomNumber = (rand() % max)+1;
    return randomNumber;
}

void Board::setBoard(char a, int r, int c){
    boardOverall[r][c] = a;
}
void Board::initializePokemonPosition(int playerRow, int playerColumn){
    for(int rr = 0; rr < 25; rr++){
        for(int cc = 0; cc < 16; cc++){
            pokemonPositions[rr][cc] = 0;
        }
    }
    int p = 1; //integer starts at 1
    while(p < 21){
        int row = randomNum(25)-1;
        int col = randomNum(16)-1;
        if(boardOverall[row][col] != 'w' && boardOverall[row][col] != 'G'){
            if(playerRow != row && playerColumn != col){
                if(pokemonPositions[row][col] == 0){
                    pokemonPositions[row][col] = p;
                    p++;
                }
            }
        }
    }
}
void Board::initializeTrainerPositions(){
    for(int rr = 0; rr < 25; rr++){
        for(int cc = 0; cc < 16; cc++){
            trainerPositions[rr][cc] = 0; //sets everything to zero to begin with
        }
    }
    int t = 1; //for number of trainers
    while(t <= 15){ //there's 15 trainers
        for(int r = 0; r < 25; r++){
            for(int c = 0; c < 16; c++){
                if(boardOverall[r][c] == 'G'){
                    trainerPositions[r][c] = t; //gives that tile an integer
                    t++; //increments integer, will get to 15 on the last G
                }
            }
        }
    }
}

void Board::displayVisible(int playerRow, int playerColumn){
    for(int r = (playerRow-3); r <= (playerRow+3); r++){
        for(int c = (playerColumn-3); c <= (playerColumn+3); c++){
            if(playerColumn == c && playerRow == r){
                visible[3][3] = '@'; //player position
            }
            else if(r < 0 || c < 0 || r > 24 || c > 15){
                visible[(r-playerRow)+3][(c-playerColumn)+3] = '?'; //for off map
            }
            else{
                if(boardOverall[r][c] == 'w'){
                    visible[(r-playerRow)+3][(c-playerColumn)+3] = '~';
                }
                else if(boardOverall[r][c] == 'G'){
                    visible[(r-playerRow)+3][(c-playerColumn)+3] = 'G';
                }
                else if(boardOverall[r][c] == 'C'){
                    visible[(r-playerRow)+3][(c-playerColumn)+3] = 'C';
                }
                else{
                    visible[(r-playerRow)+3][(c-playerColumn)+3] = '*';
                }
            }
        }
    }
    for(int i = 0; i < 7; i++){
        for(int x = 0; x < 7; x++){
            cout << visible[i][x] << " ";
        }
        cout << endl;
    }
}
void Board::randomizePokemonPosition(int playerRow, int playerColumn){
    int p = 1;
    while(p < 21){
        for(int r = 0; r < 25; r++){//for every row
            int row = r;
            for(int c = 0; c < 16; c++){ //for every column.. hunting down integers != 0
                int col = c;
                if(pokemonPositions[r][c]  == p){ //if there is a pokemon there, it will have a number 1-20 on it, the for loops hunt them down
                    int validMove = 0; //for while loop
                    int tries = 0;
                    while(!(validMove == 1 || tries > 10)){
                        int rando = randomNum(4);
                        if(rando == 1){ //north
                            row--;
                            if((row > 24 || row < 0 || col > 15 || col < 0) || (boardOverall[row][col] == 'w' || boardOverall[row][col] == 'G' || boardOverall[row][col] == 'C') || (playerRow == row && playerColumn == col) || (pokemonPositions[row][col] != 0)) {
                                tries++;
                                row = r; //resets row back to r every time the move is not valid
                                col = c; //resets row back to c every time the move is not valid
                            }
                            else{
                                validMove++;
                            }
                        }
                        else if(rando == 2){ //south
                            row++;
                            if((row > 24 || row < 0 || col > 15 || col < 0) || (boardOverall[row][col] == 'w' || boardOverall[row][col] == 'G' || boardOverall[row][col] == 'C') || (playerRow == row && playerColumn == col) || (pokemonPositions[row][col] != 0)) {
                                tries++;
                                row = r; //resets row back to r every time the move is not valid
                                col = c; //resets row back to c every time the move is not valid
                            }
                            else{
                                validMove++;
                            }
                        }
                        else if(rando == 3){ //west
                            col--;
                            if((row > 24 || row < 0 || col > 15 || col < 0) || (boardOverall[row][col] == 'w' || boardOverall[row][col] == 'G' || boardOverall[row][col] == 'C') || (playerRow == row && playerColumn == col) || (pokemonPositions[row][col] != 0)) {
                                tries++;
                                row = r; //resets row back to r every time the move is not valid
                                col = c; //resets row back to c every time the move is not valid
                            }
                            else{
                                validMove++;
                            }
                        }
                        else if(rando == 4){ //east
                            col++;
                            if((row > 24 || row < 0 || col > 15 || col < 0) || (boardOverall[row][col] == 'w' || boardOverall[row][col] == 'G' || boardOverall[row][col] == 'C') || (playerRow == row && playerColumn == col) || (pokemonPositions[row][col] != 0)) {
                                tries++;
                                row = r; //resets row back to r every time the move is not valid
                                col = c; //resets row back to c every time the move is not valid
                            }
                            else{
                                validMove++;
                            }
                        }
                        // if((row > 24 || row < 0 || col > 15 || col < 0) || (boardOverall[row][col] == 'w' || boardOverall[row][col] == 'G' || boardOverall[row][col] == 'C') || (playerRow == row && playerColumn == col) || (pokemonPositions[row][col] != 0)) {
                        //     tries++;
                        // }
                        // else{
                        //     validMove++;
                        // }
                    }
                    if(tries >= 10){
                        int t = 0;
                        while(t < 1){
                            row = randomNum(25)-1;
                            col = randomNum(16)-1;
                            if(!((row > 24 || row < 0 || col > 15 || col < 0) || (boardOverall[row][col] == 'w' || boardOverall[row][col] == 'G' || boardOverall[row][col] == 'C') || (playerRow == row && playerColumn == col) || (pokemonPositions[row][col] != 0))){
                                t++;
                            }
                        }
                    }
                    pokemonPositions[row][col] = p; //switches
                    pokemonPositions[r][c] = 0; //switches... the zero of the empty spot and the integer of the "pokemon" spot switch
                }
            }
        }
        p++;
    }
}

int Board::checkGym(int r, int c){
    if(boardOverall[r][c] == 'G'){
        return trainerPositions[r][c]; //gym is there, returns the value of that gym, so whatever trainer is there
    }
    else{
        return 0; //no gym
    }
}
int Board::checkPokemon(int row, int col){
    for(int r = row-2; r < row+2; r++){
        //for(int c = col-2; c )
    }
    if(pokemonPositions[row][col] != 0){
        return pokemonPositions[row][col]; //pokemon is there
    }
    else{
        return 0; //no pokemon :((
    }
}
int Board::checkPokeCenter(int playerRow, int playerColumn){
    if(boardOverall[playerRow][playerColumn] == 'C'){
        return 1; //pokecenter is there
    }
    else{
        return 0; //no pokeCenter :((
    }
}
char Board::checkTile(int r, int c){
    return boardOverall[r][c];
}
void Board::displayPokemonMap(){
    for(int i = 0; i < 25; i++){
        for(int x = 0; x < 16; x++){
            cout << pokemonPositions[i][x] << " ";
        }
        cout << endl;
    }
}
void Board::deletePokemon(int gameNumber){
    for(int r = 0; r < 25; r++){
        for(int c = 0; c < 16; c++){
            if(pokemonPositions[r][c] == gameNumber){
                pokemonPositions[r][c] = 0;
            }
        }
    }
}
int Board::checkPokemonVisibility(int row, int col){
    int gameNumber = 0; //this is the int stored in the pokemonpositions board
    for(int r = row-3; r <= row+3; r++){
        for(int c = col-3; c <= col+3; c++){
            if(pokemonPositions[r][c] != 0){
                gameNumber = pokemonPositions[r][c];
            }
        }
    }
    return gameNumber; //will be either zero or a whole integer 1-20
}
int Board::checkPokemonWild(int row, int col){
    int gameNumber = 0; //this is the int stored in the pokemonpositions board
    for(int r = row-2; r <= row+2; r++){
        for(int c = col-2; c <= col+2; c++){
            if(pokemonPositions[r][c] != 0){
                gameNumber = pokemonPositions[r][c];
            }
        }
    }
    return gameNumber; //will be either zero or a whole integer 1-20
}
void Board::randomizeSingleP(int playerRow, int playerColumn, int gameNumber){
    for(int r = 0; r < 25; r++){
        for(int c = 0; c < 16; c++){
            if(pokemonPositions[r][c] == gameNumber){
                int row; //new row of pokemon
                int col; //new col of pokemon
                int t = 0;
                while(t < 1){ //while we are still looking for a new random position for the pokemon to chill at
                    row = randomNum(25)-1;
                    col = randomNum(16)-1;
                    if(!((row > 24 || row < 0 || col > 15 || col < 0) || (boardOverall[row][col] == 'w' || boardOverall[row][col] == 'G' || boardOverall[row][col] == 'C') || (playerRow == row && playerColumn == col) || (pokemonPositions[row][col] != 0))){
                        t++;
                    }
                }
                pokemonPositions[row][col] = gameNumber; //new position for pokemon
                pokemonPositions[r][c] = 0; //old position changes to zero
            }
        }
    }
}