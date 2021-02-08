//
//  Player.h
//  CS 32 Project 3
//
//  Created by Angela Zhang on 5/13/20.
//  Copyright © 2020 Angela Zhang. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include "Actor.h"

#include <vector>

class Object;
class Scroll;
class Weapon;

class Player: public Actor
{
public:
    Player(Game* g);
    ~Player();
    
    // game play functions
    std::string move(char direction);
    std::string pickUp(Object* obj);
    std::string read(Scroll* s);
    std::string wield(Weapon* w);
    std::string displayInventory(char type);
    void killActor();
    
    // dungeon display function
    void display() const;
    
    // game play helper functions
    bool checkMove(int r, int c) const;
    bool checkAttack(int r, int c) const;
    
private:
    std::vector<Object*> m_inventory;
    int m_invSize;
    char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
};

#endif /* Player_h */

