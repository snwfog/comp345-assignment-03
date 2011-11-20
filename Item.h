/**
 *  Item.h
 *  comp345-assignment-03
 *
 *  Size, ArmorSlot, WeaponSlot, WeaponWield
 *  Item, Armor, Potion, Weapon, Longsword
 *  All of these class are pretty much self-explanatory,
 *  and they are logically built from d20 equipments rules.
 *  This class is different from assignment 2, I have moved
 *  all the constructor to their representative "builder"
 *  class, see ItemBuilder.h. 
 */
#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <map>
#include "Functions.h"

using std::string;
using std::map;

/**
 * Enumerations
 */
enum Size { FINE = 1, DIMINUTIVE, TINY, SMALL, MEDIUM,
            LARGE, HUGE, GARGANTUAN, COLOSSAL };

enum ArmorSlot { HEAD = 1, CHEST, HANDS, FEET, 
                 WAIST, WRIST, FINGER } ;

enum WeaponSlot { MAINHAND = 1, OFFHAND };
enum WeaponWield { ONEHAND = 1, TWOHAND };

enum Attribute { ARMOR_CLASS = 20, MAX_DEXTERITY, ARMOR_SLOT, WEAPON_WIELD, WEAPON_SLOT, SIZE, POTION_POOL, CON, STR, DEX, WIS, INT, CHR };

std::ostream& operator <<(std::ostream& os, const ArmorSlot& s);
std::ostream& operator <<(std::ostream& os, const WeaponSlot& s);
std::ostream& operator <<(std::ostream& os, const WeaponWield& s);
std::ostream& operator <<(std::ostream& os, const Size& s);

/**
 * Item class
 */
class Item {
protected:
    int cost;
    string name;
    map<Attribute, int> stats;
public:
    int getCost() { return cost; }
    string getName() { return name; }
    map<Attribute, int> getStatsMap() { return stats; }
    
    void setCost(int c) { cost = c; }
    void setName(string n) { name = n; }
};

/**
 * Armor class, extends Item
 */
class Armor : public Item {
protected:
    int armor, dex;
    ArmorSlot slot;
    
public:
    // setters
    void setArmor(int a) { 
        armor = a; 
        stats[ARMOR_CLASS] = a;
    }
    
    void setMaxDexterity(int d) {
        dex = d; 
        stats[MAX_DEXTERITY] = d;
    }
    
    void setArmorSlot(ArmorSlot s) { 
        slot = s; 
        stats[ARMOR_SLOT] = s;
    }
    
    void setStats(Attribute a, int v) { stats[a] = v; }
    void setAllStats();
    
    // getters
    int getArmor() { return armor; }
    int getMaxDexterity() { return dex; }
    ArmorSlot getSlot() { return slot; }
    int getStats(string s);
};

/**
 * Potion class, extends Item
 */
class Potion : public Item {
public:
    int getPotionPool() { return pool; }
    void setPotionPool(int p) { pool = p; }
private:
    int pool;
};


/**
 * Weapon class, extends Item
 */
class Weapon : public Item {
protected:
    // int hardness, critical;
    WeaponWield wield;
    Size size;
public:
    // setters
    void setSize(Size s) { 
        size = s; 
        stats[SIZE] = s;
    }
    
    void setWeaponWield(WeaponWield w) { 
        wield = w; 
        stats[WEAPON_WIELD] = w;
    }
    
    virtual void setCost() = 0;
    // getters
    Size getSize() { return size; }
    WeaponWield getWeaponWield() { return wield; }
    
    virtual int getWeaponDamage() = 0;
};

/**
 * Longsword class, extends Weapon
 */
class Longsword : public Weapon {
public:
    void setCost();
    int getWeaponDamage();
};

#endif
