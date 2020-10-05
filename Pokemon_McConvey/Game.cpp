#include <iostream>
#include "Game.h"
#include "Pokemon.h"
#include "Board.h"
#include "Player.h"
#include <vector>
#include <fstream>
#include <stdlib.h>
using namespace std;

int randomNumber(int max){
    int randomNumber = (rand() % max)+1;
    return randomNumber;
}

Game::Game(){
    win = 0;
}

void split(string s, char del, vector<string> &tempVec){ //function with four paramaters, including a string, a character, an array, and an integer
    string temp = s + del;
    string a; //initialize string for the word to be put in each array spot
    for(int g = 0; g < temp.length(); g++){ //loop for g < length of the temp string
        if(temp[g] != del){ //if the character of temp in spot g does not equal the delimeter
            a += temp[g]; //add that character to string a for author
        }
        else{ //if the character is the delimeter
            if(a != ""){//if the string is not empty (if there were two delimeters in a row, it would not run through this)
                tempVec.push_back(a);
                a = "";
            }
            else{
                a = ""; //for when there are two delimeters back to back
            }
        }
    }
}
void splitChar(string s, char del, char temparr[], int x){ //function with four paramaters, including a string, a character, an array, and an integer
    string temp = s + del;
    int n = 0; //for temp array
    for(int g = 0; g < temp.length(); g++){ //loop for g < length of the temp string
        if(temp[g] != del){ //if the character of temp in spot g does not equal the delimeter
            temparr[n] = temp[g]; //that character becomes the next iteration of the temparr
            n++;
        }
    }
}
int Game::readPokemonRoster(string fileName, vector<Pokemon> &pokedexReference){ //code for reading the pokemon.txt file
    ifstream myFile; //names ifstream
    myFile.open(fileName); //opens file
    if(myFile.is_open()){ //if it's open
        string line = ""; //sets string for readin the file
        int lineidx = 0;
        while(getline(myFile, line)){ //while we can read lines from the file
            if(lineidx == 0){
                lineidx++;
            }
            else{
                vector<string> tempVec; //sets a vector of strings
                split(line, ',', tempVec); //sends every line to the split function
                int num = stoi(tempVec[0]); //for the pokedex entry number
                string name1 = tempVec[1]; //for the pokemon name
                int stats1[5]; //array of doubles for stats
                for(int i = 2; i < 7; i++){ //traverses the stats of the string "line"
                    stats1[i-2] = stoi(tempVec[i]); //converts
                }
                vector<string> type1; //array for the types of the pokemon
                for(int g = 7; g < tempVec.size(); g++){ // traverses the pokemon types
                    type1.push_back(tempVec[g]); //fills vector with 1 or two types, depending
                }
                Pokemon p = Pokemon(num, name1, stats1, type1, -1); //gives a gameNumber of -1 so we know for later
                pokedexOverall.push_back(p); //will end up filling up 151 pokemon, so the vector will be that big
                pokedexReference.push_back(p);
            }
        }
        myFile.close(); //closes the file just in case
        return 0;
    }
    else{
        return -1;// if it didn't open trhe file correctly
    }
}
int Game::readPokemonBoard(string fileName){
    ifstream myFile;
    myFile.open(fileName);
    if(myFile.is_open()){
        string line = "";
        int i = 0;
        while(getline(myFile, line)){
            if(line != ""){
                char temparr[16];
                splitChar(line, ',', temparr, 16);
                for(int g = 0; g < 16; g++){
                    gameBoard.setBoard(temparr[g], i, g);
                }
                i++;
            }
        }
        myFile.close();
        return 0;
    }
    else{
        return -1;// if it didn't open trhe file correctly
    }
}
void Game::initializePokemonPositionG(int playerRow, int playerColumn){
    gameBoard.initializePokemonPosition(playerRow, playerColumn); //initializes pokemon map with int 1-20 scattered among zeros
}
void Game::randomizeWildPositionG(int playerRow, int playerColumn){
    gameBoard.randomizePokemonPosition(playerRow, playerColumn); //randomizes all pokemon positions that are left
}
void Game::populateWild(){ //function that populates the wild
    for(int p = 1; p < 21; p++){ //for 20 pokemon total
        int t = 0;
        while(t < 1){ //changes to 1 when we find a pokemon that is not one of the four choosable
            int randoP = randomNumber(151)-1; //gets a random
            if(randoP != 0 && randoP != 1 && randoP != 2 && randoP != 4 && pokedexOverall[randoP].getGameNumber() == -1){ //can't be one of the starters, that's not how pokemon works!! also can't already be out there
                t++; //gets outta the while loop
                pokedexOverall[randoP].setGameNumber(p); //sets the game number of that pokemon to p... that way, when you encounter an int on the pokemon board that's not zero, you can find what pokemon it is.
            }    
        }
    }
}

