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
#include "Map.h"
#include "Item.h"
#include "Observer.h"
#include "Merchant.h"

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
    int maxArmorBonus;
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
    
    // map coordinate
    Coordinate* coord;
public:
    // functions
    int attackPerRound() { return ceil(level/5.0); }
    int attackBonus(int attackRound) { return (maxAttackBonus - 5*(attackRound - 1)); }
    void giveGold(int g) { gold += g; }
    int takeGold(int g) { gold -= g; return g; }
    
    // getters
    string getName() { return name; }
    string getCharacterClass() { return characterClass; }
    int getGold() { return gold; }
    int getLevel() { return level; }
    int getExperience() { return experience; }
    //int getExperienceToLevel() { return experienceToLevel; }
    int getExperienceToLevel() { return 20 * (pow(level, 2.0) + level*2 + 1); }
    int getHitPoint() { return hitPoint; }
    int getManaPoint() { return manaPoint; }
    int getMaxHitPoint() { return maxHitPoint; }
    int getMaxManaPoint() { return manaPoint; }
    int getMaxAttackBonus() { return maxAttackBonus; }
    int getMaxDamagBonus() { return maxDamageBonus; }
    int getAbilityScore(Attribute at) { return abilityScores[at]; }
    int getArmorBonus() { return maxArmorBonus; }
    Attribute* getAbilityRanks() { return abilityRank; }
    Armor* getEquippedArmor(ArmorSlot as) { return (equipments)[as]; }
    Weapon* getEquippedWeapon(WeaponSlot ws) { return (weapons)[ws]; }
    Item* getInventoryItem(int index) { return characterInventory[index]; }
    Coordinate* getCoordinate() { return coord; }
    
    // setters
    void setName(string n) { name = n; }
    void setCharacterClass(string n) { characterClass = n; }
    void setGold(int g) { gold = g; }
    void setLevel(int l) { level = l; }
    void setExperience(int exp, bool = FALSE);
    void setHitPoint(int hp) { hitPoint = hp; }
    void setManaPoint(int mp) { manaPoint = mp; }
    void setMaxHitPoint(int maxhp) { maxHitPoint = maxhp; }
    void setMaxManaPoint(int maxmp) { maxManaPoint = maxmp; }
    void setMaxAttackBonus(int atkb) { maxAttackBonus = atkb; }
    void setMaxDamageBonus(int dmgb) { maxDamageBonus = dmgb; }
    void setAbilityScore(Attribute at, int value) { abilityScores[at] = value; }
    void setArmorBonus(int ab) { maxArmorBonus = ab; }
    void setAbilityRanks(Attribute* attr) { abilityRank = attr; }
    void setEquippedArmor(ArmorSlot as, Armor* am);
    void setEquippedWeapon(WeaponSlot ws, Weapon* wp);
    void setInventoryItem(int index, Item* it) { characterInventory[index] = it; }
    void setCoordinate(int y, int x) {
        coord = new Coordinate(y, x);
    }
    
    // character actions
    void levelUp();
    void equipArmor(ArmorSlot, Armor*);
    Armor* unequipArmor(ArmorSlot);
    void equipWeapon(WeaponSlot, Weapon*);
    Weapon* unequipWeapon(WeaponSlot);
    
    void usePotion(Potion*);
    // main d20 battle function
    void battle(Character*, int round = 1);
    int getAttackRoll(int round = 1);
    
    void removeInventoryItem(int index, bool notify = TRUE);
    void putInventoryItem(Item*, bool notify = TRUE);
    void putToInventory(Item*, int, bool notify = TRUE);
    void deleteInventoryItem(int);
    void equipWeaponFromInventory(WeaponSlot ws, int inventorySlot);
    void equipArmorFromInventory(ArmorSlot as, int inventorySlot);
    void deleteInventoryItem(int index, bool notify, bool log, string msg);
    
    // character check function
    bool isDisabled() { return ((hitPoint <= 0) && (hitPoint > -10)); }
    bool isDead() { return (hitPoint <= -10); }
    
    // helper functions
    // set all armors, weapons inventory to null
    void wipeAllContainer();
    void deleteEquippedArmor(ArmorSlot);
    void deleteEquippedWeapon(WeaponSlot);
    
    int emptyInventorySlot();
    bool inventoryIsFull();
    
    // merchant related actions
    void buy(Merchant*, int);
    void sell(int);
    
    // observer methods
    void attachCharacterObserver(Observer* ob) { observer = ob; }
};

#endif
