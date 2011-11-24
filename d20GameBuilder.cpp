/**
 *  d20GameBuilder.cpp
 *  comp345-assignment-03
 *  
 */

#include <iostream>
#include "d20GameBuilder.h"

void d20GameBuilder::setStaticGameComponent(Character* c, Map* m) {
    game->setPlayer(c);
    game->setMap(m);
}