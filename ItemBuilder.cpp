/**
 *  ItemBuilder.cpp
 *  comp345-assignment-03
 *
 */

#include <iostream>
#include "ItemBuilder.h"
//enum Slot { CHEST, HANDS, FEET, WAIST, HEAD, 
//WRIST, FINGER, MAINHAND, OFFHAND };


void LeatherArmorBuilder::buildArmor(string name, ArmorSlot slot) {
    armor->setName(name);
    armor->setCost(10);
    armor->setArmorSlot(slot);
    armor->setArmor(2);
    armor->setMaxDexterity(6);
    armor->setAllStats();
    armor->setItemType(IS_ARMOR);
    
}

void ChainmailArmorBuilder::buildArmor(string name, ArmorSlot slot) {
    armor->setName(name);
    armor->setCost(150);
    armor->setArmorSlot(slot);
    armor->setArmor(5);
    armor->setMaxDexterity(2);
    armor->setAllStats();
    armor->setItemType(IS_ARMOR);
}

void FullplateArmorBuilder::buildArmor(string name, ArmorSlot slot) {
    armor->setName(name);
    armor->setCost(1500);
    armor->setArmorSlot(slot);
    armor->setArmor(8);
    armor->setMaxDexterity(1);
    armor->setAllStats();
    armor->setItemType(IS_ARMOR);
}

void LongswordBuilder::buildWeapon(string name, WeaponWield wield, Size size) {
    longsword->setName(name);
    longsword->setWeaponWield(wield);
    longsword->setSize(size);
    longsword->setCost();
    longsword->setAttackBonus(roll(5));
    longsword->setDamageBonus(roll(5));
    longsword->setItemType(IS_WEAPON);
    longsword->setWeaponType(IS_MELEE);
}

void LongbowBuilder::buildWeapon(string name, WeaponWield wield, Size size) {
    longbow->setName(name);
    longbow->setWeaponWield(wield);
    longbow->setSize(size);
    longbow->setCost();
    longbow->setAttackBonus(roll(5));
    longbow->setDamageBonus(roll(5));
    longbow->setItemType(IS_WEAPON);
    longbow->setWeaponType(IS_RANGE);
}

void PotionBuilder::buildPotion(string name, int pool, int cost) {
    pot->setName(name);
    pot->setCost(cost);
    pot->setPotionPool(pool);
    pot->setItemType(IS_POTION);
}


void ItemGenerator::constructArmor(string name, ArmorSlot slot) {
    armorBuilder->createNewItem();
    armorBuilder->buildArmor(name, slot);
}

void ItemGenerator::constructWeapon(string name, WeaponWield wield, Size size) {
    weaponBuilder->createNewItem();
    weaponBuilder->buildWeapon(name, wield, size);
}

void ItemGenerator::constructPotion(Size s) {
    string os;
    int pool;
    int cost;
    switch (s) {
        case FINE:
            os = "Fine Healing Potion";
            pool = 3;
            cost = 1;
            break;
        case DIMINUTIVE:
            os = "Diminutive Healing Potion";
            pool = 5;
            cost = 3;
            break;
        case TINY:
            os = "Tiny Healing Potion";
            pool = 8;
            cost = 5;
            break;
        case SMALL:
            os = "Small Healing Potion";
            pool = 12;
            cost = 10;
            break;
        case MEDIUM:
            os = "Medium Healing Potion";
            pool = 17;
            cost = 15;
            break;
        case LARGE:
            os = "Large Healing Potion";
            pool = 23;
            cost = 18;
            break;
        case BUGE:
            os = "Huge Healing Potion";
            pool = 30;
            cost = 23;
            break;
        case GARGANTUAN:
            os = "Gargantuan Healing Potion";
            pool = 38;
            cost = 30;
            break;
        case COLOSSAL:
            os = "Colossal Healing Potion";
            pool = 47;
            cost = 45;
            break;
        default:
            os = "Atomic Healing Potion";
            pool = 100;
            cost = 100;
            break;
    }
    potionBuilder->createNewItem();
    potionBuilder->buildPotion(os, pool, cost);
}

Item* ItemGenerator::getRandomItem() {
    Item* randomItem;
    switch (roll(3)) {
        case 1: // armor
            switch (roll(3)) {
                case 1:
                    setArmorBuilder(new LeatherArmorBuilder());
                    constructArmor("Random Leather Armor", static_cast<ArmorSlot>(roll(6)));
                    break;
                case 2:
                    setArmorBuilder(new ChainmailArmorBuilder());
                    constructArmor("Random Chainmail Armor", static_cast<ArmorSlot>(roll(6)));
                    break;
                case 3:
                    setArmorBuilder(new FullplateArmorBuilder());
                    constructArmor("Random Fullplate Armor", static_cast<ArmorSlot>(roll(6)));
                    break;
                default:
                    break;
            }
            randomItem = getArmor();
            break;
        case 2:
            switch (roll(2)) {
                case 1:
                    setWeaponBuilder(new LongswordBuilder());
                    constructWeapon("Random Longsword", static_cast<WeaponWield>(roll(2)), static_cast<Size>(roll(9)));
                    randomItem = getWeapon();
                    break;
                case 2:
                    setWeaponBuilder(new LongbowBuilder());
                    constructWeapon("Random Longbow", TWOHAND, MEDIUM);
                    randomItem = getWeapon();
                    break;
                default:
                    break;
            }
            break;
        case 3:
            setPotionBuilder(new PotionBuilder());
            constructPotion();
            randomItem = getPotion();
            break;
        default:
            break;
    }
    return randomItem;
}

