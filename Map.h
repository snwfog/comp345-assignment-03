/**
 *  Map.h
 *  comp345-assignment-03
 *
 *  Same as from assignment 2. Class that represents
 *  a Map object. Added the "level" member variable
 *  such that Map with different level will possibly
 *  contains chest with corresponding level of items.
 *
 */

#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <iostream>

using std::string;

// maximum width of stdscr
const int STD_X = 80-16;
// maximum height of stdscr
const int STD_Y = 25-1;

// character representation of the game objects
enum MapObjectType { EMPTY = ' ', WALL = '#', MONSTER = 'x', PLAYER = 'A', TREASURE_CHEST = 'n', ENTRANCE = 'O', EXIT = '@' };

// structure to represent game objects
struct MapObject {
    int y, x;
    // type should contains the name of the type in later version
    MapObjectType mapObjectType;
    MapObject();
    MapObject(int, int, MapObjectType);
    friend std::ostream& operator <<(std::ostream& os, const MapObject& object);
    friend std::istream& operator >>(std::istream& is, MapObject& object);
};


// forward declare
class Map;

// observer abstract class
class Observer {
public:
    Observer() { };
    ~Observer() { };
    
    virtual void update(Map*) = 0;
};

class Map {
private:
    string mapname;
    int mapLevel;
    // observers vectors
    std::vector<Observer*> observers;
    // map objects database
    MapObject mapObjectDatabase[STD_Y][STD_X]; 
    // helping functions
    void ldmap();

public:
    Map();
    Map(string);
    ~Map();
    
    string getmapname() { return mapname; };
    MapObject* getAtLocation(int, int);
    int getMapLevel() { return mapLevel; }

    void setName(string n) { mapname = n; }
    void setAtLocation(int, int, MapObject);
    void setMapLevel(int lvl) { mapLevel = lvl; } 
    
    void save();
    
    // function added for assignment 2
    // obeservers pattern
    void attach(Observer*);
    //void detach(const Observer&);
    void notify();
};

#endif