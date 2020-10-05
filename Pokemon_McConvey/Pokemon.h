#include <iostream>

#ifndef POKEMON_H
#define POKEMON_H

class Pokemon{
    private:
        std::string name;
        int pokedexEntry;
        int stats[5]; 
        std::string type[2];
        int numType = 0;
        int level = 1;
        int gameNumber = -1;
    public:
        Pokemon();
        Pokemon(int pokedex, std::string name, int stats1[], std::vector<std::string> type1, int gameNum);
        void setHP(int hp);
        int getHP();
        void setAttack(int attack);
        int getAttack();
        void setDefense(int defense);
        int getDefense();
        void setSpeed(int speed);
        int getSpeed();
        void setMax(int Max);
        int getMax();
        int setGameNumber(int g);
        int getGameNumber();
        std::string getName();
        void levelUp();
};
#endif

        