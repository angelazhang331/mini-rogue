#ifndef Weapons_h
#define Weapons_h

#include "Object.h"

class Actor;

class Mace : public Weapon {
public:
    Mace(Game* g);
    ~Mace();
};

class ShortSword : public Weapon {
public:
    ShortSword(Game* g);
    ~ShortSword();
};

class LongSword : public Weapon {
public:
    LongSword(Game* g);
    ~LongSword();
};

class MagicAxe : public Weapon {
public:
    MagicAxe(Game* g);
    ~MagicAxe();
};

class MagicFangs : public Weapon {
public:
    MagicFangs(Game* g);
    ~MagicFangs();
    void effect(Actor* a);
};

#endif /* Weapons_h */
