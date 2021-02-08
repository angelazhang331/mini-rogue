#include "Player.h"
#include "Weapons.h"
#include "Scrolls.h"
#include "Monster.h"
#include "Game.h"
#include "Dungeon.h"
#include "globals.h"
#include "utilities.h"

#include <iostream>

Player::Player(Game* g):Actor(PLAYER_HP, new ShortSword(g), PLAYER_ARMOR, PLAYER_STRENGTH, PLAYER_DEXTERITY, PLAYER_SLEEP, g, "Player")
{
    m_invSize = 1;
    m_inventory.push_back(weapon());
}

Player::~Player()
{
    while(m_inventory.size() != 0)
    {
        auto i = m_inventory.begin();
        delete *i;
        i = m_inventory.erase(i);
    }
}

// GAME PLAY FUNCTIONS

std::string Player::move(char direction)
{
    // attempt to move in a direction
    // if it is clear, move
    // if there is a monster in the way, attack
    switch(direction)
    {
        case ARROW_UP:
            if(checkMove(row()-1, col()))
                setRow(row() - 1);
            else if(checkAttack(row()-1, col()))
                return attack(game()->monsterAt(row()-1, col()));
            break;
        case ARROW_DOWN:
            if(checkMove(row()+1, col()))
                setRow(row() + 1);
            else if(checkAttack(row()+1, col()))
                return attack(game()->monsterAt(row()+1, col()));
            break;
        case ARROW_LEFT:
            if(checkMove(row(), col()-1))
                setCol(col() - 1);
            else if(checkAttack(row(), col()-1))
                return attack(game()->monsterAt(row(), col()-1));
            break;
        case ARROW_RIGHT:
            if(checkMove(row(), col()+1))
                setCol(col() + 1);
            else if(checkAttack(row(), col()+1))
                return attack(game()->monsterAt(row(), col()+1));
            break;
        default:
            break;
    }
    return "";
}

std::string Player::pickUp(Object* obj)
{
    std::string msg;
    // if the inventory is not full,
    if(m_invSize < MAX_INVENTORY_SIZE)
    {
        // pick up the object (scroll or weapon) and add it to the inventory
        msg = obj->pickUpMsg();
        m_inventory.push_back(obj);
        m_invSize++;
    }
    else
    {
        msg = "Your knapsack is full; you can't pick that up.";
    }
    return msg;
}

std::string Player::read(Scroll* s)
{
    std::string msg = "You read a scroll called " + s->name() + ". ";
    // apply the scroll's effect to the player
    msg += s->action();
    s->effect(this);
    // find the instance of the scroll in the inventory and remove it
    for(auto i = m_inventory.begin(); i != m_inventory.end(); i++)
    {
        if(*i == s)
        {
            delete s;
            m_inventory.erase(i);
            m_invSize--;
            break;
        }
    }
    return msg;
}

std::string Player::wield(Weapon* w)
{
    // swap current weapon with the new one selected from the inventory
    std::string msg = "You are wielding " + w->name() + ".";
    setWep(w);
    return msg;
}

std::string Player::displayInventory(char type)
{
    std::string msg = "";
    clearScreen();
    std::cout << "Inventory:" << std::endl;
    for(int i = 0; i < m_invSize; i++)
    {
        std::cout << letters[i] << ". " << m_inventory[i]->name() << std::endl;
    }
    // if inventory is displayed for reading scroll, only accept characters that point to a scroll
    // if inventory is displayed for wielding weapon, only accept characters that point to a weapon
    if(type == READ_SCROLL || type == WIELD_WEAPON)
    {
        // find what that index points to
        char ch = getCharacter();
        int index = 0;
        for(int i = 0; i < MAX_INVENTORY_SIZE; i++)
        {
            if(letters[i] == ch)
            {
                index = i;
                break;
            }
        }
        // ask for a character and check that character is smaller than the max items
        if(index < m_invSize)
        {
            switch(type)
            {
                    // if type matches, perform action, otherwise exit inventory
                case READ_SCROLL: {
                    Scroll* s = dynamic_cast<Scroll*>(m_inventory[index]);
                    if(s != nullptr)
                    {
                        msg = read(s);
                    }
                    else
                    {
                        msg = "You can't read a " + m_inventory[index]->name();
                    }
                    break;
                }
                case WIELD_WEAPON: {
                    Weapon* w = dynamic_cast<Weapon*>(m_inventory[index]);
                    if(w != nullptr)
                    {
                        msg = wield(w);
                    }
                    else
                    {
                        msg = "You can't wield " + m_inventory[index]->name();
                    }
                    break;
                }
                default:
                    break;
            }
        }
        clearScreen();
    }
    else if(type == INVENTORY)
    {
        switch(getCharacter())
        {
            default:
                clearScreen();
                break;
        }
    }
    return msg;
}

// DUNGEON DISPLAY FUNCTION

void Player::display() const
{
    // put the player icon onto the game dungeon
    game()->dungeon()->set(row(), col(), PLAYER);
}

void Player::killActor() {
    // tell the game that the player died
    game()->playerDied();
}

// GAME PLAY HELPER FUNCTIONS

bool Player::checkMove(int r, int c) const {
    // return whether the player can move to that spot
    switch(game()->dungeon()->at(r,c))
    {
        case SPACE:
        case STAIRWAY:
        case WEAPON:
        case SCROLL:
        case GOLDEN_IDOL:
            return true;
            break;
        default:
            break;
    }
    return false;
}

bool Player::checkAttack(int r, int c) const {
    // return whetehr the player can attack something at that spot
    switch(game()->dungeon()->at(r,c))
    {
        case BOGEYMAN:
        case DRAGON:
        case SNAKEWOMAN:
        case GOBLIN:
            return true;
            break;
        default:
            break;
    }
    return false;
}
