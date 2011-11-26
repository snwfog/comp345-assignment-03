/**
 *  Character.h
 *  comp345-assignment-03
 *
 */

#ifndef CHARACTERBUILDER_H
#define CHARACTERBUILDER_H
#include "Character.h"
#include "ItemBuilder.h"

class CharacterBuilder {
public:
    Character* getCharacter() { return character; }
    void createNewCharacter() { character = new Character(); }
    
    void setBaseAbilityScore(Attribute*);
    virtual void initializeCharacter() = 0;
protected:
    Character* character;
};

class BullyBuilder : public CharacterBuilder {
public:
    void initializeCharacter();
};

class NimbleBuilder : public CharacterBuilder {
public:
    void initializeCharacter();
};

class TankBuilder : public CharacterBuilder {
public:
    void initializeCharacter();
};

class MonsterBuilder : public CharacterBuilder {
public:
    void initializeCharacter();
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
