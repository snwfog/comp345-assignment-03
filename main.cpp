//
//  main.cpp
//  comp345-assignment-02
//
//  Created by Charles Chao Yang on 11-11-03.

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include "MapEditor.h"
#include "d20Game.h"
#include "ChestBuilder.h"
#include "MapBuilder.h"
#include "CharacterBuilder.h"
#include "d20GameBuilder.h"

using namespace std;

int main (int argc, const char* argv[]) {
    srand(time(0));
    
    int opt;
    string input = "";
    cout << "***********************************" << endl;
    cout << "* ====      Welcome to       ==== *" << endl;
	cout << "*  === Dungeons and Dragons  ===  *" << endl;
	cout << "*   ==       COMP345         ==   *" << endl;
    cout << "***********************************" << endl;
    
    // generate a single fighter throughout the entire game
    FighterGenerator* fg = new FighterGenerator();
    fg->setCharacterBuilder(new BullyBuilder());
    fg->createNewFighter("Jennifer");
    Character* player = fg->getCharacter();
    
    // give awesome starting item to the 
    ItemGenerator* ig = new ItemGenerator();
    ig->setArmorBuilder(new FullplateArmorBuilder());
    ig->constructArmor("Warbringer Chestguard", CHEST);
    player->putInventoryItem(ig->getArmor(), FALSE); // false is no notifying through observer
    ig->constructArmor("Warbringer Gauntlets", HANDS);
    player->putInventoryItem(ig->getArmor(), FALSE);
    ig->constructArmor("Warbringer Greathelm", HEAD);
    player->putInventoryItem(ig->getArmor(), FALSE);
    ig->constructArmor("Warbringer Greaves", FEET);
    player->putInventoryItem(ig->getArmor(), FALSE);
    ig->constructArmor("Champion's Seal", FINGER);
    player->putInventoryItem(ig->getArmor(), FALSE);
    ig->setWeaponBuilder(new LongswordBuilder());
    ig->constructWeapon("The Ashbringer", TWOHAND, BUGE);
    player->putInventoryItem(ig->getWeapon(), FALSE);
    ig->constructWeapon("Treacherous Blade", TWOHAND, BUGE);
    player->putInventoryItem(ig->getWeapon(), FALSE);
    ig->setWeaponBuilder(new LongbowBuilder());
    ig->constructWeapon("The Fallen Star", TWOHAND, MEDIUM);
    player->putInventoryItem(ig->getWeapon(), FALSE);
    
    bool quit = FALSE;
    while (!quit) {
        cout << "1. Map Editor" << endl;
        cout << "2. Play Arena" << endl;
        cout << "3. Play Custom Map" << endl;
        cout << "4. Quit Game" << endl;
        cout << "Choose your option: ";
        // for safety check of input http://www.cplusplus.com/forum/articles/6046/
        getline(cin, input);
        stringstream stm(input);
        if (stm >> opt && opt <= 4 && opt >= 1) {
            switch (opt) {
                case 1: {
                    cout << "Please enter a map name. If the map already exists, " << endl;
                    cout << "it will be loaded, else a new map will be created with the name." << endl;
                    cout << "Map name: ";
                    getline(cin, input);
                    MapEditor* editor = new MapEditor(input);
                    break; }
                case 2: {
                  /**
                    * MapBuilder
                    */
                    MapGenerator* mg = new MapGenerator();
                    mg->setMapBuilder(new ArenaBuilder());
                    mg->constructMap();
                    
                    d20GameBuilder* gb = new d20GameBuilder();
                    gb->createNewGame();
                    gb->setStaticGameComponent(player, mg->getMap());
                    d20Game* game = gb->getGame();
                    game->start();
                    delete gb;
                    delete mg;
                    gb = NULL;
                    mg = NULL;
                    break; }
                case 3: {
                    cout << "Map name: ";
                    getline(cin, input);
                    std::fstream file;
                    file.open(input.c_str(), ios_base::out | ios_base::in);
                    if (file.is_open()) {
                        // close the file
                        file.close();
                        Map* map = new Map(input);
                        d20GameBuilder* gb = new d20GameBuilder();
                        gb->createNewGame();
                        gb->setStaticGameComponent(player, map);
                        d20Game* game = gb->getGame();
                        game->start();
                        
                        delete gb;
                        gb = NULL;
                    } else
                        cout << "Map does not exist!" << endl;
                    break; }
                case 4: {
                    cout << "Good bye!" << endl;
                    quit = TRUE;
                    exit(1);
                    break;}
                default: {
                    cout << "Error: Unrecognized option, please try again." << endl;   
                    break;  }  
            }
        }
    }
    return 0;
}