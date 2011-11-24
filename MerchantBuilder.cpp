/**
 *  MerchantBuilder.cpp
 *  comp345-assignment-03
 *
 */
#include <iostream>
#include "MerchantBuilder.h"
#include "ItemBuilder.h"

void MerchantBuilder::fillMerchantStach() {
    // create local item generator
    ItemGenerator* ig = new ItemGenerator();
    // IMPORTANT HERE ONLY UPDATE 9 ITEMS FROM MERCHANT!!
    for (int i = 0; i < 9; i++) {
        merchant->putItem(ig->getRandomItem());
    }
}