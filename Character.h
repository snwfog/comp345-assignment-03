/**
 *  Character.h
 *  comp345-assignment-03
 *
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include <map>
#include <vector>
#include "Item.h"

using std::map;
using std::vector;

class Character {
private:
    // basic character info
    char name[12];
    char characterClass[12];
    
    // character vital information
    int level;
    int experience, experienceToLevel;
    int hitPoint, manaPoint;
    int maxHitPoint, maxManaPoint;
    
    // character attributes
    map<Attribute, int> characterAttributes;
    
    // character armors
    map<ArmorSlot, Armor*> characterEquipments;
    
    // character weapons
    map<WeaponSlot, Weapon*> characterWeapons;
    
    // character inventory
    Item* characterInventory[10];
    
    // other character variables
    // character observers
    vector<Observers*> characterObservers;
};

#endif
