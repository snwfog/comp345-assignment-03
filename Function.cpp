/**
 *  Function.cpp
 *  comp345-assignment-03
 *
 */

#include <iostream>
#include "Functions.h"

int roll(int range) {
    return rand()%(range) + 1;
}

int roll(int range, int count, int modifier) {
    int rollResult = 0;
    for (int i = 0; i < count; i++)
        rollResult += roll(range);
    return rollResult + modifier;
}      


int rollBaseStats() {
    int lowest = (total = roll(6));
    int next;

    for (int i = 0; i < 3; i++) {
        if ((next = roll(6)) < lowest)
            lowest = next;
        total += nextRoll;
    }
    
    return total - lowest;
}