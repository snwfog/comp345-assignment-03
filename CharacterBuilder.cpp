/**
 *  CharacterBuilder.cpp
 *  comp345-assignment-03
 *
 */

#include <iostream>
#include "CharacterBuilder.h"
#include "Function.h"

void CharacterBuilder::setBaseAbilityScore(Attribute* at) {
    
    // temporary ability scores arrays
    int tmp[6];
    // roll for the 6 primary ability scores
    for (int i = 0; i < 6; i++)
        tmp[i] = rollBaseStats();
    
    // distributes them accordinly
    int* largest;
    for (int i = 0; i < 6; i++) {
        largest = &tmp[i];
        for (int j = 0; j < 6; j++) {
            if (tmp[j] > *largest)
                largest = &tmp[j];
        }
        
        character->setAbilityScore(static_cast<Attribute>(at[i]), *largest);
        *largest = 0;
    }
    character->setAbilityRanks(at);
}

void CharacterBuilder::levelUp() {
    character->setLevel(character->getLevel() + 1);
    int hp = character->getHitPoint() + roll(10) + toModifier(character->getAbilityScore(CON));
    character->setMaxHitPoint(hp);
    character->setHitPoint(hp);
    character->levelUp(); // notify observers
}

void BullyBuilder::initializeCharacterType() {
    Attribute abilityRanks[] = { STR, CON, DEX, INT, CHR, WIS };
    
    character->setCharacterClass("Bully");
    character->setLevel(1);
    setBaseAbilityScore(&(abilityRanks[0]));
    character->setHitPoint(roll(10) + toModifier(character->getAbilityScore(CON)));
    character->setMaxHitPoint(character->getHitPoint());
    character->setManaPoint(0);
    character->setMaxManaPoint(character->getManaPoint());
}

void NimbleBuilder::initializeCharacterType() {
    Attribute abilityRanks[] = { DEX, CON, STR, INT, CHR, WIS };
    
    character->setCharacterClass("Nimble");
    character->setLevel(1);
    setBaseAbilityScore(&(abilityRanks[0]));
    character->setHitPoint(roll(10) + toModifier(CON));
    character->setMaxHitPoint(character->getHitPoint());
    character->setManaPoint(0);
    character->setMaxManaPoint(character->getManaPoint());
}

void TankBuilder::initializeCharacterType() {
    Attribute abilityRanks[] = { CON, DEX, STR, INT, CHR, WIS };
    
    character->setCharacterClass("Tank");
    character->setLevel(1);
    setBaseAbilityScore(&(abilityRanks[0]));
    character->setHitPoint(roll(10) + toModifier(CON));
    character->setMaxHitPoint(character->getHitPoint());
    character->setManaPoint(0);
    character->setMaxManaPoint(character->getManaPoint());
}

void FighterGenerator::createNewFighter() {
    characterBuilder->createNewCharacter();
    characterBuilder->initializeCharacterType();
}

void FighterGenerator::createNewFighter(string name) {
    characterBuilder->createNewCharacter();
    characterBuilder->getCharacter()->setName(name);
    characterBuilder->initializeCharacterType();
}
