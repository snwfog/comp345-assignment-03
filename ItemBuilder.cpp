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
    pot->setName("Small Healing Potion");
    pot->setPotionPool(10);
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

