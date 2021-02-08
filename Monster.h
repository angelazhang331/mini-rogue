#ifndef Monster_h
#define Monster_h

#include "Actor.h"

class Game;
class Object;

class Monster : public Actor
{
public:
    Monster(int hp, Weapon* w, int a, int s, int d, int sl, Game* g, std::string at);
    virtual ~Monster();
    
    // game play functions
    virtual std::string move() = 0;
    virtual void drop() = 0;
    
    // game play helper functions
    bool checkMove(int r, int c) const;
    bool checkAttack(int r, int c) const;
    void killActor();
    
};

class Bogeyman : public Monster
{
public:
    Bogeyman(Game* g);
    ~Bogeyman();

    std::string move();
    void drop();
    void display() const;
};

class Snakewoman : public Monster
{
public:
    Snakewoman(Game* g);
    ~Snakewoman();
    
    std::string move();
    void drop();
    void display() const;
};

class Dragon : public Monster
{
public:
    Dragon(Game* g);
    ~Dragon();
    
    std::string move();
    void drop();
    void display() const;
};

class Goblin : public Monster
{
public:
    Goblin(Game* g, int sd);
    ~Goblin();
    
    std::string move();
    int goblinMoveHelper(int gr, int gc, int pr, int pc, int steps);
    void drop();
    void display() const;
    
private:
    int m_smellDis;
};

#endif /* Monster_h */
