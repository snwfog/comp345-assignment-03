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

void LongswordBuilder::buildLongsword(string name, WeaponWield wield, Size size) {
    longsword->setName(name);
    longsword->setWeaponWield(wield);
    longsword->setSize(size);
    longsword->setCost();
    longsword->setAttackBonus(roll(5));
    longsword->setDamageBonus(roll(5));
    longsword->setItemType(IS_WEAPON);
}

void PotionBuilder::buildPotion(string name, int pool) {
    pot->setName(name);
    pot->setPotionPool(pool);
    pot->setItemType(IS_POTION);
}


void ItemGenerator::constructArmor(string name, ArmorSlot slot) {
    armorBuilder->createNewItem();
    armorBuilder->buildArmor(name, slot);
}

void ItemGenerator::constructLongsword(string name, WeaponWield wield, Size size) {
    longswordBuilder->createNewItem();
    longswordBuilder->buildLongsword(name, wield, size);
}

void ItemGenerator::constructPotion(Size s) {
    string os;
    int pool;
    switch (s) {
        case FINE:
            os = "Fine Healing Potion";
            pool = 3;
            break;
        case DIMINUTIVE:
            os = "Diminutive Healing Potion";
            pool = 5;
            break;
        case TINY:
            os = "Tiny Healing Potion";
            pool = 8;
            break;
        case SMALL:
            os = "Small Healing Potion";
            pool = 12;
            break;
        case MEDIUM:
            os = "Medium Healing Potion";
            pool = 17;
            break;
        case LARGE:
            os = "Large Healing Potion";
            pool = 23;
            break;
        case BUGE:
            os = "Huge Healing Potion";
            pool = 30;
            break;
        case GARGANTUAN:
            os = "Gargantuan Healing Potion";
            pool = 38;
            break;
        case COLOSSAL:
            os = "Colossal Healing Potion";
            pool = 47;
            break;
        default:
            os = "Atomic Healing Potion";
            pool = 100;
            break;
    }
    potionBuilder->createNewItem();
    potionBuilder->buildPotion(os, pool);
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
            setLongswordBuilder(new LongswordBuilder());
            constructLongsword();
            randomItem = getLongsword();
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

