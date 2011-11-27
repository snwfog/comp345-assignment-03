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
    cout << "*** Welcome to Dungeons and Dragons (tm)! ***" << endl;
    
    // generate a single fighter throughout the entire game
    FighterGenerator* fg = new FighterGenerator();
    fg->setCharacterBuilder(new BullyBuilder());
    fg->createNewFighter("Jennifer");
    Character* player = fg->getCharacter();
    
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
                    //MapEditor* me = new MapEditor(mg->getMap());
                    
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
                    } else {
                        cout << "Map does not exist!" << endl;
                    }
                    file.close();
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
    
    /**
     * ChestBuilder test
     */
//    ChestGenerator* cg = new ChestGenerator();
//    cg->setChestBuilder(new ChestBuilder());
//    cg->constructChest();
//    Chest* achest = cg->getChest();
//    for (int i = 0; i < achest->size(); i++) {
//        map<Attribute, int> stats = achest->getItem(i)->getStatsMap();
//        cout << (achest->getItem(i))->getName() << endl;
//        map<Attribute, int>::const_iterator itr;
//        for(itr = stats.begin(); itr != stats.end(); ++itr) {
//            switch (itr->first) {
//                case SIZE:
//                    cout << "Size: " << static_cast<Size>(itr->second) << endl;
//                    break;
//                case WEAPON_WIELD:
//                    cout << "Requires: " << static_cast<WeaponWield>(itr->second);
//                case WEAPON_SLOT:
//                    cout << "Slot: " << static_cast<ArmorSlot>(itr->second);
//                default:
//                    break;
//            }
//        }
//    }

    /**
     * ItemBuilder test
     */
//    ItemGenerator* ig = new ItemGenerator();
//    ig->setArmorBuilder(new LeatherArmorBuilder());
//    ig->constructArmor("New Leather Armor", HEAD);
//    
//    ig->setLongswordBuilder(new LongswordBuilder());
//    ig->constructLongsword("Ashbringer", TWOHAND, HUGE);
//    cout << ig->getArmor()->getCost() << endl;
//    cout << ig->getLongsword()->getCost() << endl;
//    cout << ig->getLongsword()->getWeaponDamage() << endl;
//    cout << ig->getLongsword()->getWeaponDamage() << endl;
//    cout << ig->getLongsword()->getWeaponDamage() << endl;
//    cout << ig->getLongsword()->getWeaponDamage() << endl;

    /**
     * CharacterBuilder test
     */
//    FighterGenerator* fg = new FighterGenerator();
//    fg->setCharacterBuilder(new BullyBuilder());
//    fg->createNewFighter("Johnny");
//    Character* aBully = fg->getCharacter();
//    
//    cout << aBully->getName() << endl;
//    cout << aBully->getCharacterClass() << endl;
//    cout << "STR: " << aBully->getAbilityScore(STR) << endl;
//    cout << "CON: " << aBully->getAbilityScore(CON) << endl;
//    cout << "DEX: " << aBully->getAbilityScore(DEX) << endl;
//    cout << "INT: " << aBully->getAbilityScore(INT) << endl;
//    cout << "CHR: " << aBully->getAbilityScore(CHR) << endl;
//    cout << "WIS: " << aBully->getAbilityScore(WIS) << endl;
//    cout << "HP: " << aBully->getHitPoint() << endl;
//    cout << "MP: " << aBully->getManaPoint() << endl;
//    cout << "Attack Bonus: " << aBully->getMaxAttackBonus() << endl;
//    
//    aBully->levelUp();
//    cout << "HP: " << aBully->getHitPoint() << endl;
//    cout << "Attack Bonus: " << aBully->getMaxAttackBonus() << endl;
    
    return 0;
}