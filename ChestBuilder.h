/**
 *  ChestBuilder.h
 *  comp345-assignment-03
 *
 */

#ifndef CHESTBUILDER_H
#define CHESTBUILDER_H
#include "Chest.h"
#include "ItemBuilder.h"

class ChestBuilder {
public:
    Chest* getChest() { return chest; }
    void createNewChest() { chest = new Chest(); }
    void putItem(Item* it) { chest->putItem(it); }
    void putRandomItem();
    
private:
    Chest* chest;
};

class ChestGenerator {
public:
    void constructChest();
    void setChestBuilder(ChestBuilder* cb) { chestBuilder = cb; }
    Chest* getChest() { return chestBuilder->getChest(); }
    
private:
    ChestBuilder* chestBuilder;
};
#endif
