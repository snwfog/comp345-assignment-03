/**
 *  Function.cpp
 *  comp345-assignment-03
 *
 */

#include <iostream>
#include "Function.h"

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
    int lowest = roll(6);
    int total = lowest;
    int next;

    for (int i = 0; i < 3; i++) {
        if ((next = roll(6)) < lowest)
            lowest = next;
        total += next;
    }
    
    return total - lowest;
}

int toModifier(int n) { return (n - 10)/2; }

bool fileExists(const std::string& filename)
{
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}