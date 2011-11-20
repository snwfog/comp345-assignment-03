/**
 *  Character.h
 *  comp345-assignment-03
 *
 */

#ifndef CHARACTERBUILDER_H
#define CHARACTERBUILDER_H
#include "Character.h"


class CharacterBuilder {
public:
    Character* getCharacter() { return character; }
    void createNewCharacter() { character = new Character(); }
    
    void setBaseAbilityScore(Attribute*);
    virtual void initializeCharacterType() = 0;
protected:
    Character* character;
};

class BullyBuilder : public CharacterBuilder {
public:
    void initializeCharacterType();
};

class NimbleBuilder : public CharacterBuilder {
public:
    void initializeCharacterType();
};

class TankBuilder : public CharacterBuilder {
public:
    void initializeCharacterType();
};

class FighterGenerator {
public:
    Character* getCharacter() { return characterBuilder->getCharacter(); }
    void setCharacterBuilder(CharacterBuilder* cb) { characterBuilder = cb; }
    void createNewFighter();
    void createNewFighter(string name);
private:
    CharacterBuilder* characterBuilder;
};
#endif
