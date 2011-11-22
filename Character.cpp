/**
 *  Character.cpp
 *  comp345-assignment-03
 *
 */

#include <iostream>
#include "Character.h"

void Character::equipArmor(ArmorSlot as, Armor* am) {
    
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
    
    // notify observer
    observer->updateAbility();
    stringstream msg;
    msg << "You've equipped " << am->getName() << " to your " << am->getSlot() << " slot.";
    observer->updateConsole(&msg, TRUE);
}


Armor* Character::unequipArmor(ArmorSlot as) {
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
                abilityScores[CON] -= it->second;
                break;
            case STR:
                abilityScores[STR] -= it->second;
                break;
            case DEX:
                abilityScores[DEX] -= it->second;
                break;
            case WIS:
                abilityScores[WIS] -= it->second;
                break;
            case INT:
                abilityScores[INT] -= it->second;
                break;
            case CHR:
                abilityScores[CHR] -= it->second;
                break;
            default:
                break;
        }
    }
    
    // notify observer
    observer->updateAbility();
    stringstream msg;
    msg << "You've unequipped " << am->getName() << " from your " << am->getSlot() << " slot.";
    observer->updateConsole(&msg, TRUE);
    return am;
}

void Character::equipWeapon(WeaponSlot ws, Weapon* wp) {
    // check if the armor is empty or not
    //    if (equipments[as] == NULL)
    //        return NULL;

    weapons[ws] = wp;
    // iterator through every stats of the armor
    // and add the ability scores to the total
    // ability scores of the character
    
    map<Attribute, int>::const_iterator it;
    map<Attribute, int> stats = wp->getStatsMap();
    for (it = stats.begin(); it != stats.end(); ++it) {
        switch (it->first) {
            case ATTACK_BONUS:
                maxAttackBonus += it->second;
                break;
            case DAMAGE_BONUS:
                maxDamageBonus += it->second;
                break;
            default:
                break;
        }
    }
    
    // notify observer
    observer->updateAbility();
    stringstream msg;
    msg << "You've equipped " << wp->getName();
    observer->updateConsole(&msg, TRUE);
}

Weapon* Character::unequipWeapon(WeaponSlot ws) {
    // check if the armor is empty or not
    //    if (equipments[as] == NULL)
    //        return NULL;
    
    Weapon* am = weapons[ws];
    // iterator through every stats of the armor
    // and add the ability scores to the total
    // ability scores of the character
    
    map<Attribute, int>::const_iterator it;
    map<Attribute, int> stats = am->getStatsMap();
    for (it = stats.begin(); it != stats.end(); ++it) {
        switch (it->first) {
            case ATTACK_BONUS:
                maxAttackBonus -= it->second;
                break;
            case DAMAGE_BONUS:
                maxDamageBonus -= it->second;
                break;
            default:
                break;
        }
    }
    
    // notify observer
    observer->updateAbility();
    stringstream msg;
    msg << "You've unequipped " << am->getName();
    observer->updateConsole(&msg, TRUE);
    return am;
}

void Character::levelUp() {
    setLevel(getLevel() + 1);
    int hp = getMaxHitPoint() + roll(10) + toModifier(getAbilityScore(CON));
    setMaxHitPoint(hp);
    setHitPoint(hp);
    setMaxAttackBonus(getMaxAttackBonus() + 1);
    
    // notify character observer
    observer->updateBasic();
    observer->updateVital();
    observer->updateAbility();
    stringstream msg;
    msg << "**Congratulation!** You've reached level " << level << ".";
    observer->updateConsole(&msg, TRUE);
}

//enum ArmorSlot { HEAD = 1, CHEST, HANDS, FEET, WAIST, WRIST, FINGER };
//enum Size { FINE, DIMINUTIVE, TINY, SMALL, MEDIUM, BUGE, LARGE, GARGANTUAN, COLOSSAL};
//enum WeaponSlot { MAINHAND = 1, OFFHAND };
//enum WeaponWield { ONEHAND = 1, TWOHAND };
//enum Attribute { ARMOR_CLASS = 20, MAX_DEXTERITY, ARMOR_SLOT, WEAPON_WIELD, WEAPON_SLOT, SIZE, POTION_POOL, CON, STR, DEX, WIS, INT, CHR, ATTACK_BONUS, DAMAGE_BONUS, CRITICAL };
void Character::wipeAllContainer() {
    // equipements
    equipments[HEAD] = NULL;
    equipments[CHEST] = NULL;
    equipments[HANDS] = NULL;
    equipments[FEET] = NULL;
    equipments[WAIST] = NULL;
    equipments[WRIST] = NULL;
    equipments[FINGER] = NULL;
    
    // weapons
    weapons[MAINHAND] = NULL;
    weapons[OFFHAND] = NULL;
    
    // inventory
    for (int i = 0; i < 10; i++)
        characterInventory[i] = NULL;
}

int Character::emptyInventorySlot() {
    int free = 0;
    for (int i = 0; i < 10; i++) {
        if (characterInventory[i] == NULL)
            free++;
    }
    
    return free;
}