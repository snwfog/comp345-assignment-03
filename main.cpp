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
#include "ChestBuilder.h"
#include "MapBuilder.h"
#include "CharacterBuilder.h"

using namespace std;

int main (int argc, const char* argv[]) {
    srand(time(0));
    
//    int opt;
//    string input = "";
//    cout << "Welcome to the Game Editor!" << endl;
//    
//    while (true) {
//        cout << "1. Map Editor" << endl;
//        cout << "2. Character Editor" << endl;
//        cout << "3. Quit Editor" << endl;
//        cout << "Choose your option: ";
//        // for safety check of input http://www.cplusplus.com/forum/articles/6046/
//        getline(cin, input);
//        stringstream stm(input);
//        if (stm >> opt && opt <= 3 && opt >= 1) {
//            switch (opt) {
//                case 1: {
//                    cout << "Please enter a map name. If the map already exists, " << endl;
//                    cout << "it will be loaded, else a new map will be created with the name." << endl;
//                    cout << "Map name: ";
//                    string file;
//                    cin >> file;
//                    MapEditor* editor = new MapEditor(file);
//                    break; }
//                case 2: {
//                    cout << "Sorry, the Character Editor  is not available yet." << endl;
//                    break; }
//                case 3: {
//                    cout << "Good bye!" << endl;
//                    exit(1);
//                    break;}
//                default: {
//                    cout << "Unrecognized option." << endl;
//                    break;  }  
//            }
//
//        }
//        
//        cout << "Error: Unrecognized option, please try again." << endl;    
//    }
    
    
//    ChestGenerator* cg = new ChestGenerator();
//    cg->setChestBuilder(new ChestBuilder());
//    cg->constructChest();
//    Chest* achest = cg->getChest();
//    for (int i = 0; i < achest->size(); i++) {
//        map<string, int> stats = achest->getItem(i)->getStatsMap();
//        cout << (achest->getItem(i))->getName() << endl;
//        map<string, int>::const_iterator itr;
//        for(itr = stats.begin(); itr != stats.end(); ++itr) {
//            if ((itr->first).compare("Size") == 0)
//                cout << "Size: " << static_cast<Size>(itr->second) << endl;
//            else if ((itr->first).compare("Wield") == 0)
//                cout << "Requires: " << static_cast<WeaponWield>(itr->second);
//            else if ((itr->first).compare("Slot") == 0)
//                cout << "Slot: " << static_cast<ArmorSlot>(itr->second);
//                
//        }
//    }

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
//    
//    MapGenerator* mg = new MapGenerator();
//    mg->setMapBuilder(new ArenaBuilder());
//    mg->constructMap();
//    MapEditor* me = new MapEditor(mg->getMap());
//    
    
/**
 * CharacterBuilder test
 */
    FighterGenerator* fg = new FighterGenerator();
    fg->setCharacterBuilder(new BullyBuilder());
    fg->createNewFighter("Johnny");
    Character* aBully = fg->getCharacter();
    
    cout << aBully->getName() << endl;
    cout << aBully->getCharacterClass() << endl;
    cout << "STR: " << aBully->getAbilityScore(STR) << endl;
    cout << "CON: " << aBully->getAbilityScore(CON) << endl;
    cout << "DEX: " << aBully->getAbilityScore(DEX) << endl;
    cout << "INT: " << aBully->getAbilityScore(INT) << endl;
    cout << "CHR: " << aBully->getAbilityScore(CHR) << endl;
    cout << "WIS: " << aBully->getAbilityScore(WIS) << endl;
    cout << "HP: " << aBully->getHitPoint() << endl;
    cout << "MP: " << aBully->getManaPoint() << endl;
    
    return 0;
}