void Game::populateTrainers(){
    for(int t = 0; t < 15; t++){
        int numb = randomNumber(6);
        for(int p = 0; p < 6; p++){
            if(p < numb){
                int t = 0;
                while(t < 1){ //changes to 1 when we find a pokemon that is not one of the four choosable
                    int randoP = randomNumber(151)-1; //gets a random
                    if(randoP != 0 && randoP != 1 && randoP != 2 && randoP != 4 && pokedexOverall[randoP].getGameNumber() == -1){ //can't be one of the starters, that's not how pokemon works!! also can't already be out there
                        t++; //gets outta the while loop
                        trainerParties[t][p] = pokedexOverall[randoP];//gives the trainer their pokemon...
                        pokedexOverall[randoP].setGameNumber(69); //all trainers get pokemon w gamenumber 69... that way they dont all have the smae pokemon
                    }    
                }
            }
            else{
                vector<string> type1;
                type1.push_back(" "); //gives empty type
                int stats1[5]; //blank w zeros
                trainerParties[t][p] = Pokemon(-5, "", stats1, type1, -5); //gives them dud pokemon..if a pokemon does not have a pokedex entry or whatever, it's not a pokemon
            }
        }
    }
}

void Game::setGyms(){
    gameBoard.initializeTrainerPositions();
}
int Game::getPokedexEntry(int gameNumber){
    int h = -1;
    for(int i = 0; i < 151; i++){
        if(pokedexOverall[i].getGameNumber() == gameNumber){
            h = i+1;
        }
    }
    return h; //returns the iteration in the pokedex of the encountered wild pokemon... tells you what pokemon it is, basically
}

