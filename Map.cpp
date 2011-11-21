/**
 *  Map.cpp
 *  comp345-assignment-03
 *
 */

#include <fstream>
#include "Map.h"

std::ostream& operator <<(std::ostream& os, const MapObject& object) {
    switch (object.mapObjectType) {
        case WALL:
            os << "#";
            break;
        case MONSTER:
            os << "x";
            break;
        case PLAYER:
            os << "A";
            break;
        case TREASURE_CHEST:
            os << "n";
            break;
        case ENTRANCE:
            os << "O";
            break;
        case EXIT:
            os << "@";
            break;
        case MERCHANT:
            os << "Y";
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
            break;
        case 'n':
            object.mapObjectType = TREASURE_CHEST;
            break;
        case 'O':
            object.mapObjectType = ENTRANCE;
            break;
        case '@':
            object.mapObjectType = EXIT;
            break;
        case 'Y':
            object.mapObjectType = MERCHANT;
            break;
        default:
            object.mapObjectType = EMPTY;
            break;
    }
    
    return is;
}

MapObject::MapObject(int y, int x, MapObjectType type) : y(y), x(x), mapObjectType(type) {}

MapObject::MapObject() : y(0), x(0), mapObjectType(EMPTY) { }    

Map::Map() {
    for (int y = 0; y < STD_Y; y++)
        for (int x = 0; x < STD_X; x++)
            mapObjectDatabase[y][x] = MapObject(y, x, EMPTY);
}

Map::Map(std::string name) : mapname(name) {
    //  check if the map already exists
    std::ifstream in;
    in.open(name.c_str());
    
    if (!in.fail()) {
        ldmap();
    } else {
        // create empty map
        for (int i = 0; i < STD_Y; i++) {
            for (int j = 0; j < STD_X; j++) {
                mapObjectDatabase[i][j] = MapObject(i, j, EMPTY);
            }
        }
    }
    
    in.close();
}

Map::~Map() {}

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
    return &(mapObjectDatabase[y][x]);
}

void Map::notify() {
    for (int i = 0; i < observers.size(); i++) {
        (observers[i])->update(this);
    }
}

void Map::attach(MapObserver* ob) {
    observers.push_back(ob);
}
