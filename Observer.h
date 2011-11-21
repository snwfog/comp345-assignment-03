/**
 *  Observer.h
 *  comp345-assignment-03
 *  
 */

#ifndef OBSERVER_H
#define OBSERVER_H

//#include <ncurses.h>

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

//
///**
// *  Character Observer/Builder
// */
//
//// basic info observer
//class CharacterBasicObserver : public Observer {
//public:
//    void createWindow();
//    void updateInfo(Character* c);
//};
//
//// vital info observer
//class CharacterVitalObserver : public Observer {
//public:
//    void createWindow();
//    void updateInfo(Character* c);
//    
//};
//
//// ability scores observer
//class CharacterAbilityObserver : public Observer {
//public:
//    void createWindow();
//    void updateInfo(Character* c);
//    
//};
//

#endif
