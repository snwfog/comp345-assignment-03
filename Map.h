//
//  Map.h
//  comp345-assignment-02
//
//  Created by Charles Chao Yang on 11-11-03.


#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>

// maximum width of stdscr
const int STD_X = 80-16;
// maximum height of stdscr
const int STD_Y = 25-1;

// character representation of the game objects
enum MapObjectType { EMPTY = ' ', WALL = '#', MONSTER = 'x', PLAYER = 'A', CHEST = 'n', ENTRANCE = 'O', EXIT = '@' };

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
    std::string mapname;
    // observers vectors
    std::vector<Observer*> observers;
    // map objects database
    MapObject mapObjectDatabase[STD_Y][STD_X]; 
    // helping functions
    void ldmap();

public:
    Map();
    Map(std::string);
    ~Map();
    
    std::string getmapname() { return mapname; };
    void save();
    void setAtLocation(int, int, MapObject);
    MapObject* getAtLocation(int, int);

    // function added for assignment 2
    // obeservers pattern
    void attach(Observer*);
    //void detach(const Observer&);
    void notify();
};

#endif