/**
 *  MapEditor.cpp
 *  comp345-assignment-03
 *
 */

#include <iostream>
#include <sstream>
#include "MapEditor.h"

// struct for cursor object
Cursor::Cursor(int y, int x) : y(y), x(x) { }
Cursor::Cursor() : y((STD_Y)/2), x((STD_X)/2) { }

MapEditor::MapEditor() {
    // ncurses initialization funcs
    initscr();
    noecho();
    curs_set(0);
    raw();
    keypad(stdscr, TRUE);
    wclear(stdscr);
    refresh();
    // end of ncurses initialization funcs
    
    // initialize member variables
    csr = new Cursor();
    pmap = new Map();
    wlgd = createLegendWindow();
    wdlg = createDialogueWindow();
    
    // attach itself to the observers
    pmap->attach(this);
    
    // flush the map
    refreshmap();
    
    // show the cursor
    mvcsr(NULL);
    
    // set the initial cursor to blinking
    attron(A_BLINK);
    mvwprintw(stdscr, csr->y, csr->x, "_");
    attroff(A_BLINK);
    refresh();
    
    // go edit mode
    edit();
    
    // end ncurses
    endwin();
}

MapEditor::MapEditor(Map* map) {
    // ncurses initialization funcs
    initscr();
    noecho();
    curs_set(0);
    raw();
    keypad(stdscr, TRUE);
    wclear(stdscr);
    refresh();
    // end of ncurses initialization funcs
    
    // initialize member variables
    csr = new Cursor();
    pmap = map;
    wlgd = createLegendWindow();
    wdlg = createDialogueWindow();
    
    // attach itself to the observers
    pmap->attach(this);
    
    // flush the map 
    refreshmap();
    
    // show the cursor
    mvcsr(NULL);
    
    // set the initial cursor to blinking
    MapObject* tmp = pmap->getAtLocation(csr->y, csr->x);
    attron(A_BLINK | A_UNDERLINE);
    mvwprintw(stdscr, csr->y, csr->x, "%c", static_cast<char>(tmp->mapObjectType));
    attroff(A_BLINK | A_UNDERLINE);
    refresh();
    
    // go edit mode
    edit();
    
    // end ncurses
    endwin();
}

MapEditor::MapEditor(std::string name) {
    // ncurses initialization funcs
    initscr();
    noecho();
    curs_set(0);
    raw();
    keypad(stdscr, TRUE);
    wclear(stdscr);
    refresh();
    // end of ncurses initialization funcs
    
    // initialize member variables
    csr = new Cursor();
    pmap = new Map(name);
    wlgd = createLegendWindow();
    wdlg = createDialogueWindow();
    
    // attach itself to the observers
    pmap->attach(this);
    
    // flush the map 
    refreshmap();
    
    // show the cursor
    mvcsr(NULL);
    
    // set the initial cursor to blinking
    MapObject* tmp = pmap->getAtLocation(csr->y, csr->x);
    attron(A_BLINK | A_UNDERLINE);
    mvwprintw(stdscr, csr->y, csr->x, "%c", static_cast<char>(tmp->mapObjectType));
    attroff(A_BLINK | A_UNDERLINE);
    refresh();
    
    // go edit mode
    edit();
    
    // end ncurses
    endwin();
}

MapEditor::~MapEditor() {
    // save();
    delete pmap;
    pmap = NULL;
    
    delete csr;
    csr = NULL;
    
    endwin();
}

