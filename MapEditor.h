//
//  MapEditor.h
//  comp345-assignment-02
//
//  Created by Charles Chao Yang on 11-11-03.

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
