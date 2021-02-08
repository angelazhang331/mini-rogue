#ifndef Scrolls_h
#define Scrolls_h

#include "Object.h"

class Game;

class Teleportation : public Scroll {
public:
    Teleportation(Game* g);
    ~Teleportation();
    
    void effect(Actor* a);
};

class Strength : public Scroll {
public:
    Strength(Game* g);
    ~Strength();
    void effect(Actor* a);
};

class Health : public Scroll {
public:
    Health(Game* g);
    ~Health();
    void effect(Actor* a);
};

class Armor : public Scroll {
public:
    Armor(Game* g);
    ~Armor();
    void effect(Actor* a);
};

class Dexterity : public Scroll {
public:
    Dexterity(Game* g);
    ~Dexterity();
    void effect(Actor* a);
};

#endif /* Scrolls_h */
