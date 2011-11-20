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
    
    /**
     * ChestBuilder test
     */
    ChestGenerator* cg = new ChestGenerator();
    cg->setChestBuilder(new ChestBuilder());
    cg->constructChest();
    Chest* achest = cg->getChest();
    for (int i = 0; i < achest->size(); i++) {
        map<Attribute, int> stats = achest->getItem(i)->getStatsMap();
        cout << (achest->getItem(i))->getName() << endl;
        map<Attribute, int>::const_iterator itr;
        for(itr = stats.begin(); itr != stats.end(); ++itr) {
            switch (itr->first) {
                case SIZE:
                    cout << "Size: " << static_cast<Size>(itr->second) << endl;
                    break;
                case WEAPON_WIELD:
                    cout << "Requires: " << static_cast<WeaponWield>(itr->second);
                case WEAPON_SLOT:
                    cout << "Slot: " << static_cast<ArmorSlot>(itr->second);
                default:
                    break;
            }
        }
    }

    /**
     * ItemBuilder test
     */
    ItemGenerator* ig = new ItemGenerator();
    ig->setArmorBuilder(new LeatherArmorBuilder());
    ig->constructArmor("New Leather Armor", HEAD);
    
    ig->setLongswordBuilder(new LongswordBuilder());
    ig->constructLongsword("Ashbringer", TWOHAND, HUGE);
    cout << ig->getArmor()->getCost() << endl;
    cout << ig->getLongsword()->getCost() << endl;
    cout << ig->getLongsword()->getWeaponDamage() << endl;
    cout << ig->getLongsword()->getWeaponDamage() << endl;
    cout << ig->getLongsword()->getWeaponDamage() << endl;
    cout << ig->getLongsword()->getWeaponDamage() << endl;
    /**
     * MapBuilder test
     */
    MapGenerator* mg = new MapGenerator();
    mg->setMapBuilder(new ArenaBuilder());
    mg->constructMap();
    MapEditor* me = new MapEditor(mg->getMap());
    
    
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
    cout << "Attack Bonus: " << aBully->getMaxAttackBonus() << endl;
    
    aBully->levelUp();
    cout << "HP: " << aBully->getHitPoint() << endl;
    cout << "Attack Bonus: " << aBully->getMaxAttackBonus() << endl;

    return 0;
}