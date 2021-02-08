#ifndef Dungeon_h
#define Dungeon_h

#include <string>

#include "globals.h"

class Game;

class Dungeon {
public:
    Dungeon(Game* g);
    ~Dungeon();
    
    // accessor
    char at(int r, int c) const;
    int level() const;
    Game* game() const;
    
    // setters
    void set(int r, int c, char ch);
    
    // game play functions
    void descend();
    void update();
    void display(std::string pm, std::string am);
    
    // dungeon creation functions
    void generateBoard();
    bool generateRoom(int r, int c, int numR, int numC, int& numRooms);
    bool checkOverlap(int minR, int maxR, int minC, int maxC);
    void setRoom(int minR, int maxR, int minC, int maxC);
    bool generateCorridor(int r, int c, char direction);
    void setCorridor(int r, int c, char direction);
    
private:
    char m_grid[DUNGEON_ROWS][DUNGEON_COLUMNS];
    char m_plain[DUNGEON_ROWS][DUNGEON_COLUMNS];
    int m_level;
    Game* m_game;
    
};

#endif /* Dungeon_h */
