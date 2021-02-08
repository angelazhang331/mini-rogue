#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <vector>
#include <string>

class Dungeon;
class Player;
class Monster;
class Object;
class Actor;

class Game
{
public:
    Game(int goblinSmellDistance);
    ~Game();
    void play();
    
    // create and delete game object functions
    void generateMonsters();
    void deleteMonsters();
    void generateObjects();
    void deleteObjects();
    
    // game play functions
    std::string takePlayerTurn();
    std::string takeMonsterTurn();
    
    // accessors
    Dungeon* dungeon() const;
    Player* player() const;
    std::vector<Monster*> monsters() const;
    std::vector<Object*> objects() const;
    Monster* monsterAt(const int& r, const int& c) const;
    Object* objectAt(const int& r, const int& c) const;
    
    // player turn functions
    std::string checkObject();
    std::string wieldWeapon();
    std::string readScroll();
    std::string viewInventory();
    std::string descend();
    std::string cheat();

    // game play helper functions
    void playerDied();
    void monsterDied(Monster* m);
    void objectPickedUp(Object* obj);
    void addObject(Object* obj);
    
private:
    Dungeon* m_dungeon;
    Player* m_player;
    std::vector<Monster*> m_monsters;
    int m_numMonsters;
    std::vector<Object*> m_objects;
    int m_numObjects;
    bool idolFound;
    bool playerDead;
    int m_goblinSmellDistance;
};

#endif // GAME_INCLUDED
