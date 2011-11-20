/**
 *  ChestBuilder.cpp
 *  comp345-assignment-03
 *
 */

#include "ChestBuilder.h"

void ChestBuilder::putRandomItem() {
    ItemGenerator* ig = new ItemGenerator();
    switch (roll(2)) {
    case 1:
        switch (roll(3)) {
            case 1:
                ig->setArmorBuilder(new LeatherArmorBuilder());
                ig->constructArmor("Random Leather Armor", static_cast<ArmorSlot>(roll(7)));
                break;
            case 2:
                ig->setArmorBuilder(new ChainmailArmorBuilder());
                ig->constructArmor("Random Chainmail Armor", static_cast<ArmorSlot>(roll(7)));
                break;
            case 3:
                ig->setArmorBuilder(new FullplateArmorBuilder());
                ig->constructArmor("Random Fullplate Armor", static_cast<ArmorSlot>(roll(7)));
                break;
        }
        putItem(ig->getArmor());
        break;
    case 2:
        ig->setLongswordBuilder(new LongswordBuilder());
        ig->constructLongsword("Random Longsword", static_cast<WeaponWield>(roll(2)), static_cast<Size>(roll(4, 1, 3)));
        putItem(ig->getLongsword());
        break;
    }
}

void ChestGenerator::constructChest() {
    chestBuilder->createNewChest();
    int itemCount = roll(3, 1, 2);
    for (int i = 0; i < itemCount; i++) {
        chestBuilder->putRandomItem();
    }
}