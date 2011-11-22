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
using std::stringstream;

class Observer {
public:
    // dynamic windows updates
    virtual void updateBasic() = 0;
    virtual void updateVital() = 0;
    virtual void updateAbility() = 0;
    virtual void updateConsole(stringstream*, bool) = 0;
};

#endif
