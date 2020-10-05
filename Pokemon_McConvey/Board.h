#include <iostream>
#include <stdlib.h>

#ifndef BOARD_H
#define BOARD_H

class Board{
    private:
        char boardOverall[25][16]; //entirety of board, read from file
        char visible[7][7]; //visible menu that's displayed every single turn
        int pokemonPositions[25][16]; //will populate a similarly sized array, with integers 0 or 1-20 depending on the pokemon there or not
        int trainerPositions[25][16]; //will populate a similarly sized arrat, with integers 1-15 on positions where there is a Gym
    public:
        int readBoardFile(std::string fileName); //starts game by reading file and beginning with initializing position of player at 0,0, for later changing
        void displayVisible(int playerRow, int playerColumn); //takes in a player position and calculates the visible plain around him;
        void initializePokemonPosition(int playerRow, int playerColumn); //initializes 20 random pokemon spots
        void initializeTrainerPositions(); //populates the trainers double array according to where the gyms are
        void randomizePokemonPosition(int playerRow, int playerColumn); //randomizes pokemon position after each turn
        int checkGym(int r, int c); //checks the trainers board and returns trainer number of that position
        int checkPokemon(int playerRow, int playerColumn); //returns 1 if there is a pokemon on that exact position (we will need to traverse visible area...)
        int checkPokeCenter(int playerRow, int playerColumn);
        void setBoard(char a, int r, int c);
        char checkTile(int r, int c); //checks the tile of the boardOverall
        void displayPokemonMap(); //brrp
        void deletePokemon(int gameNumber); //refreshes the pokemon positions map,replacing a cought pokemon with a 0;
        int checkPokemonVisibility(int row, int col);
        int checkPokemonWild(int row, int col);
        void randomizeSingleP(int playerRow, int playerColumn, int gameNumber);
};  
#endif