WINDOW* MapEditor::createLegendWindow() {
    // create the legend window
    WINDOW* pwTemp = newwin(STD_Y+1, 16, 0, STD_X);
    // change the border style of the legend window
    wborder(pwTemp, '|', '|', '-', '-', '+', '+', '+', '+');
    // print the legend text
    mvwprintw(pwTemp, 1, 1, " LEGEND   ");
    
    mvwprintw(pwTemp, 3, 1, " # [w]all");
    mvwprintw(pwTemp, 4, 1, " A [p]layer");
    mvwprintw(pwTemp, 5, 1, " n [c]hest");
    mvwprintw(pwTemp, 6, 1, " x [m]onster");
    mvwprintw(pwTemp, 7, 1, " Y merchan[t]");
    mvwprintw(pwTemp, 8, 1, " O [e]ntrace");
    mvwprintw(pwTemp, 9, 1, " @ e[x]it");
    
    mvwprintw(pwTemp, 11, 1, " [a]uto walls");
    // disabled, specific of door have not been determined
    
    mvwprintw(pwTemp, 12, 1, " [r]emove");
    
    //mvwprintw(pwTemp, 13, 1, " (s)ave map");
    mvwprintw(pwTemp, 14, 1, " [q]uit");
    
    // display the legend window
    wrefresh(pwTemp);
    return pwTemp;
}

WINDOW* MapEditor::createDialogueWindow() {
    WINDOW* pwTemp = newwin(1, STD_X, STD_Y, 0);
    
    // display the dialog window (empty for now)
    wrefresh(pwTemp);
    return pwTemp;
}

void MapEditor::edit() {
    int c;
    while ((c = getch()) != 'q') {
        switch (c) {
            case KEY_LEFT:
            case KEY_RIGHT:
            case KEY_UP:
            case KEY_DOWN:
                mvcsr(c);
                break;
            case 'w':
            case 'p':
            case 'c':
            case 'm':
            case 'r':
            case 'e':
            case 'x':
            case 't':
                addatcsr(c);
                break;
            case 'a':
                autowall();
                break;
            default:
                // mvwprintw(pwDialog, 0, 0, "Error: Unrecognized option. ");
                // wrefresh(pwDialog);
                break;
        }
    }
    
    // when quitting, save the current map
    printwdlg("saving the current map as: " + pmap->getmapname());
    usleep(1000000);
    pmap->save();
    
    // end ncurses
    endwin();
}

void MapEditor::mvcsr(int c) {
    switch (c) {
        case KEY_LEFT:
            mvcsrpos(csr->y, csr->x-1);
            break;
        case KEY_RIGHT:
            mvcsrpos(csr->y, csr->x+1);
            break;
        case KEY_UP:
            mvcsrpos(csr->y-1, csr->x);
            break;
        case KEY_DOWN:
            mvcsrpos(csr->y+1, csr->x);
            break;
        default:
            mvcsrpos(csr->y, csr->x);
            break;
    }
}

void MapEditor::mvcsrpos(int y, int x) {
    // check if y and x are out of the stdscr boundaries
    if (!(y >= STD_Y || y < 0 || x >= STD_X || x < 0)) {
        
        // restore old cursor pos object
        // this should happen without notifying the user, i.e. its not an intentional change
        // from the user, but just to display on the GUI
        MapObject* tmp = pmap->getAtLocation(csr->y, csr->x);
        if (tmp->mapObjectType == EMPTY) {
            // print empty space at current cursor pos
            mvwprintw(stdscr, csr->y, csr->x, " ");
        } else {
            // print the object in the game obj db's
            mvwprintw(stdscr, csr->y, csr->x, "%c", static_cast<char>(tmp->mapObjectType));
        }
        
        // update cursor coordinate
        csr->x = x;
        csr->y = y;
        
        // retrieve game object at new csr pos
        tmp = pmap->getAtLocation(csr->y, csr->x);
        if (tmp->mapObjectType == EMPTY) {
            // turn on the blinking attribute of stdscr
            attron(A_BLINK);
            mvwprintw(stdscr, y, x, "_");
            attroff(A_BLINK);
            refresh();
        } else {
            attron(A_BLINK | A_UNDERLINE);
            mvwprintw(stdscr, y, x, "%c", static_cast<char>(tmp->mapObjectType));
            attroff(A_BLINK | A_UNDERLINE);
            refresh();
        }
        
        std::stringstream msg;
        msg << "cursor: " << csr->y << "y, " << csr->x << "x";
        printwdlg(msg.str());
    }
}

