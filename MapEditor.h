/**
 *  MapEditor.h
 *  comp345-assignment-03
 * 
 *  Same as from assignment 2. This class loads the map
 *  and allows map edits.
 */
#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <ncurses.h>
#include "Map.h"

// struct for cursor object
struct Cursor {
    int y, x;
    Cursor(int, int);
    Cursor();
};

class MapEditor : Observer {
public:
    MapEditor();
    MapEditor(Map*);
    MapEditor(std::string);
    ~MapEditor();
    void wrtdlg(std::string);
    void update(Map*);
    
private:
    Map* pmap;
    Cursor* csr; // the cursor
    WINDOW* wlgd; // legend window
    WINDOW* wdlg; // dialogue window
    
    WINDOW* createLegendWindow();
    WINDOW* createDialogueWindow();
    
    void edit();
    void printwdlg(std::string);
    void mvcsr(int);
    void mvcsrpos(int, int);
    void refreshmap();
    void addatcsr(int);
    void autowall();
    
    
};
#endif
