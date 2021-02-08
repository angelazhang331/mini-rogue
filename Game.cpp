#include "Game.h"
#include "Player.h"
#include "Monster.h"
#include "Weapons.h"
#include "Scrolls.h"
#include "Dungeon.h"
#include "utilities.h"

#include <iostream>

using namespace std;


Game::Game(int goblinSmellDistance)
{
    m_dungeon = new Dungeon(this);
    m_player = new Player(this);
    idolFound = false;
    playerDead = false;
    m_goblinSmellDistance = goblinSmellDistance;
    
    // create the monsters and objects in the dungeon
    generateMonsters();
    generateObjects();
}

Game::~Game()
{
    // delete all dynamically allocated things
    delete m_dungeon;
    delete m_player;
    deleteMonsters();
    deleteObjects();
}

void Game::play()
{
    // display message located at the bottom of the dungeon display
    std::string playerMsg = "", monsterMsg = "";
    
    // if the actor is not dead and the idol has not been found, continute taking turns
    while (!idolFound && !playerDead)
    {
        // display the current dungeon
        m_dungeon->display(playerMsg, monsterMsg);
        //take player and monster turns
        playerMsg = takePlayerTurn();
        monsterMsg = takeMonsterTurn();
    }
    // if the idol has been found,
    if(idolFound)
    {
        // display the winning message
        m_dungeon->display(playerMsg, monsterMsg);
        cout << "Congratulations, you won!" << endl;
    }
    // if the player died
    else if(playerDead)
    {
        // display losing message
        m_dungeon->display(playerMsg, monsterMsg);
    }
    // wait for 'q' to exit the game
    cout << "Press q to exit game." << endl;
    while(getCharacter() != QUIT)
    {
    }
    exit(0);
}

// CREATE AND DELETE GAME OBJECT FUNCTIONS

void Game::generateMonsters() {
    // generate the number of monsters based on the dungeon level
    int level = m_dungeon->level();
    m_numMonsters = randInt(2, 5*(level+1)+1);
    
    // fill the monsters vector with monster types based on the level
    // randomly select the monster type for each monster
    for(int i = 0; i < m_numMonsters; i++)
    {
        m_dungeon->update();
        switch(level) {
                // for levels 0 and 1, only Snakewoman and Goblins appear
            case 0:
            case 1:
                switch(randInt(0,1)) {
                    case 0:
                        m_monsters.push_back(new Snakewoman(this));
                        break;
                    case 1:
                        m_monsters.push_back(new Goblin(this, m_goblinSmellDistance));
                        break;
                }
                break;
                // for level 2, Snakewomen, Goblins, and Bogeymen appear
            case 2:
                switch(randInt(0,2)) {
                    case 0:
                        m_monsters.push_back(new Snakewoman(this));
                        break;
                    case 1:
                        m_monsters.push_back(new Goblin(this, m_goblinSmellDistance));
                        break;
                    case 2:
                        m_monsters.push_back(new Bogeyman(this));
                        break;
                }
                break;
                // for levels 3 and 4, all monsters appear
            case 3:
            case 4:
                switch(randInt(0,3)) {
                    case 0:
                        m_monsters.push_back(new Snakewoman(this));
                        break;
                    case 1:
                        m_monsters.push_back(new Goblin(this, m_goblinSmellDistance));
                        break;
                    case 2:
                        m_monsters.push_back(new Bogeyman(this));
                        break;
                    case 3:
                        m_monsters.push_back(new Dragon(this));
                        break;
                }
                break;
        }
    }
}

void Game::deleteMonsters() {
    // delete all the currently alive monsters in the monster vector
    auto it = m_monsters.begin();
    while(!m_monsters.empty()){
        delete *it;
        it = m_monsters.erase(it);
        m_numMonsters--;
    }
}

