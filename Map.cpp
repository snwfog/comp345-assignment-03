//
//  Map.cpp
//  comp345-assignment-02
//
//  Created by Charles Chao Yang on 11-11-03.

#include <iostream>
#include <fstream>
#include "Map.h"

std::ostream& operator <<(std::ostream& os, const MapObject& object) {
    switch (object.mapObjectType) {
        case EMPTY:
            os << " ";
            break;
        case WALL:
            os << "#";
            break;
        case MONSTER:
            os << "x";
            break;
        case PLAYER:
            os << "A";
            break;
        case CHEST:
            os << "o";
            break;
        default:
            os << " "; // EMPTY
            break;
    }
    
    return os;
}

std::istream& operator >>(std::istream& is, MapObject& object) {
    char c;
    is >> c;
    switch (c) {
        case '#':
            object.mapObjectType = WALL;
            break;
        case 'x':
            object.mapObjectType = MONSTER;
            break;
        case 'A':
            object.mapObjectType = PLAYER;
        case 'o':
            object.mapObjectType = CHEST;
        default:
            object.mapObjectType = EMPTY;
            break;
    }
    
    return is;
}

MapObject::MapObject(int y, int x, MapObjectType type) : y(y), x(x), mapObjectType(type) {}

// careful when using this constructor, because the y/x position
// are set to 0, this could cause problem in some cases
MapObject::MapObject() : y(0), x(0), mapObjectType(EMPTY) { }    

Map::Map() : mapname("untitled_map") {
    for (int y = 0; y < STD_Y; y++)
        for (int x = 0; x < STD_X; x++)
            mapObjectDatabase[y][x] = MapObject(y, x, EMPTY);
    
    // attach(observers)
}

Map::Map(std::string name) : mapname(name) {
    //  check if the map already exists
    std::ifstream in;
    std::string input;
    
    if (!in.fail()) {
        ldmap();
    } else {
        // create empty map
        for (int i = 0; i < STD_Y; i++)
            for (int j = 0; j < STD_X; j++)
                mapObjectDatabase[i][j] = MapObject(i, j, EMPTY);
    }
    in.close();
    
    // attach observers
}

Map::~Map() {
    // detach observers
}

void Map::ldmap() {
    std::ifstream in;
    in.open(mapname.c_str());
    
    for (int i = 0; i < STD_Y; i++) {
        for (int j = 0; j < STD_X; j++) {
            mapObjectDatabase[i][j] = MapObject(i, j, static_cast<MapObjectType>(in.get()));
        }
    }
}

void Map::save() {
    std::ofstream out;
    out.open(mapname.c_str());
    
    for (int i = 0; i < STD_Y; i++) {
        for (int j = 0; j < STD_X; j++) {
           out << mapObjectDatabase[i][j];
        }
    }
}

void Map::setAtLocation(int y, int x, MapObject object) {
    mapObjectDatabase[y][x] = object;
    notify();
}

MapObject* Map::getAtLocation(int y, int x) {
    return &mapObjectDatabase[y][x];
}

void Map::notify() {
    for (int i = 0; i < observers.size(); i++) {
        (observers[i])->update(this);
    }
}

void Map::attach(Observer* ob) {
    observers.push_back(ob);
}
