/**
 *  MerchantBuilder.h
 *  comp345-assignment-03
 *
 */

#ifndef MERCHANTBUILDER_H
#define MERCHANTBUILDER_H
#include "Merchant.h"

class MerchantBuilder {
public:
    Merchant* getMerchant() { return merchant; }
    void createNewMerchant() { merchant = new Merchant(); }
    void fillMerchantStach();
private:
    Merchant* merchant;
};

#endif
