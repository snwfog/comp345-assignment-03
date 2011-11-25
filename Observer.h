/**
 *  Observer.h
 *  comp345-assignment-03
 *  
 */

#ifndef OBSERVER_H
#define OBSERVER_H

/**
 * Character observer
 */

#include <sstream>
#include <string>
using std::stringstream;
using std::string;

class Observer {
public:
    // dynamic windows updates
    virtual void updateBasic() = 0;
    virtual void updateVital() = 0;
    virtual void updateAbility() = 0;
    virtual void updateConsole(stringstream*, bool log = 0) = 0;
    virtual void updateConsole(string, bool log = 0) = 0;
    
    virtual void updateWeapon() = 0;
    virtual void updateArmor() = 0;
    virtual void updateInventory() = 0;
};
#endif