void Game::generateObjects() {
    // each level contains 2 to 3 random objects
    m_numObjects = randInt(2, 3);
    
    // for each object, randomly select weapon or scroll and then randomly select weapon or scroll type
    // magic weapons and scrolls of teleportation do not appear on its own
    for(int i = 0; i < m_numObjects; i++)
    {
        m_dungeon->update();
        switch(randInt(0, 1))
        {
            case 0:
                switch(randInt(1, 3))
                {
                    case 1:
                        m_objects.push_back(new Mace(this));
                        break;
                    case 2:
                        m_objects.push_back(new ShortSword(this));
                        break;
                    case 3:
                        m_objects.push_back(new LongSword(this));
                        break;
                }
                break;
            case 1:
                switch(randInt(1,4))
                {
                    case 1:
                        m_objects.push_back(new Strength(this));
                        break;
                    case 2:
                        m_objects.push_back(new Health(this));
                        break;
                    case 3:
                        m_objects.push_back(new Armor(this));
                        break;
                    case 4:
                        m_objects.push_back(new Dexterity(this));
                        break;
                }
                break;
        }
    }
    
    // generate stairway at the end of the objects vector if not on the last level
    if(m_dungeon->level() != 4)
    {
        m_objects.push_back(new Stairway(this));
        m_numObjects++;
    }
    // if at the last level, generate a golden idol instead
    else
    {
        m_objects.push_back(new GoldenIdol(this));
        m_numObjects++;
    }
}

void Game::deleteObjects() {
    // delete all objects that have not been picked up yet
    auto it = m_objects.begin();
    while(!m_objects.empty()){
        delete *it;
        it = m_objects.erase(it);
        m_numObjects--;
    }
}

// GAME PLAY FUNCTIONS

std::string Game::takePlayerTurn() {
    
    // 1 in 10 chance of increasing health
    if(trueWithProbability(0.1))
    {
        player()->incHP(1);
    }
    
    // if the player is asleep, decrement its sleep time
    if(player()->sleep() != 0)
    {
        player()->decSleep(1);
    }
    
    // make sure the dungeon is up to date
    dungeon()->update();
    
    // if the player is not alseep, accept a character and respond to it
    if(player()->sleep() == 0)
    {
        switch(getCharacter())
        {
                // on all arrow characters, player will attempt to move in that direction
            case ARROW_UP:
                return player()->move(ARROW_UP);
                break;
            case ARROW_DOWN:
                return player()->move(ARROW_DOWN);
                break;
            case ARROW_LEFT:
                return player()->move(ARROW_LEFT);
                break;
            case ARROW_RIGHT:
                return player()->move(ARROW_RIGHT);
                break;
            case PICK_UP_OBJECT:
                return checkObject();
                break;
            case WIELD_WEAPON:
                return wieldWeapon();
                break;
            case READ_SCROLL:
                return readScroll();
                break;
            case INVENTORY:
                return viewInventory();
                break;
            case DESCEND:
                return descend();
                break;
            case CHEAT:
                return cheat();
                break;
            case QUIT:
                exit(0);
                break;
            default:
                break;
        }
    }
    // if player is asleep, accept a character and do not respond to it
    else
    {
        getCharacter();
        return "";
    }
    return "";
}

std::string Game::takeMonsterTurn() {
    std::string msg = "";
    // for every monster in the game's monster vector, take its turn
    for(int i = 0; i != m_numMonsters; i++)
    {
        dungeon()->update();
        // if that monster is not asleep, take its turn, otherwise skip over it
        if(monsters()[i]->sleep() == 0)
        {
            std::string temp = monsters()[i]->move();
            // each monster that interacts with the player has a action string, so add rather than set.
            if(temp != "")
            {
                msg += temp + "\n";
            }
        }
    }
    return msg;
}

// ACCESSORS

Dungeon* Game::dungeon() const {
    // return reference to the game's dungeon
    return m_dungeon;
}

Player* Game::player() const {
    // return reference to the game's player
    return m_player;
}

