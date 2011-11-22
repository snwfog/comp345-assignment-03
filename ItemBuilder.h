/**
 *  ItemBuilder.h
 *  comp345-assignment-03
 * 
 *  ItemBuilder class reponsible of builder all of the Item
 *  objects used in the game.
 */

#ifndef ITEMBUILDER_H
#define ITEMBUILDER_H

#include <string>
#include "Item.h"
using std::string;

class ItemBuilder {
public:
    virtual void createNewItem() = 0;
};

class ArmorBuilder : public ItemBuilder {
public:
    Armor* getArmor() { return armor; }
    void createNewItem() { armor = new Armor(); }
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
    void buildLongsword(string name, WeaponWield wield, Size size);
};

class PotionBuilder : public ItemBuilder {
protected:
    Potion* pot;
public:
    Potion* getPotion() { return pot; }
    void createNewItem() { pot = new Potion(); }
    void buildPotion(string name, int pool);
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
