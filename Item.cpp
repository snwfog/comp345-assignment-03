/**
 *  Item.cpp
 *  comp345-assignment-03
 *  // Should fix some of the switch cases and handle them in 
 *  // the builder file.
 */

#include <iostream>
#include <cstdlib>
#include "Item.h"

using std::string;

// overloaded << operator for ENUM to string conversion
std::ostream& operator <<(std::ostream& os, const ArmorSlot& s) {
    switch (s) {
        case HEAD:
            os << "Head";
            break;
        case CHEST:
            os << "Chest";
            break;
        case HANDS:
            os << "Hands";
            break;
        case FEET:
            os << "Feet";
            break;
        case WAIST:
            os << "Waist";
            break;
        case FINGER:
            os << "Finger";
            break;
        default:
            os << "Unknown Armor Slot";
            break;
    }
    return os;
}

std::ostream& operator <<(std::ostream& os, const WeaponSlot& s) {
    switch (s) {
        case MAINHAND:
            os << "Mainhand";
            break;
        case OFFHAND:
            os << "Offhand";
            break;
        default:
            os << "Unknown Weapon Slot";
            break;
    }
    return os;
}

std::ostream& operator <<(std::ostream& os, const Size& s) {
    switch (s) {
        case FINE:
            os << "Fine";
            break;
        case DIMINUTIVE:
            os << "Diminutive";
            break;
        case TINY:
            os << "Tiny";
            break;
        case SMALL:
            os << "Small";
            break;
        case MEDIUM:
            os << "Medium";
            break;
        case LARGE:
            os << "Large";
            break;
        case BUGE:
            os << "Huge";
            break;
        case GARGANTUAN:
            os << "Gargantuan";
            break;
        case COLOSSAL:
            os << "Colossal";
            break;
        default:
            os << "Atomic";
            break;
    }
    
    return os;
}

std::ostream& operator <<(std::ostream& os, const WeaponWield& s) {
    switch (s) {
        case ONEHAND:
            os << "One-handed";
            break;
        case TWOHAND:
            os << "Two-handed";
            break;
        default:
            os << "Three-handed";
            break;
    }
    return os;
}

void Armor::setAllStats() {
    switch (slot) {
        case HEAD:
            setStats(INT, roll(5));
            setStats(WIS, roll(5));
            break;
        case FEET:
            setStats(DEX, roll(5));
            break;
        case WAIST:
            setStats(STR, roll(5));
            setStats(CON, roll(5));
            break;
        case FINGER:
            setStats(STR, roll(5));
            setStats(CON, roll(5));
            setStats(WIS, roll(5));
            setStats(CHR, roll(5));
            break;
        default:
            break;
    }
}

void Weapon::setAllStats() {
    setAttackBonus(roll(10));
    setDamageBonus(roll(10));
}

void Longsword::setCost() {
    switch (size) {
    case FINE:
        cost = 5;
        break;
    case DIMINUTIVE:
        cost = 8;
        break;
    case TINY:
        cost = 10;
        break;
    case SMALL:
        cost = 15;
        break;
    case MEDIUM:
        cost = 15;
        break;
    case LARGE:
        cost = 30;
        break;
    case BUGE:
        cost = 45;
        break;
    case GARGANTUAN:
        cost = 60;
        break;
    case COLOSSAL:
        cost = 75;
        break;
    default:
        cost = 10000;
        break;
    }
}

int Longsword::getWeaponDamage() {
    switch (size) {
        case FINE:
            return roll(2);
            break;
        case DIMINUTIVE:
            return roll(3);
            break;
        case TINY:
            return roll(4);
            break;
        case SMALL:
            return roll(6);
            break;
        case MEDIUM:
            return roll(8);
            break;
        case LARGE:
            return roll(2, 6);
            break;
        case BUGE:
            return roll(3, 6);           
            break;
        case GARGANTUAN:
            return roll(4, 6);
            break;
        case COLOSSAL:
            return roll(6, 6);
            break;
        default:
            return NULL;
            break;
    }
}

int Weapon::getSizeModifier() {
    switch (size) {
        case FINE:
            return 8;
            break;
        case DIMINUTIVE:
            return 4;
            break;
        case TINY:
            return 2;
            break;
        case SMALL:
            return 1;
            break;
        case MEDIUM:
            return 0;
            break;
        case LARGE:
            return -1;
            break;
        case BUGE:
            return -2;
            break;
        case GARGANTUAN:
            return -4;
            break;
        case COLOSSAL:
            return -8;
            break;
    }
}