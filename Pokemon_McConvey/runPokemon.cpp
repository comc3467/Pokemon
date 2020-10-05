
#include "Game.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
using namespace std;

int randomNumberR(int max){
    int randomNumber = (rand() % max)+1;
    return randomNumber;
}


void instructionsF(){
    cout << endl << "Instructions:" << endl;
    cout << "Here in the world of Pokemon, the objective is pretty simple: Be the best. That generally means either having the most or best Pokemon." << endl;
    cout << "This is a turn based game, and every turn a small part of the world surrounding you (your position denoted by @, water by ~, land by *, " << endl;
    cout << "Pokemon Center by C, Gym by G, and a position off the playable map by ?. Pokemon Gyms are where you use the Pokemon in your party of 6 to fight" << endl;
    cout << "Another trainer with their own Pokemon. If you lose against a trainer at a G location, you will be transported to the nearest Pokemon Center, " << endl;
    cout << "where your pokemon party will be healed and their levels incremented by 1. Also at the Pokemon Centers, you may change your Pokemon party." << endl;
    cout << "Now, Gyms are not the only place where one can battle; there are also battles with wild pokemon. You cannot see pokemon until you both are on the same tile," << endl;
    cout << "But from there, you will enter a battle. Battles are as follows: The pokemon who has a quicker speed attacks first. Pokemon with better stats like" << endl;
    cout << "Health points (HP), attack, defense, and speed, tend to do better in battles than weaker pokemon, but anything can happen hahaha. If you defeat" << endl;
    cout << "a wild pokemon, that pokemon joins your team (it will go in your party or to your Pokedex, accessible at any Pokemon Center." <<endl;
    cout << "Pokeballs are your form of currency; if you catch a Pokemon, you lose 1, if you defeat a trainer, you gain 5. You start with 10, so use them wisely!" << endl;
    cout << "Every turn, you have four options. 1. Move: You may choose to move in any direction that's not water (~) or off the map (?). 2. Rest: Resting a turn " << endl;
    cout << "will restore every pokemon in your party's HP by 1, but your amount of Pokeballs will go down by 1 (Pokeballs are your form of currency in this game)." << endl;
    cout << "3. Try your luck: If there is a pokemon hiding in your visibility, you have a 1/2 chance of catching that pokemon – Pokeballs are constant" << endl;
    cout << "4. Quit: please don't do this... it's just embarrassing. You can win in two ways: You defeat 6 trainers or you catch Pokemon of at least 8 different types" << endl;
    cout << "(Pokemon have either one or two types, and you can check them by going to a Pokemon Center. Hmmmmmm, I think that's about it...if not, you'll figure it out," << endl;
    cout << "Hahahahaha" << endl;
}

void pokeCenter(Game runIt, vector<Pokemon> &pokedexReference){ //cide for when the 
    cout << "POKECENTER BITCH";
}
void gym(Game runIt, vector<Pokemon> &pokedexReference){
    cout << "GYM MOTHERFUCKER";
}
void battleWild(Game runIt, vector<Pokemon> &pokedexReference){
    cout << "WILD MOTHERFUCKING BATTLE";
}

void quit(){
    cout << endl << "Thanks for your time!!";
}

