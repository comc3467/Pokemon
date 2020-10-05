#include <iostream>
#include <vector>



#ifndef PLAYER_H
#define PLAYER_H

class Player{
    private:
        std::string name;
        int points = 0;
        int pokeballs = 0;
        int badges = 0;
        int playerRow;
        int playerColumn;
    public:
        Player();
        Player(std::string name1, int poin, int pokeball, int playerRow, int playerColumn); //paramatized
        int addPoints(int p); //could be negative, returns value afterwards
        int addPokeballs(int po); //could be negative, returns value afterwards
        int addBadges(int b); //could . be negative, returns value afterwards
        void setPlayerPosition(int r, int c);
        int getPlayerRow();
        int getPlayerColumn();
        void changeParty(int selections[], int indexPokedex);
        int changePlayerPosition(char d, Board gameBoard); //takes in either n, s, e, w for direction and changes accordingly; -1 if it's water or unsiccessful. 0 if good.
        int checkChangePlayerPosition(char d, Board gameBoard);
    
};
#endif