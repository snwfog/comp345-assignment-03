/**
 *  Character.h
 *  comp345-assignment-03
 *
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include <map>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include "Item.h"
#include "Observer.h"

using std::map;
using std::vector;
using std::string;
using std::stringstream;

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
    int maxAttackBonus, maxDamageBonus;
    int gold;
    
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
    Observer* observer;
    
public:
    // functions
    int attackPerRound() { return ceil(level/5); }
    int attackBonus(int attackRound) { return (maxAttackBonus - 5*(attackRound - 1)); }
    void giveGold(int g) { gold += g; }
    int takeGold(int g) { gold -= g; return g; }
    
    // getters
    string getName() { return name; }
    string getCharacterClass() { return characterClass; }
    int getGold() { return gold; }
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
    Armor* getEquippedArmor(ArmorSlot as) { return (equipments)[as]; }
    Weapon* getEquippedWeapon(WeaponSlot ws) { return (weapons)[ws]; }
    Item* getInventoryItem(int index) { return characterInventory[index]; }
    
    // setters
    void setName(string n) { name = n; }
    void setCharacterClass(string n) { characterClass = n; }
    void setGold(int g) { gold = g; }
    void setLevel(int l) { level = l; }
    void setExperience(int exp) { experience = exp; }
    void setHitPoint(int hp) { hitPoint = hp; }
    void setManaPoint(int mp) { manaPoint = mp; }
    void setMaxHitPoint(int maxhp) { maxHitPoint = maxhp; }
    void setMaxManaPoint(int maxmp) { maxManaPoint = maxmp; }
    void setMaxAttackBonus(int atkb) { maxAttackBonus = atkb; }
    void setAbilityScore(Attribute at, int value) { abilityScores[at] = value; }
    void setAbilityRanks(Attribute* attr) { abilityRank = attr; }
    void setEquippedArmor(ArmorSlot as, Armor* am) { equipments[as] = am; }
    void setEquippedWeapon(WeaponSlot ws, Weapon* wp) { weapons[ws] = wp; }
    void setInventoryItem(int index, Item* it) { characterInventory[index] = it; }
    
    // character actions
    void levelUp();
    void equipArmor(ArmorSlot, Armor*);
    Armor* unequipArmor(ArmorSlot);
    void equipWeapon(WeaponSlot, Weapon*);
    Weapon* unequipWeapon(WeaponSlot);
    
    // helper functions
    // set all armors, weapons inventory to null
    void wipeAllContainer();
    //void wipeContainer(int it);
    int emptyInventorySlot();
    // observer methods
    void attachCharacterObserver(Observer* ob) { observer = ob; }
};

#endif
