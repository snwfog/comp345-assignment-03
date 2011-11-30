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
#include <sstream>
#include <string>
#include <ncurses.h>
#include "Observer.h"
#include "Character.h"
#include "Map.h"
#include "Item.h"
#include "CharacterBuilder.h"
#include "MerchantBuilder.h"
#include "ChestBuilder.h"

using std::vector;
using std::ofstream;
using std::map;
using std::stringstream;
using std::string;

class d20Game : public Observer {
public:
    // map/player getter/setter
    void setMap(Map* m) { map = m; }
    void setPlayer(Character* c) { player = c; }
    Map* getMap() { return map; }
    Character* getPlayer() { return player; }
    //    vector<Character*> npc; // not playable characters
    //    vector<Chest*> treasure; // treasure chests
    
    /**
     * Game playing related functions
     */
    void start(); // start the game playing engine
    void endgame();
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
    void updateMerchantPaneHelp();
    void updateChestPaneHelp();
    
    // item panel
    WINDOW* wItem;
    WINDOW* createWindowItem();
    void updateItem(Item*);
    
    // console window
    WINDOW* wConsole;
    WINDOW* createWindowConsole();
    void updateConsole(string, bool log = FALSE);
    void updateConsole(stringstream*, bool log = FALSE);
    
    // object specific window
    WINDOW* wMerchantInventory;
    WINDOW* createWindowMerchant();
    void updateMerchantInventory(Merchant*);
    
    WINDOW* wChest;
    WINDOW* createWindowChest();
    void updateChestStach(Chest*);
    
    WINDOW* wMonster;
    WINDOW* createWindowMonster();
    void updateMonsterVital(Character*);
    
    /**
     * Map and player movement
     */
    void refreshmap();
    void setPlayerCoordinate();
    void move(int);
    void movePlayerPosition(int, int);
    
    /**
     * Objects interaction
     */
    // chest stash, only stored generated chest
    vector<Chest*> chests;
    // monster list, only stored generated monster
    vector<Character*> monsters;
    
private:
    Map* map;
    Character* player;
    Coordinate* playerInitialCoordinate;
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
     * Player actions/interactions
     */
    void interactWithEnvironment();
    MapObject* getPrioritaryInteractableObject();
    MapObject* getPrioritaryInteractableObjectRadius2();
    void interactWithMerchant();
    // edit player inventory at merchant
    void interactWithChest();
    void interactWithMonster();
    
    /**
     * Others
     */
    // combat log file
    ofstream clog;
    ItemGenerator* ig;
};

#endif
