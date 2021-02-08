#include "Actor.h"
#include "Game.h"
#include "Dungeon.h"
#include "Weapons.h"
#include "utilities.h"
#include "globals.h"

#include <string>

using namespace std;

Actor::Actor(int hp, Weapon* w, int a, int s, int d, int sl, Game* g, string at)
{
    m_hitpoints = hp;
    m_weapon = w;
    m_armor = a;
    m_strength = s;
    m_dexterity = d;
    m_sleep = sl;
    m_game = g;
    m_actorType = at;
    m_maxHP = PLAYER_HP;
    setPos();
}

Actor::~Actor()
{
}

// ACCESSORS

int Actor::row() const
{
    // return actor current row
    return m_row;
}

int Actor::col() const
{
    // return actor current column
    return m_col;
}

int Actor::hitpoints() const
{
    // return actor current hit points
    return m_hitpoints;
}

Weapon* Actor::weapon() const
{
    // return actor current weapon
    return m_weapon;
}

int Actor::armor() const
{
    // return actor current armor points
    return m_armor;
}

int Actor::strength() const
{
    // return actor current strength points
    return m_strength;
}

int Actor::dexterity() const
{
    // return actor current dexterity points
    return m_dexterity;
}

int Actor::sleep() const
{
    // return actor current sleep time
    return m_sleep;
}

Game* Actor::game() const
{
    // return reference to the game that contains the actor
    return m_game;
}

std::string Actor::type() const
{
    // return the actor type
    return m_actorType;
}

// SETTERS

void Actor::setRow(const int& r)
{
    // set actor current row
    m_row = r;
}

void Actor::setCol(const int& c)
{
    // set actor current column
    m_col = c;
}

void Actor::setWep(Weapon*& w)
{
    // set actor current weapon
    m_weapon = w;
}

void Actor::setStrength(const int& s)
{
    // if greater than upper limit, set to upper limit
    if(s >= 99)
        m_strength = 99;
    // if less than upper limit, set desired value
    else
        m_strength = s;
}

void Actor::setMaxHp(const int& max)
{
    // if greater than upper limit, set to upper limit
    if(max >= 99)
        m_maxHP = 99;
    // if less than upper limit, set desired value
    else
        m_maxHP = max;
}

void Actor::setSleep(const int& s)
{
    // if greater than upper limit, set to upper limit
    if(s >= 9)
        m_sleep = 9;
    // if less than upper limit, set desired value
    else
        m_sleep = s;
}

// INCREASE VALUES

void Actor::incHP(const int& change)
{
    // if attempting to increase past the max, set to max
    if(m_hitpoints + change >= m_maxHP)
        m_hitpoints = m_maxHP;
    // if attempting to decrease past 0, set to 0
    else if(m_hitpoints + change <= 0)
        m_hitpoints = 0;
    // otherwise set it to the desired value
    else
        m_hitpoints += change;
}

void Actor::incArmor(const int& change)
{
    // if result is greater than max, then set to max.
    if(m_armor + change >= 99)
        m_armor = 99;
    // if resulting value is not greater than max, set to resulting value
    else
        m_armor += change;
    // function will never decrease value, so no lower limit check
}

void Actor::incStrength(const int& change)
{
    // if result is greater than max, then set to max
    if(m_strength + change >= 99)
        m_strength = 99;
    // if resulting value is not greater than max, set to resulting value
    else
        m_strength += change;
    // function will never decrease value, so no lower limit check
}

void Actor::incDex(const int& change)
{
    // if result is greater than max, then set to max
    if(m_dexterity + change >= 99)
        m_dexterity = 99;
    // if resulting value is not greater than max, set to resulting value
    else
        m_dexterity += change;
    // function will never decrease value, so no lower limit check
}

void Actor::decSleep(const int& change)
{
    // if result is less than 0, then set to 0
    if(m_sleep - change <= 0)
        m_sleep = 0;
    // otherwise set to resulting value
    else
        m_sleep -= change;
    // function will not increase so no upper limit check
}

std::string Actor::attack(Actor* a) const
{
    // return value: a string describing what just happened
    std::string s = type() + " " + weapon()->action() + " " + weapon()->name() + " at " + a->type();;
    
    // calculate whether the actor hits or misses its target
    int attackerPoints = dexterity() + weapon()->dexBonus();
    int defenderPoints = a->dexterity() + a->armor();
    if(randInt(1, attackerPoints) >= randInt(1, defenderPoints))
    {
        // if the actor hits its target, modify the target
        s += a->getHit(this);
    }
    else
    {
        s += " and misses.";
    }
    return s;
}

std::string Actor::getHit(const Actor* a)
{
    std::string s = " and hits";
    
    // if the actor is hit by Actor* a
    int currS = sleep();
    
    // determines how many hitpoints the attack took
    int damagePoints = randInt(0, a->strength() + a->weapon()->damageBonus() - 1);
    incHP(-damagePoints);
    
    // if the weapon used has another effect (like sleep), apply to hit actor (this)
    a->weapon()->effect(this);
    
    // if the actor (this) died
    if(hitpoints() <= 0)
    {
        // kill the actor in the game
        s = " dealing a final blow";
        killActor();
    }
    
    // if sleep is added, return this
    else if(sleep() > 0 && sleep() > currS)
    {
        s += ", putting " + type() + " to sleep";
    }
    s += ".";
    return s;
}

void Actor::setPos()
{
    // places the actor at an empty position in the dungeon.
    char pos;
    do {
        m_row = randInt(0, DUNGEON_ROWS - 1);
        m_col = randInt(0, DUNGEON_COLUMNS - 1);
        pos = game()->dungeon()->at(m_row, m_col);
    } while(pos != ' ');
}
