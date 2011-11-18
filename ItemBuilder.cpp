//
//  ItemBuilder.cpp
//  comp345-assignment-03
//
//  Created by Charles Chao Yang on 11-11-17.

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
    
}

void ChainmailArmorBuilder::buildArmor(string name, ArmorSlot slot) {
    armor->setName(name);
    armor->setCost(150);
    armor->setArmorSlot(slot);
    armor->setArmor(5);
    armor->setMaxDexterity(2);
    armor->setAllStats();
}

void FullplateArmorBuilder::buildArmor(string name, ArmorSlot slot) {
    armor->setName(name);
    armor->setCost(1500);
    armor->setArmorSlot(slot);
    armor->setArmor(8);
    armor->setMaxDexterity(1);
    armor->setAllStats();
}

void LongswordBuilder::buildWeapon(string name, WeaponWield wield, Size size) {
    longsword->setName(name);
    longsword->setWeaponWield(wield);
    longsword->setSize(size);
    longsword->setCost();
}

void ItemGenerator::constructArmor(string name, ArmorSlot slot) {
    armorBuilder->createNewItem();
    armorBuilder->buildArmor(name, slot);
    armorBuilder->setAllStats(slot);
}

void ItemGenerator::constructLongsword(string name, WeaponWield wield, Size size) {
    longswordBuilder->createNewItem();
    longswordBuilder->buildWeapon(name, wield, size);
}

