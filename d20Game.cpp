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

// create basic stats windows
WINDOW* d20Game::createWindowBasic() {
    WINDOW* win = newwin(4, 16, 0, 0);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    return win;
}

WINDOW* d20Game::createWindowVital() {
    WINDOW* win = newwin(6, 16, 3, 0);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    return win;
}

WINDOW* d20Game::createWindowAbility() {
    WINDOW* win = newwin(8, 16, 8, 0);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    return win;
}

WINDOW* d20Game::createWindowOption() {
    WINDOW* win = newwin(10, 16, 15, 0);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    return win;
}

// observer updates on basic stats windows
void d20Game::updateBasic() {
    mvwprintw(wBasic, 1, 2, player->getName().c_str());
    mvwprintw(wBasic, 2, 2, player->getCharacterClass().c_str());
    wrefresh(wBasic);
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

void d20Game::updateOption() {
    mvwprintw(wOption, 1, 2, "[i]nventory");
    mvwprintw(wOption, 2, 2, "[q]uit");
    wrefresh(wOption);
}

// create/update console window
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
                //ext_char_pane();
                break;
            case 'q':
                updateConsole("Are you sure you want to end the game? (y/n) "); 
                if ((c = getch()) == 'y')
                    quit = TRUE;
                break;
            default:
                break;
        }
    }
}

/**
 * Game playing/interface helping functions
 */ 
void d20Game::wkill(WINDOW* win) {
    wborder(win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wclear(win);
    wrefresh(win);
    delwin(win);
}


