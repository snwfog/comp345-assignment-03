/**
 *  ItemBuilder.h
 *  comp345-assignment-03
 * 
 *  ItemBuilder class reponsible of builder all of the Item
 *  objects used in the game.
 */

#ifndef ITEMBUILDER_H
#define ITEMBUILDER_H
#include <sstream>
#include <string>
#include "Item.h"
using std::string;
using std::stringstream;

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
    void buildArmor(string name = "Random Leather Armor", ArmorSlot slot = static_cast<ArmorSlot>(roll(6)));
};

class ChainmailArmorBuilder : public ArmorBuilder {
public:
    void buildArmor(string name = "Random Chainmail Armor", ArmorSlot slot = static_cast<ArmorSlot>(roll(6)));
};

class FullplateArmorBuilder : public ArmorBuilder {
public:
    void buildArmor(string name = "Random Fullplate Armor", ArmorSlot slot = static_cast<ArmorSlot>(roll(6)));
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
    void buildPotion(string name, int pool, int cost);
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
    void constructLongsword(string name = "Random Longsword", WeaponWield wield = static_cast<WeaponWield>(roll(2)), Size size = static_cast<Size>(roll(9)));
    
    // potion builder
    void setPotionBuilder(PotionBuilder* pb) { potionBuilder = pb; }
    Potion* getPotion() { return potionBuilder->getPotion(); }
    void constructPotion(Size s = static_cast<Size>(roll(4, 1, 3))); // between small to huge
    
    // random item builder
    Item* getRandomItem();
    
private:
    ArmorBuilder* armorBuilder;
    LongswordBuilder* longswordBuilder;
    PotionBuilder* potionBuilder;
    
};

#endif
