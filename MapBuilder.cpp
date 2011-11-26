//
//  MapBuilder.cpp
//  comp345-assignment-03
//
//  Created by Charles Chao Yang on 11-11-19.

#include <iostream>
#include "MapBuilder.h"

void ArenaBuilder::placeMapObject() {
    // place the walls
    for (int i = 0; i < 9; i++) {
        map->setAtLocation(8, 28+i, MapObject(8, 28+i, WALL));
        map->setAtLocation(16, 28+i, MapObject(16, 28+i, WALL));
        map->setAtLocation(8+i, 28, MapObject(8+i, 28, WALL));
        map->setAtLocation(8+i, 36, MapObject(8+i, 36, WALL));
    }
    
    // set entrance
    map->setAtLocation(8, 32, MapObject(8, 32, ENTRANCE));

    // set exit
    map->setAtLocation(16, 32, MapObject(16, 32, EXIT));
    
    // set chest
    map->setAtLocation(13, 32, MapObject(13, 32, TREASURE_CHEST));
    
    // set monster
    map->setAtLocation(12, 32, MapObject(14, 32, MONSTER));
    map->setAtLocation(10, 32, MapObject(14, 32, MONSTER));
    
    // set player location
    map->setAtLocation(9, 32, MapObject(9, 32, PLAYER));
    
    // set merchant location
    map->setAtLocation(15, 32, MapObject(15, 32, MERCHANT));
}