void weLive(Game runIt, vector<Pokemon> &pokedexReference){
    int battles = 0; // pokemon joins party if this is the first or second battles
    int moves = 3; //counts moves (need 3 to try your luck)
    int tryLuck = 0;
    int choice = 7; //arbitrary number to start the 
    int win = 0; //becomes 1 when you win
    while(choice != 4 && win != 1){
        runIt.displayVisibleG(runIt.getPlayerRowG(), runIt.getPlayerColumnG());
        runIt.displayStats();
        cout << "Enter an integer 1-4:" << endl << "1: Move" << endl << "2: Rest" << endl << "3: Try your luck" << endl << "4: Quit" << endl;
        cin >> choice;
        if(choice < 1 || choice > 6){
            cout << "(You're supposed to choose 1-4... try again)";
        }
        else if(choice == 1){
            cout << "Move! Choose a direction to move, cannot be water (~)" << endl;
            char direction = 'p'; //arbitrary char
            int validMove = 0;
            while(validMove == 0){
                cout << "'n' = up " << endl;
                cout << "'s' = down" << endl;
                cout << "'e' = right" << endl;
                cout << "'w' = left" << endl; 
                cout << "'r' = re-choose turn options" << endl;
                cin >> direction;
                if(direction != 'n' && direction != 's' && direction != 'e' && direction != 'w' && direction != 'r'){
                    direction = 'p'; //arbitrary char to reset the while loop
                    cout << "pick 'n', 's', 'e', 'w', or 'r'... try again" << endl;
                    runIt.displayVisibleG(runIt.getPlayerRowG(), runIt.getPlayerColumnG());
                }
                else if(direction == 'r'){
                    validMove++; //gets out of the inner while loop but doesn't change anything
                }
                else{
                    if(runIt.checkChangePlayerPositionG(direction) == 0){ //will be -1 if it's water or unsuccessful, 0 if good move
                        validMove++; //it's a vlid move, so get's out of the while loop completely
                    }
                    else if(runIt.checkChangePlayerPositionG(direction) == -1){
                        cout << "That tile is water (~)... choose again" << endl;
                        runIt.displayVisibleG(runIt.getPlayerRowG(), runIt.getPlayerColumnG()); //redisplays the visible map
                    }
                    else if(runIt.checkChangePlayerPositionG(direction) == -2){
                        cout << "That tile is not part of the map (?)... choose again)" << endl;
                        runIt.displayVisibleG(runIt.getPlayerRowG(), runIt.getPlayerColumnG()); //redisplays the visible map
                    }
                }
            }
            runIt.randomizeWildPositionG(runIt.getPlayerRowG(), runIt.getPlayerColumnG()); //randomization of pokemon movements MUST BE BEFORE PLAYER MOVES
            if(direction != 'r'){
                moves++; //inrements move
                runIt.changePlayerPositionG(direction); //actually changes the position
                if(runIt.checkGymG(runIt.getPlayerRowG(), runIt.getPlayerColumnG()) != 0){ //checks if the user is now on a gym
                    int win = 69; //random number to kick things off
                    runIt.gymBattle(runIt.checkGymG(runIt.getPlayerRowG(), runIt.getPlayerColumnG()), win); //runs a gym battle function, using the trainer number from the trainer board
                }
                else if(runIt.checkPokeCenterG(runIt.getPlayerRowG(), runIt.getPlayerColumnG()) == 1){ //checks if the user is now on a pokeCenter
                    runIt.pokeCenter(0); //runs a pokecenter function with zero since you'r just chilling there
                }
                else if(runIt.checkPokemonWildG(runIt.getPlayerRowG(), runIt.getPlayerColumnG()) != 0){ //checks if the user has linked up w a pokemon
                    int win = 69; //passed by reference to the battle thingy so we can see how we did
                    runIt.battleWildG(runIt.getPokedexEntry(runIt.checkPokemonWildG(runIt.getPlayerRowG(), runIt.getPlayerColumnG())), battles, win); //runs a wild encounter function
                    battles++;
                    if(win == -1){ //lossssss
                        int r = runIt.getPlayerRowG();
                        int c = runIt.getPlayerColumnG();
                        runIt.closestGymG(r, c);
                        runIt.setPlayerPositionG(r, c);
                        cout << "You're pokemon have all fainted. You have been transported to the nearest pokemonCenter" << endl;
                        runIt.pokeCenter(-1); //runs a pokecenter function with -1 to level up because you lost
                    }
                    else if(win == -2){ //pokemonRanAway
                        runIt.randomizeSinglePG(runIt.getPlayerRowG(), runIt.getPlayerColumnG(), runIt.checkPokemonWildG(runIt.getPlayerRowG(), runIt.getPlayerColumnG())); //randomizes that pokemon
                    }
                    else if(win == 1){
                        runIt.deletePokemonG(runIt.checkPokemonWildG(runIt.getPlayerRowG(), runIt.getPlayerColumnG())); //deletes the caught pokemon from the map
                    }
                }
            cout << "NEXT TURN" << endl;
            }
        }
        else if(choice == 2){ //rest
            cout << "Ahhh, nice to relax for a turn. The HP of every pokemon in your party has increased by 1, and your Pokeballs have decreased by 1" << endl;
            cout << "You now have " << runIt.addPokeballsG(-1) << " Pokeballs left. Spennd em wisely!" << endl << "NEXT TURN" << endl;
            runIt.restUp();
        }
        else if(choice == 3){ //try your luck
            if(moves < 3){
                cout << "You need to move " << 3-moves << " time(s) before you try your luck again";
            }
            else{
                moves = 3; //this is an optional aspect of the game to make it better... change this value, moves = 3 to moves = 0 to make the game a little more fun
                int p = -1; //to count the first pokemon found
                int gameNumber = runIt.checkPokemonVisibilityG(runIt.getPlayerRowG(), runIt.getPlayerColumnG()); //either 0 or an int 1-20 for the gameNumber
                if(gameNumber == 0){
                    cout << "THERE WERE NO POKEMON IN YOUR SURROUNDNG AREA" << endl << "NEXT TURN" << endl;
                }
                else{
                    int luck = randomNumberR(10);
                    if(luck % 2 == 1){
                        cout << "THERE WAS A POKEMON IN YOUR SURROUNDING AREA, BUT FATE ALLOWED IT TO ESCAPE. BETTER LUCK NEXT TIME" << endl << "NEXT TURN" << endl;
                    }
                    else{
                        runIt.addPokemonPlayer(pokedexReference[runIt.getPokedexEntry(gameNumber)]);
                        runIt.deletePokemonG(gameNumber);
                        cout << "YOU CAUGHT A POKEMON!!! ";
                        if(runIt.getPartySize() < 6){
                            cout << pokedexReference[runIt.getPokedexEntry(gameNumber)].getName() << " HAS BEEN ADDED TO YOUR PARTY AND POKEDEX!" << endl << "NEXT TURN" << endl;
                        }
                        else{
                            cout << pokedexReference[runIt.getPokedexEntry(gameNumber)].getName() << " HAS BEEN ADDED TO YOUR POKEDEX (PARTY FULL) ";
                            cout << "ACCESS" << pokedexReference[runIt.getPokedexEntry(gameNumber)].getName() << "AT ANY POKECENTER (C)" << endl << "NEXT TURN" << endl;
                        }
                    }
                }
                runIt.randomizeWildPositionG(runIt.getPlayerRowG(), runIt.getPlayerColumnG()); //randomize positions of pokemon
            }
        }
        else if(choice == 4){
            quit(); //byeeeee
        }
        else if(choice == 5){
            runIt.displayPokemonMapG();
            runIt.randomizeWildPositionG(24, 15);
            cout << "1" << endl;
            runIt.displayPokemonMapG();
            runIt.randomizeWildPositionG(24, 15);
            cout << "2" << endl;
            runIt.displayPokemonMapG();
            runIt.randomizeWildPositionG(24, 15);
            cout << "3" << endl;
            runIt.displayPokemonMapG();
            runIt.randomizeWildPositionG(24, 15);
            cout << "4" << endl;
            runIt.displayPokemonMapG();
            runIt.randomizeWildPositionG(24, 15);
            cout << "5" << endl;
        }
        else if(choice == 6){
            for(int i = 1; i < 21; i++){
                runIt.deletePokemonG(i);

            }
        }
        
    }
}

