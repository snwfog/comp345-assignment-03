/**
 *  Character.h
 *  comp345-assignment-03
 *
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include <map>
#include <cmath>
#include <string>
#include <vector>
#include "Item.h"

using std::map;
using std::vector;
using std::string;

class Character {
private:
    // basic character info
    string name;
    string characterClass;
    
    // character vital information
    int level;
    int experience, experienceToLevel;
    int hitPoint, manaPoint;
    int maxHitPoint, maxManaPoint;
    int maxAttackBonus;
    
    // character ability scores
    map<Attribute, int> abilityScores;
    
    // character ability scores ranking
    Attribute* abilityRank;
    
    // character armors
    map<ArmorSlot, Armor*> equipments;
    
    // character weapons
    map<WeaponSlot, Weapon*> weapons;
    
    // character inventory
    Item* characterInventory[10];
    
    // other character variables
    // character observers
    // vector<Observers*>* characterObservers;

public:
    // functions
    int attackPerRound() { return ceil(level/5); }
    int attackBonus(int round) { return (maxAttackBonus - 5*(round - 1)); }
    
    // getters
    string getName() { return name; }
    string getCharacterClass() { return characterClass; }
    int getLevel() { return level; }
    int getExperience() { return experience; }
    int getExperienceToLevel() { return experienceToLevel; }
    int getHitPoint() { return hitPoint; }
    int getManaPoint() { return manaPoint; }
    int getMaxHitPoint() { return maxHitPoint; }
    int getMaxManaPoint() { return manaPoint; }
    int getMaxAttackBonus() { return maxAttackBonus; }
    int getAbilityScore(Attribute at) { return abilityScores[at]; }
    Attribute* getAbilityRanks() { return abilityRank; }
    Armor* getEquippedArmor(ArmorSlot as);
    Weapon* getEquippedWeapon(WeaponSlot ws) { return (weapons)[ws]; }
    Item* getInventoryItem(int index) { return characterInventory[index]; }
    
    // setters
    void setName(string n) { name = n; }
    void setCharacterClass(string n) { characterClass = n; }
    void setLevel(int l) { level = l; }
    void setExperience(int exp) { experience = exp; }
    void setHitPoint(int hp) { hitPoint = hp; }
    void setManaPoint(int mp) { manaPoint = mp; }
    void setMaxHitPoint(int maxhp) { maxHitPoint = maxhp; }
    void setMaxManaPoint(int maxmp) { maxManaPoint = maxmp; }
    void setMaxAttackBonus(int atkb) { maxAttackBonus = atkb; }
    void setAbilityScore(Attribute at, int value) { abilityScores[at] = value; }
    void setAbilityRanks(Attribute* attr) { abilityRank = attr; }
    void setEquippedArmor(ArmorSlot as, Armor* am);
    void setCharacterWeapon(WeaponSlot ws, Weapon* wp) { weapons[ws] = wp; }
    void setInventoryItem(int index, Item* it) { characterInventory[index] = it; }
    
    // character actions
    void levelUp();
};

#endif
