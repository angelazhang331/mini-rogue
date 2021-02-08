#ifndef Actor_h
#define Actor_h

#include <string>

class Weapon;
class Game;

class Actor
{
public:
    Actor(int hp, Weapon* w, int a, int s, int d, int sl, Game* g, std::string at);
    virtual ~Actor();
    
    // Accessors
    int row() const;
    int col() const;
    int hitpoints() const;
    Weapon* weapon() const;
    int armor() const;
    int strength() const;
    int dexterity() const;
    int sleep() const;
    Game* game() const;
    std::string type() const;
    
    // Setters
    void setRow(const int& r);
    void setCol(const int& c);
    void setWep(Weapon*& w);
    void setStrength(const int& s);
    void setMaxHp(const int& max);
    void setSleep(const int& s);
    
    // Increase values
    void incHP(const int& change);
    void incArmor(const int& change);
    void incStrength(const int& change);
    void incDex(const int& change);
    void decSleep(const int& change);
    
    // Methods
    std::string attack(Actor* a) const;
    std::string getHit(const Actor* a);
    virtual void display() const = 0;
    virtual void killActor() = 0;
    void setPos();
    
private:
    int m_row;
    int m_col;
    int m_hitpoints;
    Weapon* m_weapon;
    int m_armor;
    int m_strength;
    int m_dexterity;
    int m_sleep;
    Game* m_game;
    std::string m_actorType;
    int m_maxHP;
};

#endif /* Actor_h */
