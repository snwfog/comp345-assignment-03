/**
 *  Merchant.cpp
 *  comp345-assignment-03
 *
 */


#ifndef MERCHANT_H
#define MERCHANT_H
#include <vector>
#include "Item.h"
#include "Observer.h"
#include "ItemBuilder.h"
using std::vector;

class Merchant {
public:
    // iteration over a vector see:
    // http://stackoverflow.com/questions/409348/iteration-over-vector-in-c
    void putItem(Item* item) {
        merchantStach.push_back(item);
    }
    
    void putItem(Item* item, int index) {
        merchantStach[index] = item;
    }
    
    Item* getItem(int index) {
        ItemGenerator* ig = new ItemGenerator();
        Item* item = merchantStach[index];
        merchantStach[index] = ig->getRandomItem();
        return item;
    }
    
    Item* peek(int index) {
        return merchantStach[index];
    }
    
    void removeItem(int index) {
        merchantStach[index] = NULL;
    }
    
    void deleteItem(int index) {
        //delete merchantStach[index];
        merchantStach[index] = NULL;
    }
    
    vector<Item*> getStach() {  return merchantStach; }
    
    int size() { return (int)(merchantStach.size()); }
    
    // observer methods
    void attachMerchantObserver(Observer* ob) { observer = ob; }
    
private:
    vector<Item*> merchantStach;
    Observer* observer;
};


#endif
