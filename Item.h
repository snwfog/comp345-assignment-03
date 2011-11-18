//
//  Item.h
//  comp345-project
//
//  Created by Charles Chao Yang on 11-11-07.

#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <map>

using std::string;
using std::map;

enum Size {
    FINE = 8,
    DIMINUTIVE = 4, 
    TINY = 2,
    SMALL = 1,
    MEDIUM = 0,
    LARGE = -1,
    HUGE = -2,
    GARGANTUAN = -4,
    COLOSSAL = -8
};

enum ArmorSlot { HEAD, CHEST, HANDS, FEET, 
    WAIST, WRIST, FINGER } ;
enum WeaponSlot { MAINHAND, OFFHAND };
enum WeaponWield { ONEHAND, TWOHAND };

std::ostream& operator <<(std::ostream& os, const ArmorSlot& s);
std::ostream& operator <<(std::ostream& os, const WeaponSlot& s);
std::ostream& operator <<(std::ostream& os, const WeaponWield& s);
std::ostream& operator <<(std::ostream& os, const Size& s);


// d20 roll functions
int roll(int range);
int roll(int count, int range, int modifier = 0);

class Item {
protected:
    int cost;
    string name;
public:
    int getCost() { return cost; }
    string getName() { return name; }
    
    void setCost(int c) { cost = c; }
    void setName(string n) { name = n; }
    
};


class Armor : public Item {
private:
    int armor, dex;
    ArmorSlot slot;
    map<string, int> stats;
    
public:
    // setters
    void setArmor(int a) { armor = a; }
    void setMaxDexterity(int d) { dex = d; }
    void setArmorSlot(ArmorSlot s) { slot = s; }
    void setStats(string s, int v) { stats[s] = v; }
    void setAllStats();
    
    // getters
    int getArmor() { return armor; }
    int getMaxDexterity() { return dex; }
    ArmorSlot getSlot() { return slot; }
    virtual int getStats(string s);
};

//class Potion : public Item {
//public:
//    Potion() : Item("Healing Potion", 2), pool(0) {}
//    Potion(int s) : Item("Healing Potion", 2), pool(s) {}
//    int get_healing_amount() { return pool; }
//    
//    friend std::ostream& operator <<(std::ostream& ostream, const Potion& item) {
//        ostream << "[Healing Potion][Maximum HP: " << item.pool << "]";
//        return ostream;
//    }
//    
//private:
//    int pool;
//};

class Weapon : public Item {
protected:
    // int hardness, critical;
    WeaponWield wield;
    Size size;
public:
    // setters
    void setSize(Size s) { size = s; }
    void setWeaponWield(WeaponWield w) { wield = w; }
    virtual void setCost() = 0;
    // getters
    Size getSize() { return size; }
    WeaponWield getWeaponWield() { return wield; }
    
    virtual int getWeaponDamage() = 0;
};

class Longsword : public Weapon {
public:
    void setCost();
    int getWeaponDamage();
};

#endif
