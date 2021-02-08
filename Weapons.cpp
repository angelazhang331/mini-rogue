#include "Weapons.h"
#include "Actor.h"
#include "globals.h"
#include "utilities.h"

#include <string>

// MACE

Mace::Mace(Game* g) : Weapon(g) {
    setDex(MACE_DEX);
    setDamage(MACE_DAMAGE);
    setName("mace");
    setAction("swings");
}

Mace::~Mace() {
    
}

// SHORT SWORD

ShortSword::ShortSword(Game* g) : Weapon(g) {
    setDex(SS_DEX);
    setDamage(SS_DAMAGE);
    setName("short sword");
    setAction("slashes");
}

ShortSword::~ShortSword() {
    
}

// LONG SWORD

LongSword::LongSword(Game* g) : Weapon(g) {
    setDex(LS_DEX);
    setDamage(LS_DAMAGE);
    setName("long sword");
    setAction("swings");
}

LongSword::~LongSword() {
    
}

// MAGIC AXE

MagicAxe::MagicAxe(Game* g) : Weapon(g) {
    setDex(MA_DEX);
    setDamage(MA_DAMAGE);
    setName("magic axe");
    setAction("chops");
}

MagicAxe::~MagicAxe() {
    
}

// MAGIC FANGS

MagicFangs::MagicFangs(Game* g) : Weapon(g) {
    setDex(MF_DEX);
    setDamage(MF_DAMAGE);
    setName("magic fangs");
    setAction("strikes");
}

MagicFangs::~MagicFangs() {
    
}

void MagicFangs::effect(Actor* a) {
    // if fangs are used, there is a 1 in 5 chance the actor is put to sleep
    if(trueWithProbability(1./5.))
    {
        // if the new sleep time is more than the old sleep time, change
        int sleep = randInt(2, 6);
        if(sleep >= a->sleep())
        {
            a->setSleep(sleep);
        }
    }
}