void introGame(){
    srand(time(0));
    Game runIt; //sets a game object (which sets a vector of 151 pokedex, able to populate wild and trainers, etc.)
    vector<Pokemon> pokedexReference;
    runIt.readPokemonRoster("pokemon.txt", pokedexReference); //reads the pokemon file, so it fills up dat pokedex before it start
    runIt.readPokemonBoard("mapPoke.txt");
    cout << "Welcome to the world of Pokemon... So, you think you can tango with the finest trainers of the Kanto Region?" << endl;
    cout << "Well, it's unlikely, but the effort ought to be admirable." << endl;
    cout << "Would you like a bit of instructions before we begin?" << endl;
    int instructions = 7;
    while(instructions != 1 && instructions != 0){
        cout << "Enter 1 for yes, or 0 to proceed without instructions:" << endl;
        cin >> instructions;
        if(instructions == 1){
            instructionsF();
        }
        else if(instructions == 0){
            cout << "Hmm, no need for instructions... must mean you're pretty confident... (or maybe you've played already and lost before, hahaha) " << endl;
        }
        else{
            cout << "Ugh.. pick 1 or 2... try again" << endl;
            instructions = 7;
        }
    }
    cout << "Say, what's your name, anyways?" << endl; //cheeky lil introduction
    string user1;//code for taking in string with spaces
    cin >> user1;//code for taking in string with spaces
    string end;//code for taking in string with spaces
    getline(cin, end);//code for taking in string with spaces
    string username = user1 + end; //username
    cout << "Ahhhh, " << username << ", that sounds like the name of a champion. My name is professor Oak," << endl
    << " and I've more pokemon than I know what to do with, you want one?" << endl << "(Choose a number 1-4)" << endl;
    cout << "1. Bulbasaur" << endl << "2. Charmander" << endl << "3. Squirtle" << endl << "4. Pikachu" << endl; //gives the user a choice
    int p = 0;
    while(p < 1 || p > 4){
        cin >> p; //user gives a choice
        if(p < 1 || p > 4){ //if it's out of the acceptable range
            cout << "I said 1 through 4... pick again..." << endl; //gimme sum I can work with ughhhhh
        }
    }
    int playerR = 0; //player row
    int playerC = 0; //player column
    int po; //pokedex index based on choice and pokemon.txt
    if(p == 1){ //else if statements, setting positions and pokemon based on their decisions
        playerR = 13-1;
        playerC = 7-1;
        po = 1;
    }
    else if(p == 2){
        playerR = 13-1;
        playerC = 8-1;
        po = 4;
    }
    else if(p == 3){
        playerR = 13-1;
        playerC = 9-1;
        po = 7;
    }
    else{
        playerR = 13-1;
        playerC = 10-1;
        po = 25;
    }
    cout << "Nice pick!! I love " << pokedexReference[po-1].getName() <<"! Now, without further ado," << endl;
    cout << "let's get this show on the road! Good Luck!" << endl;
    cout << "(ominous noises as you and " << pokedexReference[po-1].getName() << " are transported to the world of Pokemon)" << endl;
    cout << endl;
    runIt.addPokemonPlayer(pokedexReference[po-1]);
    cout << "Begin!" << endl << endl;
    runIt.populateTrainers(); //gives trainers pokemon
    runIt.setGyms(); //basically populates the trainers double array so we can use it as reference for where each trainer is
    runIt.initializePokemonPositionG(playerR, playerC);//populates the pokemon positions board
    runIt.populateWild(); //populates wild, gives gameNumbers to 20 random pokemon
    runIt.setPlayerPositionG(playerR, playerC);
    weLive(runIt, pokedexReference); //in this b fr this time
    
    
}


int main(){
    introGame();
}