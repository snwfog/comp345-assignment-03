/**
 *  d20Game.cpp
 *  comp345-assignment-03
 *  
 */

#include <iostream>
#include "d20Game.h"

d20Game::d20Game(Map* m) {
/**
 * Initialize character and map variables
 */
    map = m;
    FighterGenerator* fg = new FighterGenerator();
    fg->setCharacterBuilder(new BullyBuilder());
    fg->createNewFighter("KittyMeow");
    player = fg->getCharacter();
    // attach d20game as character observer
    player->attachCharacterObserver(this);
/**
 * Building ncurses windows
 */ 
    // initiate basic ncurses funcs
    initscr();
    noecho();
    curs_set(0);
    raw();
    keypad(stdscr, TRUE);
    wclear(stdscr);
    refresh();
    
    // basic character windows
    wBasic = createWindowBasic();
    wVital = createWindowVital();
    wAbility = createWindowAbility();
    wOption = createWindowOption();
    
    // update basic character windows
    updateBasic();
    updateVital();
    updateAbility();
    updateOption(); // static
    
    // console window
    wConsole = createWindowConsole();
    updateConsole("Tip: Use the arrow key to move your character!");
/**
 * others initialization
 */
    // attach combat log file
    clog.open("combat.log");
    
    
    // start the game engine
    start();
    
    // end of ncurses
    endwin();
}

/**
 * Observer/Windows/Info variables and functions
 */

// character basic panels
// basic window
WINDOW* d20Game::createWindowBasic() {
    WINDOW* win = newwin(4, 16, 0, 0);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    return win;
}

void d20Game::updateBasic() {
    mvwprintw(wBasic, 1, 2, player->getName().c_str());
    mvwprintw(wBasic, 2, 2, player->getCharacterClass().c_str());
    wrefresh(wBasic);
}

WINDOW* d20Game::createWindowVital() {
    WINDOW* win = newwin(6, 16, 3, 0);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    return win;
}

void d20Game::updateVital() {
    stringstream msg;
    msg << "HP: " << player->getHitPoint() << "/" << player->getMaxHitPoint();
    mvwprintw(wVital, 1, 2, msg.str().c_str());
    msg.str("");
    msg.clear();
    
    msg << "MP: " << player->getManaPoint() << "/" << player->getMaxManaPoint();
    mvwprintw(wVital, 2, 2, msg.str().c_str());
    msg.str("");
    msg.clear();
    
    //msg << "EXP: " << c->getExperience() << "/" c->getExperience();
    msg << "EXP: NA";
    mvwprintw(wVital, 3, 2, msg.str().c_str());
    msg.str("");
    msg.clear();
    
    msg << "LVL: " << player->getLevel();
    mvwprintw(wVital, 4, 2, msg.str().c_str());
    msg.str("");
    msg.clear();
    
    wrefresh(wVital);
}

// ability window
WINDOW* d20Game::createWindowAbility() {
    WINDOW* win = newwin(10, 16, 8, 0);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    return win;
}

void d20Game::updateAbility() {
    stringstream msg;
    msg << "CON: " << player->getAbilityScore(CON);
    mvwprintw(wAbility, 1, 2, msg.str().c_str());
    msg.str("");
    msg.clear();
    
    msg << "STR: " << player->getAbilityScore(STR);
    mvwprintw(wAbility, 2, 2, msg.str().c_str());
    msg.str("");
    msg.clear();
    
    msg << "DEX: " << player->getAbilityScore(DEX);
    mvwprintw(wAbility, 3, 2, msg.str().c_str());
    msg.str("");
    msg.clear();
    
    msg << "INT: " << player->getAbilityScore(INT);
    mvwprintw(wAbility, 4, 2, msg.str().c_str());
    msg.str("");
    msg.clear();
    
    msg << "WIS: " << player->getAbilityScore(WIS);
    mvwprintw(wAbility, 5, 2, msg.str().c_str());
    msg.str("");
    msg.clear();
    
    msg << "CHR: " << player->getAbilityScore(CHR);
    mvwprintw(wAbility, 6, 2, msg.str().c_str());
    msg.str("");
    msg.clear();
    
    msg << "MAX. ATK: " << player->getMaxAttackBonus();
    mvwprintw(wAbility, 7, 2, msg.str().c_str());
    msg.str("");
    msg.clear();
    
    msg << "MAX. DMG: " << player->getMaxDamagBonus();
    mvwprintw(wAbility, 8, 2, msg.str().c_str());
    msg.str("");
    msg.clear();
    
    wrefresh(wAbility);
}

