/**
 *  CharacterBuilder.cpp
 *  comp345-assignment-03
 *
 */

#include <iostream>
#include "CharacterBuilder.h"
#include "Function.h"

// set the ability scores of the character
// based on the input parameter attributes
// rank array
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

void BullyBuilder::initializeCharacter() {
    Attribute abilityRanks[] = { STR, CON, DEX, INT, CHR, WIS };
    
    character->setCharacterClass("Bully");
    character->setLevel(1);
    character->setMaxAttackBonus(1);
    character->setMaxDamageBonus(1);
    setBaseAbilityScore(abilityRanks);
    character->setHitPoint(roll(10) + toModifier(character->getAbilityScore(CON)));
    character->setMaxHitPoint(character->getHitPoint());
    character->setManaPoint(0);
    character->setMaxManaPoint(character->getManaPoint());
    character->wipeAllContainer();
    
    
    // testing gears
    ItemGenerator* ig = new ItemGenerator();
    ig->setArmorBuilder(new FullplateArmorBuilder());
    ig->constructArmor("Testing Fullplate", HEAD);
    character->setInventoryItem(0, ig->getArmor());
    ig->setLongswordBuilder(new LongswordBuilder());
    ig->constructLongsword("Testing Longsword", ONEHAND, MEDIUM);
    character->setInventoryItem(1, ig->getLongsword());
    ig->constructLongsword("Ashkandii Greater Sword", TWOHAND, BUGE);
    character->setEquippedWeapon(MAINHAND, ig->getLongsword());
}

void NimbleBuilder::initializeCharacter() {
    Attribute abilityRanks[] = { DEX, CON, STR, INT, CHR, WIS };
    
    character->setCharacterClass("Nimble");
    character->setLevel(1);
    character->setMaxAttackBonus(1);
    character->setMaxDamageBonus(1);
    setBaseAbilityScore(abilityRanks);
    character->setHitPoint(roll(10) + toModifier(CON));
    character->setMaxHitPoint(character->getHitPoint());
    character->setManaPoint(0);
    character->setMaxManaPoint(character->getManaPoint());
    character->wipeAllContainer();
}

void TankBuilder::initializeCharacter() {
    Attribute abilityRanks[] = { CON, DEX, STR, INT, CHR, WIS };
    
    character->setCharacterClass("Tank");
    character->setLevel(1);
    character->setMaxAttackBonus(1);
    character->setMaxDamageBonus(1);
    setBaseAbilityScore(abilityRanks);
    character->setHitPoint(roll(10) + toModifier(CON));
    character->setMaxHitPoint(character->getHitPoint());
    character->setManaPoint(0);
    character->setMaxManaPoint(character->getManaPoint());
    character->wipeAllContainer();
}

void FighterGenerator::createNewFighter() {
    characterBuilder->createNewCharacter();
    characterBuilder->initializeCharacter();
}

void FighterGenerator::createNewFighter(string name) {
    characterBuilder->createNewCharacter();
    characterBuilder->getCharacter()->setName(name);
    characterBuilder->initializeCharacter();
}
