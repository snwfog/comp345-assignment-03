//
//  MapBuilder.h
//  comp345-assignment-03
//
//  Created by Charles Chao Yang on 11-11-19.

#ifndef MAPBUILDER_H
#define MAPBUILDER_H
#include "Map.h"

class MapBuilder {
public:
    Map* getMap() { return map; }
    void createNewMap() { map = new Map(); }
    void setName(string name) { map->setName(name); }
    virtual void placeMapObject() = 0;
    
protected:
    Map* map;
};

class ArenaBuilder : public MapBuilder {
public:
    void placeMapObject();
};

class MapGenerator {
public:
    void setMapBuilder(MapBuilder* mb) { mapBuilder = mb; }
    Map* getMap() { return mapBuilder->getMap(); }
    void constructMap() {
        mapBuilder->createNewMap();
        mapBuilder->setName("Arena Map");
        mapBuilder->placeMapObject();
    }
    
private:
    MapBuilder* mapBuilder;
};

#endif
