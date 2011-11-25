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
}

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

    stringstream msg;
    msg << "You've equipped " << am->getName() << " to your " << am->getSlot() << ".";
    observer->updateConsole(&msg, TRUE);
    // notify observer
    observer->updateAbility();
    observer->updateArmor();
    observer->updateInventory();
}


Armor* Character::unequipArmor(ArmorSlot as) {
    // check if the armor is empty or not
//    if (equipments[as] == NULL)
//        return NULL;
    
    Armor* am = equipments[as];
    // iterator through every stats of the armor
    // and modify the ability scores to the total
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
    
    
    stringstream msg;
    msg << "You've unequipped " << am->getName() << " from your " << am->getSlot() << ".";
    observer->updateConsole(&msg, TRUE);
    // unequip the armor in the character slot
    equipments[as] = NULL;
    // notify observer
    observer->updateAbility();
    observer->updateArmor();
    observer->updateInventory();
    
    return am;
}

void Character::setEquippedWeapon(WeaponSlot ws, Weapon* wp) {
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
}

void Character::equipWeaponFromInventory(WeaponSlot ws, int inventorySlot) {
    equipWeapon(ws, static_cast<Weapon*>(characterInventory[inventorySlot]));
    removeInventoryItem(inventorySlot);
}

void Character::equipArmorFromInventory(ArmorSlot as, int inventorySlot) {
    equipArmor(as, static_cast<Armor*>(characterInventory[inventorySlot]));
    removeInventoryItem(inventorySlot);
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
    
    stringstream msg;
    msg << "You've equipped " << wp->getName() << " to your " << ws << ".";
    observer->updateConsole(&msg, TRUE);
    // notify observer
    observer->updateAbility();
    observer->updateWeapon();
    observer->updateInventory();
}

Weapon* Character::unequipWeapon(WeaponSlot ws) {
    Weapon* am = weapons[ws];
    
    // iterator through every stats of the armor
    // and modify the ability scores to the total
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
    
    stringstream msg;
    msg << "You've unequipped " << am->getName() << " from your " << ws << ".";
    observer->updateConsole(&msg, TRUE);
    // set the equip slot to NULL
    weapons[ws] = NULL;
    // notify observer
    observer->updateAbility();
    observer->updateWeapon();
    observer->updateInventory();
    
    return am;
}


// character actions

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

void Character::usePotion(Potion* pot) {
    hitPoint += pot->getPotionPool();
    if (hitPoint > maxHitPoint) 
        hitPoint = maxHitPoint;
    pot->setPotionPool(0);
    observer->updateVital();
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

void Character::deleteEquippedArmor(ArmorSlot as) {
    delete equipments[as];
    equipments[as] = NULL;
    
    // notify observer
    observer->updateArmor();
}

void Character::deleteEquippedWeapon(WeaponSlot ws) {
    delete weapons[ws];
    weapons[ws] = NULL;
    // notify observer
    observer->updateWeapon();
}

void Character::removeInventoryItem(int index, bool notify) {
    characterInventory[index] = NULL;
    // notify observer
    if (notify)
        observer->updateInventory();
}

void Character::deleteInventoryItem(int index) {
    //delete characterInventory[index];
    removeInventoryItem(index, TRUE);
    
}

void Character::deleteInventoryItem(int index, bool notify, bool log, string msg) {
//    delete characterInventory[index];
    characterInventory[index] = NULL;
    if (notify)
        observer->updateConsole(msg, log);
    observer->updateInventory();
}

// specify index before storing
void Character::putToInventory(Item* it, int index, bool notify) {
    stringstream msg;
    bool success = FALSE;
    // notify observer
    if (characterInventory[index] == NULL) {
        characterInventory[index] = it;
        success = TRUE;
    }

    if (notify) {
        if (success) {
            msg << "You've stored " << it->getName() << " in your inventory.";
            observer->updateConsole(&msg, TRUE);
            observer->updateInventory();
            msg.str("");
            msg.clear();
        } else {
            observer->updateConsole("Error: That slot is occupied!", FALSE);
        }
    }
}

// auto store item in inventory
void Character::putInventoryItem(Item* it, bool notify) {
    stringstream msg;
    bool success = FALSE;
    for (int i = 0; i < 10; i++) {
        if (characterInventory[i] == NULL) {
            characterInventory[i] = it;
            success = TRUE;
            break;
        }
    }
    
    if (notify) {
        if (success) {
            msg << "You've stored " << it->getName() << " in your inventory.";
            observer->updateConsole(&msg, TRUE);
            observer->updateInventory();
            msg.str("");
            msg.clear();
        } else {
            observer->updateConsole("Error: Inventory is full!", FALSE);
        }
    }
}

void Character::buy(Merchant* merchant, int index) {
    if (gold >= merchant->peek(index)->getCost()) {
        if (!inventoryIsFull()) {
            gold -= merchant->peek(index)->getCost();
            putInventoryItem(merchant->getItem(index));
        } else {
            observer->updateConsole("Error: Inventory is full!", FALSE);
        }
        
    } else {
        observer->updateConsole("Error: You cannot afford that item!", FALSE);
    }
}

void Character::sell(int index) {
    stringstream msg;
    msg << (characterInventory[index])->getName() << " was sold to the vendor for " << (characterInventory[index])->getCost() << " gold.";
    gold += characterInventory[index]->getCost();
    // permanently remove the item
    deleteInventoryItem(index);
    
    observer->updateConsole(msg.str().c_str(), TRUE);
    msg.str("");
    msg.clear();
}

bool Character::inventoryIsFull() {
    for (int i = 0; i < 10; i++) {
        if (characterInventory[i] == NULL)
            return FALSE;
    }
    return TRUE;
}


