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

enum Size { FINE = 1, DIMINUTIVE, TINY, SMALL, MEDIUM,
            LARGE, HUGE, GARGANTUAN, COLOSSAL };

enum ArmorSlot { HEAD = 1, CHEST, HANDS, FEET, 
                 WAIST, WRIST, FINGER } ;

enum WeaponSlot { MAINHAND = 1, OFFHAND };
enum WeaponWield { ONEHAND = 1, TWOHAND };

std::ostream& operator <<(std::ostream& os, const ArmorSlot& s);
std::ostream& operator <<(std::ostream& os, const WeaponSlot& s);
std::ostream& operator <<(std::ostream& os, const WeaponWield& s);
std::ostream& operator <<(std::ostream& os, const Size& s);


// d20 roll functions
int roll(int range);
int roll(int range, int count, int modifier = 0);

class Item {
protected:
    int cost;
    string name;
    map<string, int> stats;
public:
    int getCost() { return cost; }
    string getName() { return name; }
    map<string, int> getStatsMap() { return stats; }
    
    void setCost(int c) { 
        cost = c; 
        stats["Cost"] = c;
    }
    void setName(string n) { name = n; }
};


class Armor : public Item {
protected:
    int armor, dex;
    ArmorSlot slot;
    
public:
    // setters
    void setArmor(int a) { 
        armor = a; 
        stats["Armor"] = a;
    }
    
    void setMaxDexterity(int d) {
        dex = d; 
        stats["Max. Dexterity"] = d;
    }
    
    void setArmorSlot(ArmorSlot s) { 
        slot = s; 
        stats["Slot"] = s;
    }
    
    void setStats(string s, int v) { stats[s] = v; }
    void setAllStats();
    
    // getters
    int getArmor() { return armor; }
    int getMaxDexterity() { return dex; }
    ArmorSlot getSlot() { return slot; }
    int getStats(string s);
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
    void setSize(Size s) { 
        size = s; 
        stats["Size"] = s;
    }
    
    void setWeaponWield(WeaponWield w) { 
        wield = w; 
        stats["Wield"] = w;
    }
    
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
