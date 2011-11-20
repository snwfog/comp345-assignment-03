/**
 *  MapBuilder.h
 *  comp345-assignment-03
 *
 *  MapBuilder, ArenaBuilder, MapGenerator
 *  This file implements the MapBuilder class, as
 *  required from assignment 3. MapBuilder is the interface
 *  builder class, ArenaBuilder implements MapBuilder and place
 *  the corresponding map elements on the map to make the
 *  "arena". MapGenerator contains a MapBuilder and has
 *  the ability to generates different kind of map from
 *  its MapBuilder.
 *
 */

#ifndef MAPBUILDER_H
#define MAPBUILDER_H

#include "Map.h"


/**
 * MapBuilder Inteface
 */
class MapBuilder {
public:
    Map* getMap() { return map; }
    void createNewMap() { map = new Map(); }
    void setName(string name) { map->setName(name); }
    void setMapLevel(int lvl = 0) { map->setMapLevel(lvl); }
    /**
     * placeMapObject method. Must be virtually overloaded to
     * place different objects at different location to 
     * create different type of map builder. For example
     * ArenaBuilder (coming up the next class),
     * or different DungeonBuilders (for example).
     */
    virtual void placeMapObject() = 0;

protected:
    Map* map;
};

/**
 * ArenaBuilder, implements MapBuilder. Build a 9x9 arena
 * map, as instructed by assignment 3, with a guardian, and
 * a potentially random generated chest. For random generated
 * chest, please see ChestBuilder.h and .cpp.
 */
class ArenaBuilder : public MapBuilder {
public:
    void placeMapObject();
};

/**
 * MapGenerator, director of MapBuilders. Can construct
 * different type of map by invoking the constructMap()
 * method, which itself calls the overloaded methods from
 * MapBuilders.
 */
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
