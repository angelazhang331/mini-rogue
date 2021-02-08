#ifndef Object_h
#define Object_h

#include <string>

class Game;
class Actor;

// OBJECT BASE CLASS

class Object {
public:
    Object(Game* g);
    virtual ~Object();
    
    // accessors
    int row() const;
    int col() const;
    std::string name() const;
    Game* game() const;
    
    // setters
    void setRow(const int& r);
    void setCol(const int& c);
    void setName(const std::string& n);
    
    // generate helper function
    void setPos();
    
    // game play functions
    virtual void display() const = 0;
    virtual std::string pickUpMsg() const = 0;
    
private:
    Game* m_game;
    int m_row;
    int m_col;
    std::string m_name;
};

// WEAPON DERIVED CLASS

class Weapon : public Object {
public:
    Weapon(Game* g);
    virtual ~Weapon();
    
    // accessors
    std::string action() const;
    int dexBonus() const;
    int damageBonus() const;
    
    // setters
    void setAction(const std::string& a);
    void setDex(const int& d);
    void setDamage(const int& d);
    virtual void effect(Actor*);
    
    // game display functions
    void display() const;
    std::string pickUpMsg() const;
    
private:
    std::string m_action;
    int m_dexBonus;
    int m_damage;
};

// SCROLL DERIVED CLASS

class Scroll: public Object {
    
public:
    Scroll(Game* g);
    virtual ~Scroll();
    
    // accessors
    std::string action() const;
    
    // setters
    void setAct(const std::string& a);
    
    // game play functions
    virtual void effect(Actor* a) = 0;
    void display() const;
    std::string pickUpMsg() const;
    
private:
    std::string m_action;
};

// STAIRWAY DERIVED CLASS

class Stairway: public Object {
public:
    Stairway(Game* g);
    ~Stairway();
    
    // game play functions
    void display() const;
    std::string pickUpMsg() const;
};

// GOLDEN IDOL DERIVED CLASS

class GoldenIdol: public Object {
public:
    GoldenIdol(Game* g);
    ~GoldenIdol();
    
    // game play functions
    void display() const;
    std::string pickUpMsg() const;
};

#endif /* Object_h */


