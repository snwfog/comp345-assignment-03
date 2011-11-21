/**
 *  d20Game.h
 *  comp345-assignment-03
 *  
 */

#ifndef d20GAME_H
#define d20GAME_H

#include <vector>
#include <fstream>
#include <ncurses.h>
#include "Observer.h"
#include "Character.h"
#include "Map.h"
#include "ItemBuilder.h"
#include "CharacterBuilder.h"

using std::vector;
using std::ofstream;

class d20Game : public Observer {
public:
    d20Game();
    d20Game(Map*);
    ~d20Game();

//private:
    Map* map;
    Character* player;
    // map/player getter/setter
    void setMap(Map* m) { map = m; }
    void setPlayer(Character* c) { player = c; }
    Map* getMap() { return map; }
    Character* getPlayer() { return player; }
    
//    vector<Character*> npc; // not playable characters
//    vector<Chest*> treasure; // treasure chests
    
    /**
     * Observer/Windows/Info variables and functions
     */
    WINDOW* wBasic;
    WINDOW* wVital;
    WINDOW* wAbility;
    WINDOW* wOption;
    
    // create basic stats windows
    WINDOW* createWindowBasic();
    WINDOW* createWindowVital();
    WINDOW* createWindowAbility();
    WINDOW* createWindowOption(); // static
    // observer updates on basic stats windows
    void updateBasic();
    void updateVital();
    void updateAbility();
    void updateOption();
    
    // console window
    WINDOW* wConsole;
    WINDOW* createWindowConsole();
    void updateConsole(string, bool log = FALSE);
    void updateConsole(stringstream*, bool);
    
    /**
     * Game playing related functions
     */
    void start(); // start the game playing engine
    
    /**
     * Game playing/interface helping functions
     */ 
    void wkill(WINDOW* win);
    
    /**
     * Others
     */
    // combat log file
    ofstream clog;
    ItemGenerator* ig;
};

#endif