void MapEditor::refreshmap() {
    for (int y = 0; y < STD_Y; y++) {
        for (int x = 0; x < STD_X; x++) {
            mvwprintw(stdscr, y, x, "%c", (pmap->getAtLocation(y, x))->mapObjectType);
        }
    }
    
    // refresh the cursor makes it all blinky by itself ;D
    // mvcsr(NULL);   
    refresh();
}

void MapEditor::addatcsr(int c) {
    MapObjectType tmp;
    switch (c) {
        case 'w':
            tmp = WALL; 
            break;
        case 'p':
            tmp = PLAYER;
            // remove the old player
            for (int i = 0; i < STD_Y; i++) {
                for (int j = 0; j < STD_X; j++) {
                    if ((pmap->getAtLocation(i, j))->mapObjectType == PLAYER)
                        pmap->setAtLocation(i, j, MapObject(i, j, EMPTY));
                }
            }
            break;
        case 'e':
            tmp = ENTRANCE;
            // remove the old door
            for (int i = 0; i < STD_Y; i++) {
                for (int j = 0; j < STD_X; j++) {
                    if ((pmap->getAtLocation(i, j))->mapObjectType == ENTRANCE)
                        pmap->setAtLocation(i, j, MapObject(i, j, EMPTY));
                }
            }
            break;
        case 'x':
            tmp = EXIT;
            // remove the old exit
            for (int i = 0; i < STD_Y; i++) {
                for (int j = 0; j < STD_X; j++) {
                    if ((pmap->getAtLocation(i, j))->mapObjectType == EXIT)
                        pmap->setAtLocation(i, j, MapObject(i, j, EMPTY));
                }
            }
            break;
        case 'c':
            tmp = TREASURE_CHEST;
            break;
        case 'm':
            tmp = MONSTER;
            break;
        case 'r':
            tmp = EMPTY;
            break;
        case 't':
            tmp = MERCHANT;
            break;
        default:
            tmp = EMPTY;
            break;
    }
    pmap->setAtLocation(csr->y, csr->x, MapObject(csr->y, csr->x, tmp));
    refreshmap();
}

void MapEditor::autowall() {
    int y1 = csr->y;
    int x1 = csr->x;
    int y2, x2, c;
    
    printwdlg("auto wall mode on, press 'a' again to confirm wall location");
    
    while ((c = getch()) != 'a') {
        // allow cursor movement
        switch (c) {
            case KEY_LEFT:
            case KEY_RIGHT:
            case KEY_UP:
            case KEY_DOWN:
                refreshmap();
                mvcsr(c);
                y2 = csr->y;
                x2 = csr->x;
                // create walls preview
                for (int i = y1; i <= y2; i++) {
                    mvwprintw(stdscr, i, x1, "#");
                    mvwprintw(stdscr, i, x2, "#");
                }
                for (int i = x1; i <= x2; i++) {
                    mvwprintw(stdscr, y1, i, "#");
                    mvwprintw(stdscr, y2, i, "#");
                }
                refresh();
                break;
            default:
                printwdlg("error: only arrow keys are accepted");
                break;
        }
    }
    // confirm placement of the walls
    // destroying all previous data's
    for (int i = y1; i <= y2; i++) {
        pmap->setAtLocation(i, x1, MapObject(i, x1, WALL));
        pmap->setAtLocation(i, x2, MapObject(i, x1, WALL));
    }            
    for (int i = x1; i <= x2; i++) {
        pmap->setAtLocation(y1, i, MapObject(y1, i, WALL));
        pmap->setAtLocation(y2, i, MapObject(y2, i, WALL));
    }
    refreshmap();
    printwdlg("auto wall mode completed");
}

void MapEditor::printwdlg(std::string str) {
    wclear(wdlg);
    mvwprintw(wdlg, 0, 0, str.c_str());
    wrefresh(wdlg);
}

void MapEditor::update(Map* map) {
    std::stringstream msg;
    msg << "inserted " << static_cast<char>((map->getAtLocation(csr->y, csr->x))->mapObjectType) << " at " << csr->y << "y, " << csr->x << "x";
    printwdlg(msg.str());
}