void Game::battle(int gymNumber){
    
}
int Game::getWin(){
    return win;
}
void Game::addPokemonPlayer(Pokemon p){
    if(partyPlayer.size() < 6){
        partyPlayer.push_back(p);
        pokedexPlayer.push_back(p);
    }
    else{
        pokedexPlayer.push_back(p);
    }
}
void Game::displayVisibleG(int playerRow, int playerColumn){
    gameBoard.displayVisible(playerRow, playerColumn);
}
void Game::setPlayerPositionG(int playerRow, int playerColumn){
    player.setPlayerPosition(playerRow, playerColumn);
}
int Game::checkChangePlayerPositionG(char d){
    return player.checkChangePlayerPosition(d, gameBoard);
}
void Game::changePlayerPositionG(char d){
    player.changePlayerPosition(d, gameBoard);
}
int Game::getPlayerRowG(){
    return player.getPlayerRow();
}
int Game::getPlayerColumnG(){
    return player.getPlayerColumn();
}
int Game::checkGymG(int playerRow, int playerColumn){
    return gameBoard.checkGym(playerRow, playerColumn);
}
int Game::checkPokeCenterG(int playerRow, int playerColumn){
    return gameBoard.checkPokeCenter(playerRow, playerColumn);
}
void Game::displayPokemonMapG(){
    gameBoard.displayPokemonMap();
}
int Game::getPartySize(){
    return partyPlayer.size();
}
int Game::addPokeballsG(int pokeballs){
    return player.addPokeballs(pokeballs); //could be negative, returns the amount of pokeballs the player ahs after adding the int
}
void Game::restUp(){
    for(int i = 0; i < partyPlayer.size(); i++){
        if(partyPlayer[i].getHP() < partyPlayer[i].getMax()){
            partyPlayer[i].setHP(1);
        }
    }
}
void Game::deletePokemonG(int gameNumber){
    gameBoard.deletePokemon(gameNumber);
}
void Game::displayStats(){
    cout << "CURRENT PARTY:" << endl;
    for(int i = 0; i < partyPlayer.size(); i++){
        if(i == 0){
            cout << "Name: " << partyPlayer[i].getName() << " (ACTIVE), ";
            cout << "HP: " << partyPlayer[i].getHP() << ", ";
            cout << "A: " << partyPlayer[i].getAttack() << ", ";
            cout << "D: " << partyPlayer[i].getDefense() << ", ";
            cout << "S: " << partyPlayer[i].getSpeed() << ", ";
            cout << "M: " << partyPlayer[i].getMax() << ", " << endl;
        }
        else{
            cout << "Name: " << partyPlayer[i].getName() << ", ";
            cout << "HP: " << partyPlayer[i].getHP() << ", ";
            cout << "A: " << partyPlayer[i].getAttack() << ", ";
            cout << "D: " << partyPlayer[i].getDefense() << ", ";
            cout << "S: " << partyPlayer[i].getSpeed() << ", ";
            cout << "M: " << partyPlayer[i].getMax() << ", " << endl;
        }
    }
}
int Game::checkPokemonVisibilityG(int playerRow, int playerColumn){
    return gameBoard.checkPokemonVisibility(playerRow, playerColumn);
}
int Game::checkPokemonWildG(int playerRow, int playerColumn){
    return gameBoard.checkPokemonWild(playerRow, playerColumn);
}
void Game::battleWildG(int pokedexEntry, int battles, int &win){
    Pokemon p = pokedexOverall[pokedexEntry];
    cout << "You encountered a wild pokemon!!!" << endl;
    if(battles == 0 || battles == 1){
        cout << "This is either your first or second time encountering a wild pokemon. " << p.getName() << "has decided to join your party" << endl;
        if(partyPlayer.size() < 6){
            partyPlayer.push_back(p);
            pokedexPlayer.push_back(p);
        }
        else{
            pokedexPlayer.push_back(p);
        }
    }
    else{
        int c;
        int fleeN = 0;
        int runN = 0;
        while(win != 0 && win != -1 && win != 1 && win != -2){
            cout << "Wild " << p.getName() << ":" << endl;
            cout << "Name: " << p.getName() << ", ";
            cout << "HP: " << p.getHP() << ", ";
            cout << "A: " << p.getAttack() << ", ";
            cout << "D: " << p.getDefense() << ", ";
            cout << "S: " << p.getSpeed() << ", ";
            cout << "M: " << p.getMax() << ", " << endl;
            cout << endl << "Your active pokemon is: " << partyPlayer[0].getName() << ": " << endl;
            cout << "Name: " << partyPlayer[0].getName() << " (ACTIVE), ";
            cout << "HP: " << partyPlayer[0].getHP() << ", ";
            cout << "A: " << partyPlayer[0].getAttack() << ", ";
            cout << "D: " << partyPlayer[0].getDefense() << ", ";
            cout << "S: " << partyPlayer[0].getSpeed() << ", ";
            cout << "M: " << partyPlayer[0].getMax() << ", " << endl;
            cout << endl << "What wuold you like to do?" << endl << "1. Fight" << endl << "2. Switch Active Pokemon" << endl << "3. Run" << endl;
            cin >> c;
            if(c == 1){
                int flee = randomNumber(10);
                if(flee < 5){
                    fleeN++;
                    int B = (partyPlayer[0].getSpeed()/4) % 256;
                    int A = p.getSpeed();
                    int F = (A*32)/B +(30*fleeN);
                    if(F > 256 || randomNumber(256)-1 < F){
                        cout << "The pokemon has fled." << endl;
                        win = -2; //negative 2 if the pokemon runs
                    }
                }
                else{
                    if(p.getSpeed() <= partyPlayer[0].getSpeed()){
                        int A = randomNumber(partyPlayer[0].getAttack()+1)-1;
                        int D = randomNumber(p.getDefense()+1)-1;
                        if(A > D){
                            p.setHP(0-(A-D));
                        }
                        int A1 = randomNumber(p.getAttack()+1)-1;
                        int D1 = randomNumber(partyPlayer[0].getDefense()+1)-1;
                        if(A1 > D1){
                            partyPlayer[0].setHP(0-(A1-D1));
                        }
                    }
                    else{
                        int A1 = randomNumber(p.getAttack()+1)-1;
                        int D1 = randomNumber(partyPlayer[0].getDefense()+1)-1;
                        if(A1 > D1){
                            partyPlayer[0].setHP(0-(A1-D1));
                        }
                        int A = randomNumber(partyPlayer[0].getAttack()+1)-1;
                        int D = randomNumber(p.getDefense()+1)-1;
                        if(A > D){
                            p.setHP(0-(A-D));
                        }
                    }
                    if(p.getHP() <= 0){
                        partyPlayer[0].levelUp();
                        win = 1;
                        p.setHP(0-p.getHP()); //sets thje hp to zero to then add the maximum
                        p.setHP(p.getMax()); //set to the maximum
                        if(partyPlayer.size() < 6){
                            partyPlayer.push_back(p);
                            pokedexPlayer.push_back(p);
                        }
                        else{
                            pokedexPlayer.push_back(p);
                        }
                    }
                    else if(partyPlayer[0].getHP() <= 0){
                        p.levelUp();
                        partyPlayer[0].setHP(0-partyPlayer[0].getHP()); //sets it to zero to look better
                        int lose = 0; //lil holder to see if all pokemon are dead
                        for(int checkLose = 0; checkLose < partyPlayer.size(); checkLose++){
                            if(partyPlayer[checkLose].getHP() > 0){
                                lose++;
                            }
                        }
                        if(lose == 0){
                            win--; //-1 if the player loses
                        }
                        else{
                            cout << partyPlayer[0].getName() << " has fainted, please choose another pokemon to battle." << endl;
                            for(int po = 0; po < partyPlayer.size(); po++){
                                if(partyPlayer[po].getHP() <= 0){
                                    cout << "Name: " << partyPlayer[po].getName() << " (FAINTED), ";
                                    cout << "HP: " << partyPlayer[po].getHP() << ", ";
                                    cout << "A: " << partyPlayer[po].getAttack() << ", ";
                                    cout << "D: " << partyPlayer[po].getDefense() << ", ";
                                    cout << "S: " << partyPlayer[po].getSpeed() << ", ";
                                    cout << "M: " << partyPlayer[po].getMax() << ", " << endl;
                                }
                                else{
                                    cout << po << ". --- ";
                                    cout << "Name: " << partyPlayer[po].getName() << ", ";
                                    cout << "HP: " << partyPlayer[po].getHP() << ", ";
                                    cout << "A: " << partyPlayer[po].getAttack() << ", ";
                                    cout << "D: " << partyPlayer[po].getDefense() << ", ";
                                    cout << "S: " << partyPlayer[po].getSpeed() << ", ";
                                    cout << "M: " << partyPlayer[po].getMax() << ", " << endl;
                                }
                            }
                            int newBattler = 0;
                            while (!(newBattler < 6 && newBattler > 0)){
                                cin >> newBattler;
                                if((newBattler > 4 || newBattler < 0)){
                                    cout << "Pick a feasible number" << endl;
                                }
                                else{
                                    if(partyPlayer[newBattler].getHP() <= 0){
                                        cout << "Pick a pokemon who has HP" << endl;
                                        newBattler = 0; //so we can stay in the while loop
                                    }
                                    else{
                                        Pokemon f = partyPlayer[0];
                                        Pokemon n = partyPlayer[newBattler];
                                        partyPlayer[0] = n; //puts the new pokemon as the active pokemon
                                        partyPlayer[newBattler] = f; //puts the fainted pokemon in the position where the new one comes from
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if(c == 2){
                for(int po = 0; po < partyPlayer.size(); po++){
                    if(partyPlayer[po].getHP() <= 0){
                        cout << "Name: " << partyPlayer[po].getName() << " (FAINTED), ";
                        cout << "HP: " << partyPlayer[po].getHP() << ", ";
                        cout << "A: " << partyPlayer[po].getAttack() << ", ";
                        cout << "D: " << partyPlayer[po].getDefense() << ", ";
                        cout << "S: " << partyPlayer[po].getSpeed() << ", ";
                        cout << "M: " << partyPlayer[po].getMax() << ", " << endl;
                    }
                    else{
                        cout << po << ". --- ";
                        cout << partyPlayer[po].getName() << ", ";
                        cout << "HP: " << partyPlayer[po].getHP() << ", ";
                        cout << "A: " << partyPlayer[po].getAttack() << ", ";
                        cout << "D: " << partyPlayer[po].getDefense() << ", ";
                        cout << "S: " << partyPlayer[po].getSpeed() << ", ";
                        cout << "M: " << partyPlayer[po].getMax() << ", " << endl;
                    }
                }
                cout << partyPlayer.size()+1 << " re-choose battle selection" << endl;
                int newBattler = 0;
                while (!(newBattler < 7 && newBattler > 0)){
                    cin >> newBattler;
                    if((newBattler > 4 || newBattler < 0)){
                        cout << "Pick a feasible number" << endl;
                    }
                    else{
                        if(partyPlayer[newBattler].getHP() <= 0){
                            cout << "Pick a pokemon who has HP" << endl;
                            newBattler = 0; //so we can stay in the while loop
                        }
                        else{
                            Pokemon f = partyPlayer[0];
                            Pokemon n = partyPlayer[newBattler];
                            partyPlayer[0] = n; //puts the new pokemon as the active pokemon
                            partyPlayer[newBattler] = f; //puts the old pokemon in the position where the new one comes from
                        }
                    }
                }
            }
            else if(c == 3){
                runN++;
                int B = (p.getSpeed()/4) % 256;
                int A = partyPlayer[0].getSpeed();
                int F = (A*32)/B +(30*runN);
                if(F > 256 || randomNumber(256)-1 < F){
                    cout << "You have successfully run away." << endl;
                    win = 0; //win = 0 if the plahyer successfully runs away
                }
                else{
                    cout << "You failed to escape!" << endl;
                }
            }
            else{
                cout << "Choose a number 1-3" << endl;
                c = 7;
            }
        }
    }
}
void Game::closestGymG(int &playerRow, int &playerColumn){
    int closest = 500; //holder for the int of spaces to a gym
    for(int r = 0; r < 25; r++){
        for(int c = 0; c < 16; c++){ //traverses whole game board
            if(gameBoard.checkGym(r, c) != 0){ //if there's a gym at r,c , then there's an int there
                int rows = r-playerRow;
                if(rows < 0){
                    rows = rows * -1; //changes to positive
                }
                int cols = c-playerColumn;
                if(cols < 0){
                    cols = cols*-1; //changes to positive
                }
                int distance = cols+rows; //total "moves" to get there
                if(distance < closest){ //if it's closer
                    closest = distance;
                    playerRow = r; //since they are passed by reference, we don't have to worry about returning aything
                    playerColumn = c;
                }
            }
        }
    }
}
void Game::pokeCenter(int w){
    cout << "Welcome to the PokeCenter... Your pokemon are being restored to full health" << endl;
    for(int i = 0; i < partyPlayer.size(); i++){
        partyPlayer[i].setHP(partyPlayer[i].getMax()); //sets the HP back to the max
        if(w == -1){
            partyPlayer[i].levelUp();
        }
    }
    int c = 0;
    if(pokedexPlayer.size() > 6){
        while(!(c == 1 || c == 2)){
            cout << "Would you like to access you Pokedex and switch pokemon around?" << endl << "1. Yes" << endl << "2. No" << endl;
            cin >> c;
            if(!(c == 1 || c == 2)){
                cout << "Please pick either 1 or 2" << endl;
            }
        }
        if(c == 1){
            for(int p = 0; p < pokedexPlayer.size(); p++){
                cout << (p + 1) << ". ";
                cout << "Name: " << pokedexPlayer[p].getName() << ", ";
                cout << "HP: " << pokedexPlayer[p].getHP() << ", ";
                cout << "A: " << pokedexPlayer[p].getAttack() << ", ";
                cout << "D: " << pokedexPlayer[p].getDefense() << ", ";
                cout << "S: " << pokedexPlayer[p].getSpeed() << ", ";
                cout << "M: " << pokedexPlayer[p].getMax() << ", " << endl;
            }
            cout << "Make six selections (enter int 1-" << pokedexPlayer.size() << "and press enter after each selection.)" << endl;
            int selections[6];
            int selection;
            for(int s = 0; s < 6; s++){
                cin >> selection;
                selections[s] = selection-1; //minus one because the selections are 1 to size
            }
            for(int i = 0; i < 6; i++){  //for the entire nuber of selections
                partyPlayer[i] = pokedexPlayer[selections[i]]; //sets the party iteration i to the iteration of the value of the iteration i of arr
            }
        }
    }
    else{
        cout << "You have no pokemon solely in your PC. Good luck out there!!" << endl;
    }
}
void Game::randomizeSinglePG(int playerRow, int playerColumn, int gameNumber){
    gameBoard.randomizeSingleP(playerRow, playerColumn, gameNumber);
}
void Game::gymBattle(int trainerNum, int &win){
    int trainerP = 0;
    int c = 7;
    while(win != -1 && win != 1){
            cout << "Opponents Pokemon: " << endl;
            cout << "Name: " << trainerParties[trainerNum][0].getName() << ", ";
            cout << "HP: " << trainerParties[trainerNum][0].getHP() << ", ";
            cout << "A: " << trainerParties[trainerNum][0].getAttack() << ", ";
            cout << "D: " << trainerParties[trainerNum][0].getDefense() << ", ";
            cout << "S: " << trainerParties[trainerNum][0].getSpeed() << ", ";
            cout << "M: " << trainerParties[trainerNum][0].getMax() << ", " << endl;
            cout << endl << "Your active pokemon is: " << partyPlayer[0].getName() << ": " << endl;
            cout << "Name: " << partyPlayer[0].getName() << " (ACTIVE), ";
            cout << "HP: " << partyPlayer[0].getHP() << ", ";
            cout << "A: " << partyPlayer[0].getAttack() << ", ";
            cout << "D: " << partyPlayer[0].getDefense() << ", ";
            cout << "S: " << partyPlayer[0].getSpeed() << ", ";
            cout << "M: " << partyPlayer[0].getMax() << ", " << endl;
            cout << endl << "What wuold you like to do?" << endl << "1. Fight" << endl << "2. Switch Active Pokemon" << endl;
            cin >> c;
            if(c == 1){
                if(trainerParties[trainerNum][0].getSpeed() <= partyPlayer[0].getSpeed()){
                    int A = randomNumber(partyPlayer[0].getAttack()+1)-1;
                    int D = randomNumber(trainerParties[trainerNum][0].getDefense()+1)-1;
                    if(A > D){
                        trainerParties[trainerNum][0].setHP(0-(A-D));
                    }
                    int A1 = randomNumber(trainerParties[trainerNum][0].getAttack()+1)-1;
                    int D1 = randomNumber(partyPlayer[0].getDefense()+1)-1;
                    if(A1 > D1){
                        partyPlayer[0].setHP(0-(A1-D1));
                    }
                }
                else{
                    int A1 = randomNumber(trainerParties[trainerNum][0].getAttack()+1)-1;
                    int D1 = randomNumber(partyPlayer[0].getDefense()+1)-1;
                    if(A1 > D1){
                        partyPlayer[0].setHP(0-(A1-D1));
                    }
                    int A = randomNumber(partyPlayer[0].getAttack()+1)-1;
                    int D = randomNumber(trainerParties[trainerNum][0].getDefense()+1)-1;
                    if(A > D){
                        trainerParties[trainerNum][0].setHP(0-(A-D));
                    }
                }
                if(trainerParties[trainerNum][0].getHP() <= 0){
                    int winCheck = 0;
                    for(int check = 0; check < 6; check++){
                        if(partyPlayer[check].getHP() > 0){
                            winCheck++;
                        }
                    }
                    if(winCheck == 0){
                        win++; //1 if the player wins!!!
                    }
                    else{
                        trainerP++;
                        Pokemon t = trainerParties[trainerNum][0];
                        trainerParties[trainerNum][0] = trainerParties[trainerNum][trainerP];
                        trainerParties[trainerNum][trainerP] = t;
                        
                    }
                }
                else if(partyPlayer[0].getHP() <= 0){
                    trainerParties[trainerNum][0].levelUp();
                    partyPlayer[0].setHP(0-partyPlayer[0].getHP()); //sets it to zero to look better
                    int lose = 0; //lil holder to see if all pokemon are dead
                    for(int checkLose = 0; checkLose < partyPlayer.size(); checkLose++){
                        if(partyPlayer[checkLose].getHP() > 0){
                            lose++;
                        }
                    }
                    if(lose == 0){
                        win--; //-1 if the player loses
                    }
                    else{
                        cout << partyPlayer[0].getName() << " has fainted, please choose another pokemon to battle." << endl;
                        for(int po = 0; po < partyPlayer.size(); po++){
                            if(partyPlayer[po].getHP() <= 0){
                                cout << "Name: " << partyPlayer[po].getName() << " (FAINTED), ";
                                cout << "HP: " << partyPlayer[po].getHP() << ", ";
                                cout << "A: " << partyPlayer[po].getAttack() << ", ";
                                cout << "D: " << partyPlayer[po].getDefense() << ", ";
                                cout << "S: " << partyPlayer[po].getSpeed() << ", ";
                                cout << "M: " << partyPlayer[po].getMax() << ", " << endl;
                            }
                            else{
                                cout << po << ". --- ";
                                cout << "Name: " << partyPlayer[po].getName() << ", ";
                                cout << "HP: " << partyPlayer[po].getHP() << ", ";
                                cout << "A: " << partyPlayer[po].getAttack() << ", ";
                                cout << "D: " << partyPlayer[po].getDefense() << ", ";
                                cout << "S: " << partyPlayer[po].getSpeed() << ", ";
                                cout << "M: " << partyPlayer[po].getMax() << ", " << endl;
                            }
                        }
                        int newBattler = 0;
                        while (!(newBattler < 6 && newBattler > 0)){
                            cin >> newBattler;
                            if((newBattler > 4 || newBattler < 0)){
                                cout << "Pick a feasible number" << endl;
                            }
                            else{
                                if(partyPlayer[newBattler].getHP() <= 0){
                                    cout << "Pick a pokemon who has HP" << endl;
                                    newBattler = 0; //so we can stay in the while loop
                                }
                                else{
                                    Pokemon f = partyPlayer[0];
                                    Pokemon n = partyPlayer[newBattler];
                                    partyPlayer[0] = n; //puts the new pokemon as the active pokemon
                                    partyPlayer[newBattler] = f; //puts the fainted pokemon in the position where the new one comes from
                                }
                            }
                        }
                    }
                }
            }
            else if(c == 2){
                for(int po = 0; po < partyPlayer.size(); po++){
                    if(partyPlayer[po].getHP() <= 0){
                        cout << "Name: " << partyPlayer[po].getName() << " (FAINTED), ";
                        cout << "HP: " << partyPlayer[po].getHP() << ", ";
                        cout << "A: " << partyPlayer[po].getAttack() << ", ";
                        cout << "D: " << partyPlayer[po].getDefense() << ", ";
                        cout << "S: " << partyPlayer[po].getSpeed() << ", ";
                        cout << "M: " << partyPlayer[po].getMax() << ", " << endl;
                    }
                    else{
                        cout << po << ". --- ";
                        cout << partyPlayer[po].getName() << ", ";
                        cout << "HP: " << partyPlayer[po].getHP() << ", ";
                        cout << "A: " << partyPlayer[po].getAttack() << ", ";
                        cout << "D: " << partyPlayer[po].getDefense() << ", ";
                        cout << "S: " << partyPlayer[po].getSpeed() << ", ";
                        cout << "M: " << partyPlayer[po].getMax() << ", " << endl;
                    }
                }
                cout << partyPlayer.size()+1 << " re-choose battle selection" << endl;
                int newBattler = 0;
                while (!(newBattler < 7 && newBattler > 0)){
                    cin >> newBattler;
                    if((newBattler > 4 || newBattler < 0)){
                        cout << "Pick a feasible number" << endl;
                    }
                    else{
                        if(partyPlayer[newBattler].getHP() <= 0){
                            cout << "Pick a pokemon who has HP" << endl;
                            newBattler = 0; //so we can stay in the while loop
                        }
                        else{
                            Pokemon f = partyPlayer[0];
                            Pokemon n = partyPlayer[newBattler];
                            partyPlayer[0] = n; //puts the new pokemon as the active pokemon
                            partyPlayer[newBattler] = f; //puts the old pokemon in the position where the new one comes from
                        }
                    }
                }
            }
            else{
                cout << "Choose a number 1-3" << endl;
                c = 7;
            }
        }
}