std::vector<Monster*> Game::monsters() const
{
    // return reference to the game's monster vector
    return m_monsters;
}

std::vector<Object*> Game::objects() const
{
    // return reference to the game's object vector
    return m_objects;
}

Monster* Game::monsterAt(const int& r, const int& c) const {
    // find the monster located at a specific position
    for(auto i = 0; i != monsters().size(); i++)
    {
        Monster* m = m_monsters[i];
        if(m->row() == r && m->col() == c)
        {
            // return a reference to that monster
            return m;
        }
    }
    // if no monster is there, return nullptr
    return nullptr;
}

Object* Game::objectAt(const int& r, const int& c) const {
    // find the object located at a specific position
    for(auto i = 0; i != objects().size(); i++)
    {
        Object* o = objects()[i];
        if(o->row() == r && o->col() == c)
        {
            // return a reference to that object
            return o;
        }
    }
    // if no object is there, return nullptr
    return nullptr;
}

// PLAYER TURN FUNCTIONS

std::string Game::checkObject() {
    std::string msg = "";
    Object* o = objectAt(player()->row(), player()->col());
    // if there is an object at that position to pick up, attempt to pick it up
    if(o != nullptr)
    {
        // if it is the golden idol, then the idol was found
        GoldenIdol* g = dynamic_cast<GoldenIdol*>(o);
        if(g != nullptr)
        {
            idolFound = true;
        }
        // if it is a stairway, do not pick it up
        Stairway* s = dynamic_cast<Stairway*>(o);
        if(s != nullptr)
        {
            return msg;
        }
        // otherwise player attempts to pick it up
        msg = player()->pickUp(o);
        // if the player inventory is not full, then the object is picked up and removed from
        // the game's object vector.
        if(msg != "Your knapsack is full; you can't pick that up.")
        {
            objectPickedUp(o);
        }
    }
    return msg;
}

std::string Game::wieldWeapon() {
    // display the inventory and have a player pick a weapon to wield
    return m_player->displayInventory(WIELD_WEAPON);
}

std::string Game::readScroll() {
    // display the inventory and have a player pick a scroll to read
    return m_player->displayInventory(READ_SCROLL);
}

std::string Game::viewInventory() {
    // only display the inventory
    return m_player->displayInventory(INVENTORY);
}

std::string Game::descend() {
    // create a new level layout
    // delete all monsters and objects in the current level
    deleteMonsters();
    deleteObjects();
    // regenerate the level
    dungeon()->descend();
    // find new position for player and regenerate monsters and objects.
    player()->setPos();
    generateMonsters();
    generateObjects();
    return "";
}

std::string Game::cheat() {
    // set the player strength to 9 and set the player max hit points to 50
    player()->setStrength(PLAYER_CHEAT_STRENGTH);
    player()->setMaxHp(PLAYER_CHEAT_HP);
    return "";
}

// GAME PLAY HELPER FUNCTIONS

void Game::playerDied() {
    // if player died, then change value to end turn taking loop
    playerDead = true;
}

void Game::monsterDied(Monster* m) {
    // find which monster died
    for(auto i = m_monsters.begin(); i != m_monsters.end(); i++)
    {
        // when found
        if(*i == m)
        {
            // check if they will drop something
            m->drop();
            // delete the dead monster and erase it from the vector
            delete *i;
            m_monsters.erase(i);
            m_numMonsters--;
            break;
        }
    }
}

void Game::objectPickedUp(Object* obj) {
    // find which object was picked up
    for(auto i = m_objects.begin(); i != m_objects.end(); i++)
    {
        // when found
        if(*i == obj)
        {
            // remove it from the objects vector
            m_objects.erase(i);
            m_numObjects--;
            break;
        }
    }
}

void Game::addObject(Object* obj)
{
    // if a monster drops a weapon, add it to the dungeon's obejct vector.
    m_objects.push_back(obj);
    m_numObjects++;
}
