//
//  Item.cpp
//  comp345-project
//
//  Created by Charles Chao Yang on 11-11-07.

#include <iostream>
#include <cstdlib>
#include "Item.h"

using std::string;

int roll(int range) {
    return rand()%(range);
}

int roll(int count, int range, int modifier) {
    int rollResult;
    for (int i = 0; i < count; i++)
        rollResult += roll(range);
    return rollResult + modifier;
}      


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
        case WRIST:
            os << "Mainhand";
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
        case HUGE:
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
            setStats("INT", roll(5));
            setStats("WIS", roll(5));
            break;
        case WRIST:
            setStats("STR", roll(5));
            break;
        case FEET:
            setStats("DEX", roll(5));
            break;
        case WAIST:
            setStats("STR", roll(5));
            setStats("CON", roll(5));
            break;
        case FINGER:
            setStats("STR", roll(5));
            setStats("CON", roll(5));
            setStats("WIS", roll(5));
            setStats("CHR", roll(5));
            break;
        default:
            break;
    }
}

void Longsword::setCost() {
    switch (size) {
    case SMALL:
        cost = 15;
        break;
    case MEDIUM:
        cost = 15;
        break;
    case LARGE:
        cost = 30;
        break;
    case HUGE:
        cost = 45;
        break;
    default:
        cost = NULL;
        break;
    }
}

int Longsword::getWeaponDamage() {
    switch (size) {
        case SMALL:
            return roll(6);
            break;
        case MEDIUM:
            return roll(8);
            break;
        case LARGE:
            return roll(2, 6);
            break;
        case HUGE:
            return roll(3, 6);           
            break;
        default:
            return NULL;
            break;
    }
}