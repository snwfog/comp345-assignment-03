/**
 *  d20Game.h
 *  comp345-assignment-03
 *  
 */

#ifndef d20GAME_H
#define d20GAME_H

#include <vector>
#include <map>
#include <fstream>
#include <ncurses.h>
#include "Observer.h"
#include "Character.h"
#include "Map.h"
#include "ItemBuilder.h"
#include "CharacterBuilder.h"

using std::vector;
using std::ofstream;
using std::map;

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
    
    // character basic panels
    // basic window
    WINDOW* wBasic;
    WINDOW* createWindowBasic();
    void updateBasic();
    // vital window
    WINDOW* wVital;
    WINDOW* createWindowVital();
    void updateVital();
    // ability window
    WINDOW* wAbility;
    WINDOW* createWindowAbility();
    void updateAbility();
    // option window --static
    WINDOW* wOption;
    WINDOW* createWindowOption();
    void updateOption();
    
    // character inventory/equipments panels
    // weapon window
    WINDOW* wWeapon;
    WINDOW* createWindowWeapon();
    void updateWeapon();
    // armor window
    WINDOW* wArmor;
    WINDOW* createWindowArmor();
    void updateArmor();
    
    // inventory window
    WINDOW* wInventory;
    WINDOW* createWindowInventory();
    void updateInventory();
    
    // help window --static
    WINDOW* wHelp;
    WINDOW* createWindowHelp();
    void updateCharacterPaneHelp();
    void updateItemPaneHelp();
    
    // item panel
    WINDOW* wItem;
    WINDOW* createWindowItem();
    void updateItem(Item*);
    
    // console window
    WINDOW* wConsole;
    WINDOW* createWindowConsole();
    void updateConsole(string, bool log = FALSE);
    void updateConsole(stringstream*, bool);
    
    // items related actions
    void equippedWeaponEdit(int);
    void equippedArmorEdit(int);
    void inventoryEdit(int);
    void deleteItem(int);
    
    // windows related functions
    void wkill(WINDOW* win);
    void loadCharacterPanel();
    void killCharacterPanel();
    

    /**
     * Game playing related functions
     */
    void start(); // start the game playing engine
    
    /**
     * Others
     */
    // combat log file
    ofstream clog;
    ItemGenerator* ig;
    

};

#endif
