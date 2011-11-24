/**
 *  d20GameBuilder.H
 *  comp345-assignment-03
 *  
 */

#ifndef d20GAMEBUILDER_H
#define d20GAMEBUILDER_H

#include "d20Game.h"
#include "Map.h"
#include "Character.h"

class d20GameBuilder {
public:
    d20Game* getGame() { return game; }
    void createNewGame() { game = new d20Game(); }
    void setStaticGameComponent(Character*, Map*);
    
private:
    d20Game* game;
};

#endif
