//
//  Chest.h
//  comp345-assignment-03
//
//  Created by Charles Chao Yang on 11-11-17.


#ifndef CHEST_H
#define CHEST_H

#include <stack>
#include "Item.h"

using std::stack;

class Chest {
    
public:
    // iteration over a vector see:
    // http://stackoverflow.com/questions/409348/iteration-over-vector-in-c
    Chest();
    Chest(int size);
    ~Chest();
    
    void putItem(Item* item) {
        chestContainer.push(item);
    }
    
    Item* getItem() {
        if (!chestContainer.empty()) {
            Item* tmp = chestContainer.top();
            chestContainer.pop();
            return tmp;
        }
        return NULL;
    }
    
private:
    stack<Item*> chestContainer;
};

#endif
