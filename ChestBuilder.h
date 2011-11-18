//
//  ChestBuilder.h
//  comp345-assignment-03

#ifndef CHESTBUILDER_H
#define CHESTBUILDER_H
#include "Chest.h"

class ChestBuilder {
public:
    Chest* getChest() { return chest; }
    void buildNewChest();
    
private:
    Chest* chest;
}


#endif
