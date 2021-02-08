#include "Scrolls.h"
#include "Actor.h"
#include "utilities.h"

// Scroll of Teleportation

Teleportation::Teleportation(Game* g) : Scroll(g) {
    setAct("\nYou feel your body wrenched in space and time.");
    setName("scroll of teleportation");
}

Teleportation::~Teleportation() {
    
}

void Teleportation::effect(Actor *a) {
    //The player is randomly moved to another place in the level that is not occupied by a wall or a monster.
    a->setPos();
}

// Scroll of Strength

Strength::Strength(Game* g) : Scroll(g) {
    setAct("\nYour muscles bulge.");
    setName("scroll of strength");
}

Strength::~Strength() {
    
}

void Strength::effect(Actor* a) {
    //The player's armor points are increased by a random integer from 1 to 3.
    int increase = randInt(1,3);
    a->incStrength(increase);
}

// Scroll of Health

Health::Health(Game* g) : Scroll(g) {
    setAct("\nYou feel your heart beating stronger.");
    setName("scroll of enhance health");
}

Health::~Health() {
    
}

void Health::effect(Actor* a) {
    // The player's maximum hit point value is increased by a random integer from 3 to 8. This scroll does not affect the player's current number of hit points.
    int increase = randInt(3,8);
    a->incHP(increase);
}

// Scroll of Armor

Armor::Armor(Game* g) : Scroll(g) {
    setAct("\nYour armor glows blue.");
    setName("scroll of enhance armor");
}

Armor::~Armor() {
    
}

void Armor::effect(Actor* a) {
    //The player's armor points are increased by a random integer from 1 to 3.
    int increase = randInt(1,3);
    a->incArmor(increase);
}

// Scroll of Dexterity

Dexterity::Dexterity(Game* g):Scroll(g) {
    setAct("\nYou feel like less of a klutz.");
    setName("scroll of enhance dexterity");
}

Dexterity::~Dexterity() {
    
}

void Dexterity::effect(Actor* a) {
    // The player's dexterity is increased by 1.
    a->incDex(1);
}
