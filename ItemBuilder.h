//
//  ItemBuilder.h
//  comp345-assignment-03
//
//  Created by Charles Chao Yang on 11-11-17.

#ifndef ITEMBUILDER_H
#define ITEMBUILDER_H

#include <string>
#include "Item.h"
using std::string;

class ItemBuilder {
public:
    virtual void createNewItem() = 0;
    virtual void setName(string itemName) = 0;
    virtual void setCost(int itemCost) = 0;
};

class ArmorBuilder : public ItemBuilder {
public:
    Armor* getArmor() { return armor; }
    void createNewItem() { armor = new Armor(); }
    void setName(string name) { armor->setName(name); }
    void setCost(int cost) { armor->setCost(cost); }
    void setArmorSlot(ArmorSlot slot) { armor->setArmorSlot(slot); }
    virtual void buildArmor(string name, ArmorSlot slot) = 0;
protected:
    Armor* armor;
};

class LeatherArmorBuilder : public ArmorBuilder {
public:
    void buildArmor(string name, ArmorSlot slot);
};

class ChainmailArmorBuilder : public ArmorBuilder {
public:
    void buildArmor(string name, ArmorSlot slot);
};

class FullplateArmorBuilder : public ArmorBuilder {
public:
    void buildArmor(string name, ArmorSlot slot);
};

class LongswordBuilder : public ItemBuilder {
protected:
    Longsword* longsword;
public:
    Longsword* getWeapon() { return longsword; }
    void createNewItem() { longsword = new Longsword(); }
    void setName(string name) { longsword->setName(name); }
    void setCost(int cost) { longsword->setCost(); }
    void setWeaponSize(Size size) { longsword->setSize(size); }
    void setWield(WeaponWield wield) { longsword->setWeaponWield(wield); }
    void buildLongsword(string name, WeaponWield wield, Size size);
};


class ItemGenerator {
public:
    // armor builder
    void setArmorBuilder(ArmorBuilder* ab) { armorBuilder = ab; }
    Armor* getArmor() { return armorBuilder->getArmor(); }
    void constructArmor(string name, ArmorSlot slot);
    
    // longsword builder
    void setLongswordBuilder(LongswordBuilder* lsb) { longswordBuilder = lsb; }
    Longsword* getLongsword() { return longswordBuilder->getWeapon(); }
    void constructLongsword(string name, WeaponWield wield, Size size);
    
private:
    ArmorBuilder* armorBuilder;
    LongswordBuilder* longswordBuilder;
    
};

#endif