// option window -- static
WINDOW* d20Game::createWindowOption() {
    WINDOW* win = newwin(8, 16, 17, 0);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    return win;
}

void d20Game::updateOption() {
    mvwprintw(wOption, 1, 2, "[i]nventory");
    mvwprintw(wOption, 2, 2, "[q]uit");
    wrefresh(wOption);
}


// character inventory/equipments panels
WINDOW* d20Game::createWindowWeapon() {
    WINDOW* win = newwin(5, 34, 0, 16);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    return win;
}

void d20Game::updateWeapon() {
    wclear(wWeapon);
    wborder(wWeapon, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(wWeapon);
    
    stringstream msg;
    mvwprintw(wWeapon, 1, 2, "[Character Panel]");
    Weapon* mh = player->getEquippedWeapon(MAINHAND);
    Weapon* oh = player->getEquippedWeapon(OFFHAND);
    if (mh != NULL) {
        if (mh->getWeaponWield() == TWOHAND) {
            msg << "[M]H: " << (player->getEquippedWeapon(MAINHAND)->getName());
            mvwprintw(wWeapon, 2, 2, msg.str().c_str());
            msg.str("");
            msg.clear();
            msg << "[O]H: <OCCUPIED>";
            mvwprintw(wWeapon, 3, 2, msg.str().c_str());
            msg.str("");
            msg.clear();
        } else if (oh == NULL) {
            msg << "[M]H: " << (player->getEquippedWeapon(MAINHAND)->getName());
            mvwprintw(wWeapon, 2, 2, msg.str().c_str());
            msg.str("");
            msg.clear();
            msg << "[O]H: -";
            mvwprintw(wWeapon, 3, 2, msg.str().c_str());
            msg.str("");
            msg.clear();
        } else {
            msg << "[M]H: " << (player->getEquippedWeapon(MAINHAND)->getName());
            mvwprintw(wWeapon, 2, 2, msg.str().c_str());
            msg.str("");
            msg.clear();
            msg << "[O]H: " << (player->getEquippedWeapon(OFFHAND)->getName());
            mvwprintw(wWeapon, 3, 2, msg.str().c_str());
            msg.str("");
            msg.clear();
        }
    } else if (oh != NULL) {
        msg << "[M]H: -";
        mvwprintw(wWeapon, 2, 2, msg.str().c_str());
        msg.str("");
        msg.clear();
        msg << "[O]H: " << (player->getEquippedWeapon(OFFHAND)->getName());
        mvwprintw(wWeapon, 3, 2, msg.str().c_str());
        msg.str("");
        msg.clear();
    } else {
        msg << "[M]H: -";
        mvwprintw(wWeapon, 2, 2, msg.str().c_str());
        msg.str("");
        msg.clear();
        msg << "[O]H: -";
        mvwprintw(wWeapon, 3, 2, msg.str().c_str());
        msg.str("");
        msg.clear();
    }
    wrefresh(wWeapon);
}

// armor window
WINDOW* d20Game::createWindowArmor() {
    WINDOW* win = newwin(8, 34, 4, 16);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    return win;
}

void d20Game::updateArmor() {
    wclear(wArmor);
    wborder(wArmor, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(wArmor);

    stringstream msg;
    
    if (player->getEquippedArmor(HEAD) != NULL) {
        msg << "[H]ead: " << player->getEquippedArmor(HEAD)->getName();
        mvwprintw(wArmor, 1, 2, msg.str().c_str());
        msg.str("");
        msg.clear();
    } else {
        mvwprintw(wArmor, 1, 2, "[H]ead: -");
    }
    
    if (player->getEquippedArmor(CHEST) != NULL) {
        msg << "[C]hest: " << player->getEquippedArmor(CHEST)->getName();
        mvwprintw(wArmor, 2, 2, msg.str().c_str());
        msg.str("");
        msg.clear();
    } else {
        mvwprintw(wArmor, 2, 2, "[C]hest: -");
    }
    
    if (player->getEquippedArmor(HANDS) != NULL) {
        msg << "[G]loves: " << player->getEquippedArmor(HANDS)->getName();
        mvwprintw(wArmor, 3, 2, msg.str().c_str());
        msg.str("");
        msg.clear();
    } else {
        mvwprintw(wArmor, 3, 2, "[G]loves: -");
    }
    
    if (player->getEquippedArmor(FEET) != NULL) {
        msg << "[F]eet: " << player->getEquippedArmor(FEET)->getName();
        mvwprintw(wArmor, 4, 2, msg.str().c_str());
        msg.str("");
        msg.clear();
    } else {
        mvwprintw(wArmor, 4, 2, "[F]eet: -");
    }
    
    if (player->getEquippedArmor(WAIST) != NULL) {
        msg << "[B]elt: " << player->getEquippedArmor(WAIST)->getName();
        mvwprintw(wArmor, 5, 2, msg.str().c_str());
        msg.str("");
        msg.clear();
    } else {
        mvwprintw(wArmor, 5, 2, "[B]elt: -");
    }
    
    if (player->getEquippedArmor(FINGER) != NULL) {
        msg << "[R]ing: " << player->getEquippedArmor(FINGER)->getName();
        mvwprintw(wArmor, 6, 2, msg.str().c_str());
        msg.str("");
        msg.clear();
    } else {
        mvwprintw(wArmor, 6, 2, "[R]ing: -");
    }

    wrefresh(wArmor);
}

// inventory window
WINDOW* d20Game::createWindowInventory() {
    WINDOW* win = newwin(13, 34, 11, 16);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    return win;
}

void d20Game::updateInventory() {
    wclear(wInventory);
    wborder(wInventory, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(wInventory);
    
    stringstream msg;
    msg << "[Inventory " << (10 - player->emptyInventorySlot()) << "/10][Gold: " << player->getGold() << "g]";
    mvwprintw(wInventory, 1, 2, msg.str().c_str());
    msg.str("");
    msg.clear();
    
    for (int i = 0; i < 10; i++) {
        Item* tmp = player->getInventoryItem(i);
        if (tmp == NULL)
            msg << i << ": -";
        else
            msg << i << ": " << (tmp->getName());

        mvwprintw(wInventory, i+2, 2, msg.str().c_str());
        msg.str("");
        msg.clear();
    }
    wrefresh(wInventory);
}

// help window -- static
WINDOW* d20Game::createWindowHelp() {
    WINDOW* win = newwin(12, 31, 0, 49);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    return win;
}

void d20Game::updateCharacterPaneHelp() {
    wclear(wHelp);
    wborder(wHelp, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(wHelp);
    
    mvwprintw(wHelp, 1, 2, "[Inventory Help]");
    mvwprintw(wHelp, 2, 3, "ESC: Return to game.");
    mvwprintw(wHelp, 3, 3, "\\d | [mohcgfbr]:");
    mvwprintw(wHelp, 4, 3, "    Item edit mode.");
    
    wrefresh(wHelp);
}

void d20Game::updateItemPaneHelp() {
    wclear(wHelp);
    wborder(wHelp, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(wHelp);
    
    mvwprintw(wHelp, 1, 2, "[Item Help]");
    mvwprintw(wHelp, 2, 3, "ESC: Quit item edit");
    mvwprintw(wHelp, 3, 3, "D: Delete item");
    mvwprintw(wHelp, 4, 3, "[\\d | [mohcgfbr]]:");
    mvwprintw(wHelp, 5, 3, "    Swap item slot");
    
    wrefresh(wHelp);
}

// item window
WINDOW* d20Game::createWindowItem() {
    WINDOW* win = newwin(12, 30, 12, 50);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    return win;
}

void d20Game::updateItem(Item* it) {
    wclear(wItem);
    wborder(wItem, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(wItem);
    
    stringstream msg;
    if (it->getItemType() == IS_WEAPON) {
        Weapon* wp = static_cast<Weapon*>(it);
        wattron(wItem, A_STANDOUT);
        mvwprintw(wItem, 1, 2, it->getName().c_str());
        wattroff(wItem, A_STANDOUT);
        
        msg << wp->getWeaponWield();
        mvwprintw(wItem, 2, 2, msg.str().c_str());
        msg.str("");
        
        msg << "Attack Bonus: " << wp->getAttackBonus();
        mvwprintw(wItem, 3, 2, msg.str().c_str());
        msg.str("");
        
        msg << "Damage Bonus: " << wp->getDamageBonus();
        mvwprintw(wItem, 4, 2, msg.str().c_str());
        msg.str("");
        
        msg << "Size: " << wp->getSize();
        mvwprintw(wItem, 5, 2, msg.str().c_str());
        msg.str("");
        
        msg << "Cost: " << wp->getCost() << "g";
        mvwprintw(wItem, 6, 2, msg.str().c_str());
        msg.str("");
    } else if (it->getItemType() == IS_ARMOR) {
        Armor* am = static_cast<Armor*>(it);
        wattron(wItem, A_STANDOUT);
        mvwprintw(wItem, 1, 2, it->getName().c_str());
        wattroff(wItem, A_STANDOUT);
        
        msg << am->getSlot();
        mvwprintw(wItem, 2, 2, msg.str().c_str());
        msg.str("");
        
        msg << "Armor Bonus: " << am->getArmor();
        mvwprintw(wItem, 3, 2, msg.str().c_str());
        msg.str("");
        
        msg << "Max. Dexterity: " << am->getMaxDexterity();
        mvwprintw(wItem, 4, 2, msg.str().c_str());
        msg.str("");
        
        int line = 5;
        std::map<Attribute, int> stats = am->getStatsMap();
        std::map<Attribute, int>::const_iterator itr;
        for(itr = stats.begin(); itr != stats.end(); ++itr) {
            if (itr->first == CON) {
                msg << "CON: " << itr->second;
                mvwprintw(wItem, line, 2, msg.str().c_str());
                msg.str("");
                line++;
            } else if (itr->first == STR) {
                msg << "STR: " << itr->second;
                mvwprintw(wItem, line, 2, msg.str().c_str());
                msg.str("");
                line++;
            } else if (itr->first == DEX) {
                msg << "DEX: " << itr->second;
                mvwprintw(wItem, line, 2, msg.str().c_str());
                msg.str("");
                line++;
            } else if (itr->first == INT) {
                msg << "INT: " << itr->second;
                mvwprintw(wItem, line, 2, msg.str().c_str());
                msg.str("");
                line++;
            } else if (itr->first == WIS) {
                msg << "WIS: " << itr->second;
                mvwprintw(wItem, line, 2, msg.str().c_str());
                msg.str("");
                line++;
            } else if (itr->first == CHR) {
                msg << "CHR: " << itr->second;
                mvwprintw(wItem, line, 2, msg.str().c_str());
                msg.str("");
                line++;
            }
            
        }
        msg << "Cost: " << am->getCost() << "g";
        mvwprintw(wItem, line, 2, msg.str().c_str());
        msg.str("");
    } else if (it->getItemType() == IS_POTION) {
        Potion* pt = static_cast<Potion*>(it);
        wattron(wItem, A_STANDOUT);
        mvwprintw(wItem, 1, 2, pt->getName().c_str());
        wattroff(wItem, A_STANDOUT);
        
        msg << "Amount: " << pt->getPotionPool();
        mvwprintw(wItem, 2, 2, msg.str().c_str());
        msg.str("");
        
        msg << "Cost: " << pt->getCost() << "g";
        mvwprintw(wItem, 3, 2, msg.str().c_str());
        msg.str("");
    }
    
    wrefresh(wItem);
}

// console window
WINDOW* d20Game::createWindowConsole() {
    WINDOW* win = newwin(1, 64, 24, 16);
    wrefresh(win);
    return win;
}

void d20Game::updateConsole(string str, bool log) {
    wclear(wConsole);
    mvwprintw(wConsole, 0, 1, str.c_str());
    wrefresh(wConsole);
    // append to combat log if applicable
    if (log)
        clog << str << std::endl;
}

void d20Game::updateConsole(stringstream* sstr, bool log) {
    updateConsole((sstr->str()).c_str(), log);
    sstr->str("");
    sstr->clear();
}

// windows related functions
void d20Game::wkill(WINDOW* win) {
    wborder(win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wclear(win);
    wrefresh(win);
    delwin(win);
}

void d20Game::loadCharacterPanel() {
    wWeapon = createWindowWeapon();
    updateWeapon();
    wArmor = createWindowArmor();
    updateArmor();
    wInventory = createWindowInventory();
    updateInventory();
    
    // print character panel tip
    updateConsole("Tip: Press ESC to return to the game.");
    
    bool done = FALSE;
    int c;
    while (!done) {
        
        // renew help menu
        if (wHelp != NULL)
            wkill(wHelp);
        wHelp = createWindowHelp();
        updateCharacterPaneHelp();
        
        // clean the item panel
        // kill item panel
        if (wItem != NULL) {
            wkill(wItem);
            wItem = NULL;
        }
        
        switch (c = getch()) {
            case 'm':
            case 'o':
                // kill character pane help n load item pane help
                wkill(wHelp);
                wHelp = createWindowHelp();
                updateItemPaneHelp();
                updateConsole("Tip: Press ESC to quit item edit.");
                
                equippedWeaponEdit(c);
                break;
            case 'h':
            case 'c':
            case 'g':
            case 'f':
            case 'b':
            case 'r':
                equippedArmorEdit(c);
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                inventoryEdit(c);
                break;
            case 27:
                done = TRUE;
                break;
            default:
                break;
        }
    }
    
    // destroy the character panes windows
    killCharacterPanel();
}

void d20Game::killCharacterPanel() {
    wkill(wWeapon);
    wkill(wArmor);
    wkill(wInventory);
    wkill(wHelp);
    if (wItem != NULL)
        wkill(wItem);
    
    wWeapon = NULL;
    wArmor = NULL;
    wInventory = NULL;
    wHelp = NULL;
    wItem = NULL;
    
    updateConsole("");
    // refresh the std map
    // refreshmap(); -- to add later
}

/**
 * Game playing related functions
 */
void d20Game::start() {
    int c;
    bool quit = FALSE;
    stringstream msg;
    // print tip
    updateConsole("Tip: Use the arrow key to move your character!");
    while (!quit) {
        switch (c = getch()) {
            case KEY_UP:
            case KEY_DOWN:
            case KEY_LEFT:
            case KEY_RIGHT:
                //move(c);
                break;
            case 'i':
                loadCharacterPanel();
                break;
            case 'q':
                updateConsole("Are you sure you want to end the game? (y/n) "); 
                if ((c = getch()) == 'y') {
                    quit = TRUE;
                    break;
                }
                break;
            default:
                break;
        }
    }
}

/**
 * Others
 */

// extremely long functions

// items related actions
void d20Game::equippedWeaponEdit(int it) {
    Item* item;
    WeaponSlot ws;
    int index;
    int c;
    
    if (it == 'm')
        ws = MAINHAND;
    else if (it == 'o')
        ws = OFFHAND;
    
    item = player->getEquippedWeapon(ws);
    if (item != NULL) {
        if (wItem == NULL)
            wItem = createWindowItem();
        updateItem(item);
        switch (c = getch()) {
            case 'd':
            case 's':
                updateConsole("Error: You must unequip that item first!");
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '0':
                index = static_cast<int>(c - '0');
                if (player->getInventoryItem(index) == NULL) {
                    player->putToInventory(player->unequipWeapon(ws), index);
                } else {
                    updateConsole("Error: Inventory slot is occupied.");
                }
                break;
            default:
                updateConsole("Error: Unrecognized command.");
                break;
        }
    }

}

void d20Game::equippedArmorEdit(int it) {
    Item* item;
    ArmorSlot as;
    int index;
    int c;

    if (it == 'h')
        as = HEAD;
    else if (it == 'c')
        as = CHEST;
    else if (it == 'g')
        as = HANDS;
    else if (it == 'f')
        as = FEET;
    else if (it == 'b')
        as = WAIST;
    else if (it == 'r')
        as = FINGER;
    
    item = player->getEquippedArmor(as);
    if (item != NULL) {
        if (wItem == NULL)
            wItem = createWindowItem();
        updateItem(item);
        switch (c = getch()) {
            case 'd':
            case 's':
                updateConsole("Error: You must unequip that item first!");
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '0':
                index = static_cast<int>(c - '0');
                if (player->getInventoryItem(index) == NULL) {
                    player->putToInventory(player->unequipArmor(as), index);
                } else {
                    updateConsole("Error: Inventory slot is occupied.");
                }
                break;
            default:
                updateConsole("Error: Unrecognized command.");
                break;
        }
    }
}

void d20Game::inventoryEdit(int it) {
    int index = static_cast<int>(it - '0');
    int c;
    stringstream msg;
    Item* item = player->getInventoryItem(index);
    Weapon* wp;
    Armor* am;
    ArmorSlot as;
    if (item != NULL) {
        if (wItem == NULL) {
            wItem = createWindowItem();
            updateItem(item);
        }
        switch (c = getch()) {
            // handle from inventory to weapon
            case 'm':
                if (item->getItemType() == IS_WEAPON) {
                    wp = static_cast<Weapon*>(item);
                    if (player->getEquippedWeapon(MAINHAND) == NULL) {
                        if (wp->getWeaponWield() == TWOHAND && player->getEquippedWeapon(OFFHAND) != NULL) {
                            updateConsole("Error: You require both hands for that weapon!");
                        } else {
                            player->equipWeaponFromInventory(MAINHAND, index);
                        }
                    } else {
                        updateConsole("Error: You must unequip that item first!");
                    }
                } else {
                    updateConsole("Error: Illegal operation.");
                }
                break;
            case 'o':
                if (item->getItemType() == IS_WEAPON) {
                    wp = static_cast<Weapon*>(item);
                    if (player->getEquippedWeapon(OFFHAND) == NULL) {
                        if (wp->getWeaponWield() == TWOHAND) {
                            updateConsole("Error: You can only wield that weapon in your mainhand.");
                        } else {
                            player->equipWeaponFromInventory(OFFHAND, index);
                        }
                    } else {
                        updateConsole("Error: You must unequip that item first!");
                    }
                } else {
                    updateConsole("Error: Illegal operation.");
                }
                break;
            // handle from inventory to armor slot    
            case 'h':
            case 'c':
            case 'g':
            case 'f':
            case 'b':
            case 'r':
                if (c == 'h')
                    as = HEAD;
                else if (c == 'c')
                    as = CHEST;
                else if (c == 'g')
                    as = HANDS;
                else if (c == 'f')
                    as = FEET;
                else if (c == 'b')
                    as = WAIST;
                else if (c == 'r')
                    as = FINGER;
                if (item->getItemType() == IS_ARMOR) {
                    am = static_cast<Armor*>(item);
                    if (player->getEquippedArmor(as) != NULL) {
                        updateConsole("Error: You must unequip that item first!");
                    } else {
                        if (am->getSlot() != as) {
                            updateConsole("Error: You cannot equip that there!");
                        } else {
                            player->equipArmorFromInventory(as, index);
                        }
                    }
                } else
                    updateConsole("Error: Illegal operation.");
                break;
                
            // handle for deleting an inventory
            case 'd':
                msg << "Permanantely delete: " << item->getName() << "? (y/n) ";
                updateConsole(msg.str().c_str());
                msg.str("");
                msg.clear();
                if ((c = getch()) == 'y') {                    
                    msg << item->getName() << " was permanantely delete from your inventory.";
                    updateConsole(msg.str().c_str(), TRUE);
                    player->deleteInventoryItem(index);
                    msg.str("");
                    msg.clear();
                }
                break;
                
            default:
                break;
        }
    }
    // clean all pointers
                            
    // kill item panel
    if (wItem != NULL)
        wkill(wItem);
    wItem = NULL;
}