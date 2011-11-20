/**
 *  Character.cpp
 *  comp345-assignment-03
 *
 */

#include <iostream>
#include "Character.h"

void Character::setEquippedArmor(ArmorSlot as, Armor* am) {
    
    // put the armor at the right slot
    equipments[as] = am;
    
    // iterator through every stats of the armor
    // and add the ability scores to the total
    // ability scores of the character
    
    map<Attribute, int>::const_iterator it;
    map<Attribute, int> stats = am->getStatsMap();
    for (it = stats.begin(); it != stats.end(); ++it) {
        switch (it->first) {
            case CON:
                abilityScores[CON] += it->second;
                break;
            case STR:
                abilityScores[STR] += it->second;
                break;
            case DEX:
                abilityScores[DEX] += it->second;
                break;
            case WIS:
                abilityScores[WIS] += it->second;
                break;
            case INT:
                abilityScores[INT] += it->second;
                break;
            case CHR:
                abilityScores[CHR] += it->second;
                break;
            default:
                break;
        }
    }
    
    // NOTIFY OBSEVER!!!!
}


Armor* Character::getEquippedArmor(ArmorSlot as) {
    // check if the armor is empty or not
//    if (equipments[as] == NULL)
//        return NULL;
    
    Armor* am = equipments[as];
    // iterator through every stats of the armor
    // and add the ability scores to the total
    // ability scores of the character
    
    map<Attribute, int>::const_iterator it;
    map<Attribute, int> stats = am->getStatsMap();
    for (it = stats.begin(); it != stats.end(); ++it) {
        switch (it->first) {
            case CON:
                abilityScores[CON] += it->second;
                break;
            case STR:
                abilityScores[STR] += it->second;
                break;
            case DEX:
                abilityScores[DEX] += it->second;
                break;
            case WIS:
                abilityScores[WIS] += it->second;
                break;
            case INT:
                abilityScores[INT] += it->second;
                break;
            case CHR:
                abilityScores[CHR] += it->second;
                break;
            default:
                break;
        }
    }
    
    // NOTIFY OBSEVER!!!!
    return am;
}

void Character::levelUp() {
    // NOTIFY OBSERVERS!
}