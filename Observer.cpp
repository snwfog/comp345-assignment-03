/**
 *  Observer.cpp
 *  comp345-assignment-03
 *  
 */

#include "Observer.h"

//using std::stringstream;
//
//void CharacterBasicObserver::createWindow() {
//    win = newwin(4, 16, 0, 0);
//    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
//}
//
//void CharacterBasicObserver::updateInfo(Character* c) {
//    mvwprintw(win, 1, 2, c->getName().c_str());
//    mvwprintw(win, 2, 2, c->getCharacterClass().c_str());
//    wrefresh(win);
//}
//
//
//void CharacterVitalObserver::createWindow() {
//    win = newwin(6, 16, 3, 0);
//    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
//}
//
//void CharacterVitalObserver::updateInfo(Character* c) {
//    stringstream msg;
//    msg << "HP: " << c->getHitPoint() << "/" << c->getMaxHitPoint();
//    mvwprintw(win, 1, 2, msg.str().c_str());
//    msg.str("");
//    msg.clear();
//    
//    msg << "MP: " << c->getManaPoint() << "/" << c->getMaxManaPoint();
//    mvwprintw(win, 2, 2, msg.str().c_str());
//    msg.str("");
//    msg.clear();
//    
//    //msg << "EXP: " << c->getExperience() << "/" c->getExperience();
//    msg << "EXP: NA";
//    mvwprintw(win, 3, 2, msg.str().c_str());
//    msg.str("");
//    msg.clear();
//    
//    msg << "LVL: " << c->getLevel();
//    mvwprintw(win, 4, 2, msg.str().c_str());
//    msg.str("");
//    msg.clear();
//    
//    wrefresh(win);
//}
//
//void CharacterAbilityObserver::createWindow() {
//    win = newwin(8, 16, 8, 0);
//    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
//}
//
//void CharacterAbilityObserver::updateInfo(Character* c) {
//    stringstream msg;
//    msg << "CON: " << c->getAbilityScore(CON);
//    mvwprintw(win, 1, 2, msg.str().c_str());
//    msg.str("");
//    msg.clear();
//    
//    msg << "STR: " << c->getAbilityScore(STR);
//    mvwprintw(win, 2, 2, msg.str().c_str());
//    msg.str("");
//    msg.clear();
//    
//    msg << "DEX: " << c->getAbilityScore(DEX);
//    mvwprintw(win, 3, 2, msg.str().c_str());
//    msg.str("");
//    msg.clear();
//    
//    msg << "INT: " << c->getAbilityScore(INT);
//    mvwprintw(win, 4, 2, msg.str().c_str());
//    msg.str("");
//    msg.clear();
//    
//    msg << "WIS: " << c->getAbilityScore(WIS);
//    mvwprintw(win, 5, 2, msg.str().c_str());
//    msg.str("");
//    msg.clear();
//    
//    msg << "CHR: " << c->getAbilityScore(CHR);
//    mvwprintw(win, 6, 2, msg.str().c_str());
//    msg.str("");
//    msg.clear();
//    
//    wrefresh(win);
//}
//
//
//
