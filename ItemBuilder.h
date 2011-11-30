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

class ShieldBuilder : public ItemBuilder {
protected:
    Shield* shield;
public:
    Shield* getShield() { return shield; }
    void createNewItem() { shield = new Shield(); }
    virtual void buildShield(string) = 0;
};

class BucklerBuilder : public ShieldBuilder {
    void buildShield(string);
};

class HeavyShield : public ShieldBuilder {
    void buildShield(string);
};

class TowerShield : public ShieldBuilder {
    void buildShield(string);
};

class WeaponBuilder : public ItemBuilder {
protected:
    Weapon* weapon;
public:
    virtual Weapon* getWeapon() = 0;
    virtual void createNewItem() = 0;
    virtual void buildWeapon(string, WeaponWield, Size) = 0;
};

class LongswordBuilder : public WeaponBuilder {
private:
    Longsword* longsword;
public:
    Longsword* getWeapon() { return longsword; }
    void createNewItem() { longsword = new Longsword(); }
    void buildWeapon(string, WeaponWield, Size);
};

class LongbowBuilder : public WeaponBuilder {
protected:
    Longbow* longbow;
public:
    Longbow* getWeapon() { return longbow; }
    void createNewItem() { longbow = new Longbow(); }
    void buildWeapon(string, WeaponWield, Size);
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
    
    // weapon builder
    void setWeaponBuilder(WeaponBuilder* wpb) { weaponBuilder = wpb; }
    Weapon* getWeapon() { return weaponBuilder->getWeapon(); }
    void constructWeapon(string name, WeaponWield wield, Size size);
    
    // potion builder
    void setPotionBuilder(PotionBuilder* pb) { potionBuilder = pb; }
    Potion* getPotion() { return potionBuilder->getPotion(); }
    void constructPotion(Size s = static_cast<Size>(roll(4, 1, 3))); // between small to huge
    
    // shield builder
    void setShieldBuilder(ShieldBuilder* shb) { shieldBuilder = shb; }
    Shield* getShield() { return shieldBuilder->getShield(); }
    void constructShield(string name);
    

    // random item builder
    Item* getRandomItem();
    
private:
    ArmorBuilder* armorBuilder;
    WeaponBuilder* weaponBuilder;
    ShieldBuilder* shieldBuilder;
    PotionBuilder* potionBuilder;
    
};

#endif
