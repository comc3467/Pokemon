#include "Player.h"
#include "Board.h"
#include <iostream>
using namespace std;

Player::Player(){
    points = 0;
    pokeballs = 10;
    name = "";
    playerRow = -1;
    playerColumn = -1;
}
Player::Player(string name1, int poin, int pokeball, int playerR, int playerC){
    name = name1;
    points = poin;
    pokeballs = pokeball;
    playerRow = playerR;
    playerColumn = playerC;
}

int Player::addPoints(int p){
    points += p;
    return points;
}
int Player::addPokeballs(int po){
    pokeballs += po;
    return pokeballs;
}
int Player::addBadges(int b){
    badges += b;
    return badges;
}
void Player::setPlayerPosition(int r, int c){
    playerColumn = c;
    playerRow = r;
}
int Player::getPlayerRow(){
    return playerRow;
}
int Player::getPlayerColumn(){
    return playerColumn;
}
int Player::changePlayerPosition(char d, Board gameBoard){
    int playerColumn1 = playerColumn;
    int playerRow1 = playerRow;
    char e = tolower(d);
    if(e == 'n'){
        playerRow1--;
    }
    else if(e == 's'){
        playerRow1++;
    }
    else if(e == 'w'){
        playerColumn1--;
    }
    else if(e == 'e'){
        playerColumn1++;
    }
    if(playerColumn1 < 0 || playerColumn1 > 15 || playerRow1 < 0 || playerRow1 > 24){
        return -2;
    } 
    else if(gameBoard.checkTile(playerRow, playerColumn) == 'w'){
        return -1;
    }
    else{
        playerColumn = playerColumn1;
        playerRow = playerRow1;
        return 0;
    }
}
int Player::checkChangePlayerPosition(char d, Board gameBoard){
    int playerColumn1 = playerColumn;
    int playerRow1 = playerRow;
    char e = tolower(d);
    if(e == 'n'){
        playerRow1--;
    }
    else if(e == 's'){
        playerRow1++;
    }
    else if(e == 'w'){
        playerColumn1--;
    }
    else if(e == 'e'){
        playerColumn1++;
    }
    if(playerColumn1 < 0 || playerColumn1 > 15 || playerRow1 < 0 || playerRow1 > 24){
        return -2;
    } 
    else if(gameBoard.checkTile(playerRow1, playerColumn1) == 'w'){
        return -1;
    }
    else{
        return 0;
    }
}