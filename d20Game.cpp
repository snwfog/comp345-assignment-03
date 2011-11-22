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
    WINDOW* win = newwin(8, 16, 8, 0);
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
    
    wrefresh(wAbility);
}

// option window -- static
WINDOW* d20Game::createWindowOption() {
    WINDOW* win = newwin(10, 16, 15, 0);
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
            msg << "[O]H: <EMPTY>";
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
        msg << "[M]H: <EMPTY>";
        mvwprintw(wWeapon, 2, 2, msg.str().c_str());
        msg.str("");
        msg.clear();
        msg << "[O]H: " << (player->getEquippedWeapon(OFFHAND)->getName());
        mvwprintw(wWeapon, 3, 2, msg.str().c_str());
        msg.str("");
        msg.clear();
    } else {
        msg << "[M]H: <EMPTY>";
        mvwprintw(wWeapon, 2, 2, msg.str().c_str());
        msg.str("");
        msg.clear();
        msg << "[O]H: <EMPTY>";
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
    wrefresh(wArmor);

    stringstream msg;
    
    if (player->getEquippedArmor(HEAD) != NULL) {
        msg << "[H]ead: " << player->getEquippedArmor(HEAD)->getName();
        mvwprintw(wArmor, 1, 2, msg.str().c_str());
        msg.str("");
        msg.clear();
    } else {
        mvwprintw(wArmor, 1, 2, "[H]ead: <EMPTY>");
    }
    
    if (player->getEquippedArmor(CHEST) != NULL) {
        msg << "[C]hest: " << player->getEquippedArmor(CHEST)->getName();
        mvwprintw(wArmor, 2, 2, msg.str().c_str());
        msg.str("");
        msg.clear();
    } else {
        mvwprintw(wArmor, 2, 2, "[C]hest: <EMPTY>");
    }
    
    if (player->getEquippedArmor(HANDS) != NULL) {
        msg << "[G]loves: " << player->getEquippedArmor(HANDS)->getName();
        mvwprintw(wArmor, 3, 2, msg.str().c_str());
        msg.str("");
        msg.clear();
    } else {
        mvwprintw(wArmor, 3, 2, "[G]loves: <EMPTY>");
    }
    
    if (player->getEquippedArmor(FEET) != NULL) {
        msg << "[F]eet: " << player->getEquippedArmor(FEET)->getName();
        mvwprintw(wArmor, 4, 2, msg.str().c_str());
        msg.str("");
        msg.clear();
    } else {
        mvwprintw(wArmor, 4, 2, "[F]eet: <EMPTY>");
    }
    
    if (player->getEquippedArmor(WAIST) != NULL) {
        msg << "[B]elt: " << player->getEquippedArmor(WAIST)->getName();
        mvwprintw(wArmor, 5, 2, msg.str().c_str());
        msg.str("");
        msg.clear();
    } else {
        mvwprintw(wArmor, 5, 2, "[B]elt: <EMPTY>");
    }
    
    if (player->getEquippedArmor(FINGER) != NULL) {
        msg << "[R]ing: " << player->getEquippedArmor(FINGER)->getName();
        mvwprintw(wArmor, 6, 2, msg.str().c_str());
        msg.str("");
        msg.clear();
    } else {
        mvwprintw(wArmor, 6, 2, "[R]ing: <EMPTY>");
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
    wrefresh(wInventory);
    stringstream msg;
    msg << "[Inventory " << (10 - player->emptyInventorySlot()) << "/10]";
    mvwprintw(wInventory, 1, 2, msg.str().c_str());
    msg.str("");
    msg.clear();
    
    for (int i = 0; i < 10; i++) {
        Item* tmp = player->getInventoryItem(i);
        if (tmp == NULL)
            msg << i << ": <EMPTY>";
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
    wrefresh(wHelp);
    
    mvwprintw(wHelp, 1, 2, "[Inventory Help]");
    mvwprintw(wHelp, 2, 3, "ESC: Return to game.");
    mvwprintw(wHelp, 3, 3, "\\d | [mohcgfbr]:");
    mvwprintw(wHelp, 4, 3, "    Item edit mode.");
    
    wrefresh(wHelp);
}

void d20Game::updateItemPaneHelp() {
    wclear(wHelp);
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

void d20Game::updateItem(Item*) {
    wclear(wItem);
    wrefresh(wItem);
    
    //map<Attribute, int> statsMap;
    wattron(wItem, A_STANDOUT);
    mvwprintw(wItem, 1, 2, "ITEM");
    wattroff(wItem, A_STANDOUT);
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



void d20Game::equippedArmorEdit(int it) {
    updateItemPaneHelp();
}

void d20Game::inventoryEdit(int it) {
    
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
    
    wHelp = createWindowHelp();
    updateCharacterPaneHelp();

    updateConsole("Tip: Press ESC to return to the game.");
    
    bool done = FALSE;
    int c;
    while (!done) {
        switch (c = getch()) {
            case 'm':
            case 'o':
                // kill character pane help n load item pane help
                wkill(wHelp);
                wHelp = createWindowHelp();
                updateItemPaneHelp();
                
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
                } else {
                    updateConsole("Tip: Use the arrow key to move your character!");
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
    if (wItem == NULL)
        wItem = createWindowItem();
    
    Item* item;
    int index;
    int c;
    switch (it) {
        case 'm':
            item = player->getEquippedWeapon(MAINHAND);
            if (item != NULL) {
                updateItem(NULL);
                c = getch();
                switch (c) {
                    case 'd':
                        deleteItem(it);
                        break;
                    case 's':
                        //sellItem(it);
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
                            player->setInventoryItem(index, player->unequipWeapon(MAINHAND));
                        } else {
                            updateConsole("Error: Inventory slot is occupied.");
                        }
                        break;
                    default:
                        updateConsole("Error: Unrecognized command.");
                        break;
                }
            }
            break;
            
        case 'o':
            item = player->getEquippedWeapon(OFFHAND);
            if (item != NULL) {
                updateItem(NULL);
                c = getch();
                switch (c) {
                    case 'd':
                        deleteItem(it);
                        break;
                    case 's':
                        //sellItem(it);
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
                            player->setInventoryItem(index, player->getEquippedWeapon(MAINHAND));
                        } else {
                            updateConsole("Error: Inventory slot is occupied.");
                        }
                        break;
                    default:
                        updateConsole("Error: Unrecognized command.");
                        break;
                }
            }
            break;
        default:
            updateConsole("Error: Unrecognized weapon slot.");
            break;
    }
    
    // kill item panel
    if (wItem != NULL)
        wkill(wItem);
    wItem = NULL;
    
    // reupdate the console tip
    updateConsole("Tip: Press ESC to return to the game.");
    
    // restore the help panel
    wkill(wHelp);
    wHelp = createWindowHelp();
    updateCharacterPaneHelp();
}

void d20Game::deleteItem(int it) {
    Item* item;
    bool done = FALSE; 
    int c;
    stringstream msg;
    while (!done) {
        switch (it) {
            case 'm':
                item = player->getEquippedWeapon(MAINHAND);
                if (item != NULL) {
                    msg << "Permanantely delete: " << item->getName() << "?";
                    updateConsole(msg.str().c_str());
                    msg.str("");
                    msg.clear();
                    if ((c = getch()) == 'y') {
                        player->setEquippedWeapon(MAINHAND, NULL);
                        msg << item->getName() << " was permanantely delete.";
                        updateConsole(msg.str().c_str(), TRUE);
                        msg.str("");
                        msg.clear();
                        done = TRUE;
                    } else if (c == 'n')
                        done = TRUE;
                }
                break;
            case 'o':
                item = player->getEquippedWeapon(OFFHAND);
                if (item != NULL) {
                    msg << "Permanantely delete: " << item->getName() << "?";
                    updateConsole(msg.str().c_str());
                    msg.str("");
                    msg.clear();
                    if ((c = getch()) == 'y') {
                        player->setEquippedWeapon(OFFHAND, NULL);
                        msg << item->getName() << " was permanantely delete.";
                        updateConsole(msg.str().c_str(), TRUE);
                        msg.str("");
                        msg.clear();
                        break;
                    }
                    done = TRUE;
                }
                break;
            case 'h':
                item = player->getEquippedArmor(HEAD);
                if (item != NULL) {
                    msg << "Permanantely delete: " << item->getName() << "?";
                    updateConsole(msg.str().c_str());
                    msg.str("");
                    msg.clear();
                    if ((c = getch()) == 'y') {
                        player->setEquippedArmor(HEAD, NULL);
                        msg << item->getName() << " was permanantely delete.";
                        updateConsole(msg.str().c_str(), TRUE);
                        msg.str("");
                        msg.clear();
                        break;
                    }
                    done = TRUE;
                }
                break;
            case 'c':
                item = player->getEquippedArmor(CHEST);
                if (item != NULL) {
                    msg << "Permanantely delete: " << item->getName() << "?";
                    updateConsole(msg.str().c_str());
                    msg.str("");
                    msg.clear();
                    if ((c = getch()) == 'y') {
                        player->setEquippedArmor(CHEST, NULL);
                        msg << item->getName() << " was permanantely delete.";
                        updateConsole(msg.str().c_str(), TRUE);
                        msg.str("");
                        msg.clear();
                        break;
                    }
                    done = TRUE;
                }
                break;
            case 'g':
                item = player->getEquippedArmor(HANDS);
                if (item != NULL) {
                    msg << "Permanantely delete: " << item->getName() << "?";
                    updateConsole(msg.str().c_str());
                    msg.str("");
                    msg.clear();
                    if ((c = getch()) == 'y') {
                        player->setEquippedArmor(HANDS, NULL);
                        msg << item->getName() << " was permanantely delete.";
                        updateConsole(msg.str().c_str(), TRUE);
                        msg.str("");
                        msg.clear();
                        break;
                    }
                    done = TRUE;
                }
                break;
            case 'f':
                item = player->getEquippedArmor(FEET);
                if (item != NULL) {
                    msg << "Permanantely delete: " << item->getName() << "?";
                    updateConsole(msg.str().c_str());
                    msg.str("");
                    msg.clear();
                    if ((c = getch()) == 'y') {
                        player->setEquippedArmor(FEET, NULL);
                        msg << item->getName() << " was permanantely delete.";
                        updateConsole(msg.str().c_str(), TRUE);
                        msg.str("");
                        msg.clear();
                        break;
                    }
                    done = TRUE;
                }
                break;
            case 'b':
                item = player->getEquippedArmor(WAIST);
                if (item != NULL) {
                    msg << "Permanantely delete: " << item->getName() << "?";
                    updateConsole(msg.str().c_str());
                    msg.str("");
                    msg.clear();
                    if ((c = getch()) == 'y') {
                        player->setEquippedArmor(WAIST, NULL);
                        msg << item->getName() << " was permanantely delete.";
                        updateConsole(msg.str().c_str(), TRUE);
                        msg.str("");
                        msg.clear();
                        break;
                    }
                    done = TRUE;
                }
                break;
            case 'r':
                item = player->getEquippedArmor(FINGER);
                if (item != NULL) {
                    msg << "Permanantely delete: " << item->getName() << "?";
                    updateConsole(msg.str().c_str());
                    msg.str("");
                    msg.clear();
                    if ((c = getch()) == 'y') {
                        player->setEquippedArmor(FINGER, NULL);
                        msg << item->getName() << " was permanantely delete.";
                        updateConsole(msg.str().c_str(), TRUE);
                        msg.str("");
                        msg.clear();
                        break;
                    }
                    done = TRUE;
                }
                break;
            case '0':
                item = player->getInventoryItem(0);
                if (item != NULL) {
                    msg << "Permanantely delete: " << item->getName() << "?";
                    updateConsole(msg.str().c_str());
                    msg.str("");
                    msg.clear();
                    if ((c = getch()) == 'y') {
                        player->setInventoryItem(0, NULL);
                        msg << item->getName() << " was permanantely delete.";
                        updateConsole(msg.str().c_str(), TRUE);
                        msg.str("");
                        msg.clear();
                        break;
                    }
                    done = TRUE;
                }
                break;
            case '1':
                item = player->getInventoryItem(1);
                if (item != NULL) {
                    msg << "Permanantely delete: " << item->getName() << "?";
                    updateConsole(msg.str().c_str());
                    msg.str("");
                    msg.clear();
                    if ((c = getch()) == 'y') {
                        player->setInventoryItem(1, NULL);
                        msg << item->getName() << " was permanantely delete.";
                        updateConsole(msg.str().c_str(), TRUE);
                        msg.str("");
                        msg.clear();
                        break;
                    }
                    done = TRUE;
                }
                break;
            case '2':
                item = player->getInventoryItem(2);
                if (item != NULL) {
                    msg << "Permanantely delete: " << item->getName() << "?";
                    updateConsole(msg.str().c_str());
                    msg.str("");
                    msg.clear();
                    if ((c = getch()) == 'y') {
                        player->setInventoryItem(2, NULL);
                        msg << item->getName() << " was permanantely delete.";
                        updateConsole(msg.str().c_str(), TRUE);
                        msg.str("");
                        msg.clear();
                        break;
                    }
                    done = TRUE;
                }
                break;        
            case '3':
                item = player->getInventoryItem(3);
                if (item != NULL) {
                    msg << "Permanantely delete: " << item->getName() << "?";
                    updateConsole(msg.str().c_str());
                    msg.str("");
                    msg.clear();
                    if ((c = getch()) == 'y') {
                        player->setInventoryItem(3, NULL);
                        msg << item->getName() << " was permanantely delete.";
                        updateConsole(msg.str().c_str(), TRUE);
                        msg.str("");
                        msg.clear();
                        break;
                    }
                    done = TRUE;
                }
                break;
            case '4':
                item = player->getInventoryItem(4);
                if (item != NULL) {
                    msg << "Permanantely delete: " << item->getName() << "?";
                    updateConsole(msg.str().c_str());
                    msg.str("");
                    msg.clear();
                    if ((c = getch()) == 'y') {
                        player->setInventoryItem(4, NULL);
                        msg << item->getName() << " was permanantely delete.";
                        updateConsole(msg.str().c_str(), TRUE);
                        msg.str("");
                        msg.clear();
                        break;
                    }
                    done = TRUE;
                }
                break;
            case '5':
                item = player->getInventoryItem(5);
                if (item != NULL) {
                    msg << "Permanantely delete: " << item->getName() << "?";
                    updateConsole(msg.str().c_str());
                    msg.str("");
                    msg.clear();
                    if ((c = getch()) == 'y') {
                        player->setInventoryItem(5, NULL);
                        msg << item->getName() << " was permanantely delete.";
                        updateConsole(msg.str().c_str(), TRUE);
                        msg.str("");
                        msg.clear();
                        break;
                    }
                    done = TRUE;
                }
                break;
            case '6':
                item = player->getInventoryItem(6);
                if (item != NULL) {
                    msg << "Permanantely delete: " << item->getName() << "?";
                    updateConsole(msg.str().c_str());
                    msg.str("");
                    msg.clear();
                    if ((c = getch()) == 'y') {
                        player->setInventoryItem(6, NULL);
                        msg << item->getName() << " was permanantely delete.";
                        updateConsole(msg.str().c_str(), TRUE);
                        msg.str("");
                        msg.clear();
                        break;
                    }
                    done = TRUE;
                }
                break;
            case '7':
                item = player->getInventoryItem(7);
                if (item != NULL) {
                    msg << "Permanantely delete: " << item->getName() << "?";
                    updateConsole(msg.str().c_str());
                    msg.str("");
                    msg.clear();
                    if ((c = getch()) == 'y') {
                        player->setInventoryItem(7, NULL);
                        msg << item->getName() << " was permanantely delete.";
                        updateConsole(msg.str().c_str(), TRUE);
                        msg.str("");
                        msg.clear();
                        break;
                    }
                    done = TRUE;
                }
                break;
            case '8':
                item = player->getInventoryItem(8);
                if (item != NULL) {
                    msg << "Permanantely delete: " << item->getName() << "?";
                    updateConsole(msg.str().c_str());
                    msg.str("");
                    msg.clear();
                    if ((c = getch()) == 'y') {
                        player->setInventoryItem(8, NULL);
                        msg << item->getName() << " was permanantely delete.";
                        updateConsole(msg.str().c_str(), TRUE);
                        msg.str("");
                        msg.clear();
                        break;
                    }
                    done = TRUE;
                }
                break;
            case '9':
                item = player->getInventoryItem(9);
                if (item != NULL) {
                    msg << "Permanantely delete: " << item->getName() << "?";
                    updateConsole(msg.str().c_str());
                    msg.str("");
                    msg.clear();
                    if ((c = getch()) == 'y') {
                        player->setInventoryItem(9, NULL);
                        msg << item->getName() << " was permanantely delete.";
                        updateConsole(msg.str().c_str(), TRUE);
                        msg.str("");
                        msg.clear();
                        break;
                    }
                    done = TRUE;
                }
                break;
            default:
                break;
        }
        done = TRUE;
    }
    // restore console info
    updateConsole("Tip: Press ESC to return to the game.");
    
    // update windows
    updateAbility();
    updateInventory();
    updateWeapon();
    updateArmor();
    
    if (wItem != NULL)
        wkill(wItem);
    wItem = NULL;
}