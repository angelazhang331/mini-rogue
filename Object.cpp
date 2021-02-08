#include "Object.h"
#include "Game.h"
#include "Dungeon.h"
#include "globals.h"
#include "utilities.h"

/// OBJECT BASE CLASS

Object::Object(Game* g) {
    m_game = g;
    setPos();
}

Object::~Object(){
    
}

// ACCESSORS

int Object::row() const {
    // return object current row
    return m_row;
}

int Object::col() const {
    // return object current column
    return m_col;
}

std::string Object::name() const {
    // return object name
    return m_name;
}

Game* Object::game() const {
    // return reference to the game the object is created in
    return m_game;
}

// SETTERS

void Object::setRow(const int& r) {
    // set current row
    m_row = r;
}

void Object::setCol(const int& c) {
    // set current column
    m_col = c;
}

void Object::setName(const std::string& n) {
    // set object name
    m_name = n;
}

// GENERATE HELPER FUNCTION

void Object::setPos() {
    // set object position until it is placed in an empty grid location
    char pos;
    do {
        m_row = randInt(0, DUNGEON_ROWS - 1);
        m_col = randInt(0, DUNGEON_COLUMNS - 1);
        pos = game()->dungeon()->at(m_row, m_col);
    } while(pos != ' ');
}

/// WEAPON DERIVED CLASS

Weapon::Weapon(Game* g) : Object(g) {
    
}

Weapon::~Weapon() {
    
}

// ACCESSORS

std::string Weapon::action() const {
    // return action string of the weapon
    return m_action;
}

int Weapon::dexBonus() const {
    // return dexterity bonus provided by the weapon
    return m_dexBonus;
}

int Weapon::damageBonus() const {
    // return damage bonus provided by the weapon
    return m_damage;
}

// SETTERS

void Weapon::setAction(const std::string& a) {
    // set the action string of the weapon
    m_action = a;
}

void Weapon::setDex(const int& d) {
    // set the dexterity bonus of the weapon
    m_dexBonus = d;
}

void Weapon::setDamage(const int& d) {
    // set the damage bonus of the weapon
    m_damage = d;
}

void Weapon::effect(Actor*) {
    // set the effect the weapon has on the actor
    // only the magic fangs will have an effect, so no parameter name is used until then
    return;
}

// GAME DISPLAY FUNCTIONS

void Weapon::display() const {
    // add the weapon character to the dungeon grid
    game()->dungeon()->set(row(), col(), WEAPON);
}

std::string Weapon::pickUpMsg() const {
    // string printed when a weapon is picked up
    std::string msg = "You pick up " + name() + ".";
    return msg;
}

/// SCROLL DERIVED CLASS

Scroll::Scroll(Game* g) : Object(g) {
    
}

Scroll::~Scroll() {
    
}

// ACCESSORS

std::string Scroll::action() const {
    // return the scroll's action
    return m_action;
}

// SETTERS

void Scroll::setAct(const std::string& a) {
    // set the scroll's action
    m_action = a;
}

void Scroll::display() const {
    // set scroll character on dungeon grid
    game()->dungeon()->set(row(), col(), SCROLL);
}

// GAME PLAY FUNCTIONS

std::string Scroll::pickUpMsg() const
{
    // return message when a scroll is picked up
    std::string msg = "You pick up a scroll called " + name() + ".";
    return msg;
}

/// STAIRWAY DERIVED CLASS

Stairway::Stairway(Game* g) : Object(g) {
    
}

Stairway::~Stairway() {
    
}

// GAME PLAY FUNCTIONS

void Stairway::display() const {
    // place the stairway character onto the dungeon grid
    game()->dungeon()->set(row(), col(), STAIRWAY);
}

std::string Stairway::pickUpMsg() const {
    // no string is returned because a stairway cannot be picked up
    return "";
}

/// GOLDEN IDOL DERIVED CLASS

GoldenIdol::GoldenIdol(Game* g):Object(g) {
    
}

GoldenIdol::~GoldenIdol() {
    
}

// GAME PLAY FUNCTIONS

void GoldenIdol::display() const {
    // place golden idol character onto dungeon grid
    game()->dungeon()->set(row(), col(), GOLDEN_IDOL);
}

std::string GoldenIdol::pickUpMsg() const {
    // string returned when the golden idol is picked up
    return "You pick up the golden idol.";
}
