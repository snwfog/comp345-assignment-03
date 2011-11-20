/**
 *  Chest.h
 *  comp345-assignment-03
 *
 */

#ifndef CHEST_H
#define CHEST_H

#include <vector>
#include "Item.h"

using std::vector;

class Chest {
    
public:
    // iteration over a vector see:
    // http://stackoverflow.com/questions/409348/iteration-over-vector-in-c
    void putItem(Item* item) {
        chestContainer.push_back(item);
    }
    
    Item* getItem(int index) {
        return chestContainer[index];
    }
    
    void removeItem(int index) {
        delete chestContainer[index];
        chestContainer[index] = NULL;
    }
    
    int size() { return (int)(chestContainer.size()); }
    
private:
    vector<class Item*> chestContainer;
};

#endif
