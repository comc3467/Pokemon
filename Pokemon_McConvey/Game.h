#include <vector>
#include <iostream>
#include "Pokemon.h"
#include "Board.h"
#include "Player.h"
#include <stdlib.h>
using namespace std;



#ifndef GAME_H
#define GAME_H

class Game{
    private:
        int win = 0; //becomes 1 when the user wins, -1 when the user loses
        Board gameBoard; //every game has a board
        Player player;
        std::vector<Pokemon> pokedexOverall; //pokedex Overall
        std::vector<Pokemon> pokedexPlayer; //pokedex of the player
        std::vector<Pokemon> partyPlayer; //party of the player
        Pokemon trainerParties[15][6]; //the parties might not be full, but double array is easier imo
        
    public:
        Game();
        int readPokemonRoster(std::string fileName, std::vector<Pokemon> &pokedexReference); //returns -1 if not opened correctly
        void initializePokemonPositionG(int playerRow, int playerColumn); //populates the pokemonPositions double array
        void randomizeWildPositionG(int playerRow, int playerColumn); //this randomizes positions of an ALREADY POPULATED board
        void populateWild(); //this gives random pokemon a game number, so that we know "who's in the wild"
        void populateTrainers(); //gives the trainers their pokemon
        void setGyms(); //sets the positions of the trainers... basically calls upon the board to create a specific integer 1-15 on positions with a G
        void battle(int gymNumber); //gotta figure this hoe out
        int getPokedexEntry(int gameNum); //for wild pokemon... enter the "game number" found in the wild and you get the pokedex entry
        int getWin();
        void addPokemonPlayer(Pokemon p);
        int readPokemonBoard(string fileName);
        void displayVisibleG(int playerRow, int playerColumn); //for calling on the display visible in the board function
        void setPlayerPositionG(int playerRow, int playerColumn); //sets player positions
        int checkChangePlayerPositionG(char d); //checks the return value to see if it would work
        void changePlayerPositionG(char d); //actually moves the character
        int getPlayerRowG();
        int getPlayerColumnG();
        int checkGymG(int playerRow, int playerColumn); //checks if a gym is where the player is; int not zero for gym, 0 for no gym
        int checkPokeCenterG(int playerRow, int playerColumn); //checks if there is a pokecenter
        int checkPokemonWildG(int playerRow, int playerColumn); //checks if there is a pokemon... int 1-20 for pokemon, 0 for nun
        void displayPokemonMapG();
        int getPartySize();
        int addPokeballsG(int pokeballs);
        void restUp();
        void deletePokemonG(int gameNumber);
        void displayStats();
        int checkPokemonVisibilityG(int playerRow, int playerColumn);
        void battleWildG(int pokedexEntry, int battles, int &win);
        void gymBattle(int trainerNum, int &win);
        void closestGymG(int &playerRow, int &playerColumn); //returns the int of the proper gymm
        void pokeCenter(int w); //int is zero if you're just going there, it's -1 if you're going because you lost
        void randomizeSinglePG(int playerRow, int playerColumn, int gameNumber);
        
        
        
};
#endif