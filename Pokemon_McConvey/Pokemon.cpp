#include <iostream>
#include <vector>
#include "Pokemon.h"
using namespace std;

Pokemon::Pokemon(){
    pokedexEntry = 0;
    name = "";
    for(int i = 0; i < 5; i++){
        stats[i] = 0;
    }
    for(int g = 0; g < 2; g++){
        type[g] = "";
    }
    level = 0;
    int gameNumber = -1;
}

Pokemon::Pokemon(int pokedex, string name1, int stats1[], vector<string> type1, int gameNum){
    pokedexEntry = pokedex;
    name = name1;
    for(int i = 0; i < 5; i++){
        stats[i] = stats1[i];
    }
    type[0] =type1[0];
    if(type1.size() == 2){
        type[1] = type1[1];
    }
    // for(int g = 0; g < 2; g++){
    //     type[g] = type1[g];
    //     if(type[g] != ""){
    //         numType++;
    //     }
    // }
    level = 1;
    gameNumber = gameNum;
}
void Pokemon::setHP(int hp){ //adds hp to stats[0]
    stats[0] += hp;
}
int Pokemon::getHP(){
    return stats[0];
}
void Pokemon::setAttack(int attack1){
    stats[1] += attack1;
}
int Pokemon::getAttack(){
    return stats[1];
}
void Pokemon::setDefense(int defense1){
    stats[2] += defense1;
}
int Pokemon::getDefense(){
    return stats[2];
}
void Pokemon::setSpeed(int speed1){
    stats[3] += speed1;
}
int Pokemon::getSpeed(){
    return stats[3];
}
void Pokemon::setMax(int max1){
    stats[4] = max1;
}
int Pokemon::getMax(){
    return stats[4];
}
int Pokemon::setGameNumber(int g){
    gameNumber = g;
    return gameNumber;
}
int Pokemon::getGameNumber(){
    return gameNumber;
}
string Pokemon::getName(){
    return name;
}
void Pokemon::levelUp(){
    if(stats[0] < stats[4]){
        if((stats[0] % 50) != 0){
            if((stats[0] += ((stats[0]/50)+1)) > stats[4]){
                stats[0] = stats[4];
            }
            else{
                stats[0] += ((stats[0]/50)+1);
            }
        }
        else{
            if((stats[0] += stats[0]/50) > stats[4]){
                stats[0] = stats[4];
            }
            else{
                stats[0] += (stats[0]/50);
            }
        }
    }
}