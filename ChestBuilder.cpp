/**
 *  ChestBuilder.cpp
 *  comp345-assignment-03
 *
 */

#include "ChestBuilder.h"
#include "ItemBuilder.h"

void ChestGenerator::constructChest() {
    chestBuilder->createNewChest();
    ItemGenerator* ig = new ItemGenerator();
    int itemCount = roll(3, 1, 2);
    for (int i = 0; i < itemCount; i++) {
        chestBuilder->putItem(ig->getRandomItem());
    }
}