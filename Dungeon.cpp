#include "Dungeon.h"
#include "Game.h"
#include "Player.h"
#include "Monster.h"
#include "Object.h"
#include "utilities.h"

#include <iostream>
#include <cstring>

Dungeon::Dungeon(Game* g):m_game(g){
    m_level = 0;
    generateBoard();
}

Dungeon::~Dungeon(){
    
}

// ACCESSORS

char Dungeon::at(int r, int c) const {
    // return the character at that grid location
    return m_grid[r][c];
}

int Dungeon::level() const {
    // return the level of the dungeon
    return m_level;
}

Game* Dungeon::game() const {
    // return the game the dungeon is located in
    return m_game;
}

// SETTERS

void Dungeon::set(int r, int c, char ch) {
    // set the grid location to a certain character
    m_grid[r][c] = ch;
}

// GAME PLAY FUNCTIONS

void Dungeon::descend() {
    // go to the next level and regenerate the board
    m_level++;
    generateBoard();
}

void Dungeon::update() {
    // first make the grid a copy of the empty dungeon with rooms and corridors
    memcpy(m_grid, m_plain, DUNGEON_COLUMNS*DUNGEON_ROWS*sizeof(char));
    
    // add objects
    for(int i = 0; i < m_game->objects().size(); i++)
    {
        m_game->objects()[i]->display();
    }
    
    // add monsters
    for(int i = 0; i < m_game->monsters().size(); i++)
    {
        m_game->monsters()[i]->display();
    }
    
    // add the player
    m_game->player()->display();
}

void Dungeon::display(std::string pm, std::string am) {
    clearScreen();
    // update the dungeon to ensure it is correct
    update();
    // print the dungeon
    for(int i = 0; i < DUNGEON_ROWS; i++)
    {
        for(int j = 0; j < DUNGEON_COLUMNS; j++)
        {
            std::cout << m_grid[i][j];
        }
        std::cout << std::endl;
    }
    // print the stat messages below the dungeon
    std::cout << "Dungeon Level: " << m_level << ", Hit points: " << game()->player()->hitpoints() << ", Armor: " << game()->player()->armor() << ", Strength: " << game()->player()->strength() << ", Dexterity: " << game()->player()->dexterity() << std::endl << std::endl;
    // print the action messages below the dungeon
    std::cout << pm << std::endl;
    std::cout << am << std::endl;
}

// DUNGEON CREATION FUNCTIONS

void Dungeon::generateBoard() {
    // while there are less than four rooms in the generated dungeon, regenerate
    int numRooms = 0;
    while(numRooms < 4)
    {
        // first set the dungeon to all walls
        numRooms = 0;
        for(int i = 0; i < DUNGEON_COLUMNS; i++)
        {
            for(int j = 0; j < DUNGEON_ROWS; j++)
            {
                m_grid[j][i] = WALL;
            }
        }
        
        // recursively add rooms, starting from the upper left corner
        generateRoom(randInt(1, 4), randInt(1, 10), randInt(4, 6), randInt(10, 16), numRooms);
    }
    
    // make the plain 2d array a copy of the original grid with no game objects
    memcpy(m_plain, m_grid, DUNGEON_COLUMNS*DUNGEON_ROWS*sizeof(char));
}

bool Dungeon::generateRoom(int minR, int minC, int numR, int numC, int& rooms)
{
    // stop generating rooms if there are too many
    if(rooms > 4)
        return true;
    
    // room generated goes from minR to maxR and minC to maxC
    int maxR = minR + numR;
    int maxC = minC + numC;
    
    // if all four corners are in bounds
    if(minR > 1 && minC > 1 && maxR < DUNGEON_ROWS-1 && maxC < DUNGEON_COLUMNS-1)
    {
        // check if overlapping
        if(!checkOverlap(minR, maxR, minC, maxC))
        {
            // add to the room count and set the room into hte grid
            rooms++;
            setRoom(minR, maxR, minC, maxC);
            
            // attempt to make more rooms below and to the right of the original room
            int downCounter = 0;
            while(!generateRoom(randInt(maxR + 3, maxR + 4), randInt(minC - 1, minC + 3), randInt(4, 8), randInt(8, 14), rooms) && downCounter <= 5)
            {
                downCounter++;
            }
            
            int rightCounter = 0;
            while(!generateRoom(randInt(minR - 1, minR + 3), randInt(maxC + 3, maxC + 4), randInt(4, 8), randInt(8, 14), rooms) && rightCounter <= 5)
            {
                rightCounter++;
            }
            
            // attempt to make corridors 10 times in each direction or until a corridor is generated
            int corrDownCounter = 0;
            while(!generateCorridor(maxR, randInt(minC+1, maxC-2), 'd') && corrDownCounter <= 10)
            {
                corrDownCounter++;
            }
            
            int corrRightCounter = 0;
            while(!generateCorridor(randInt(minR+1, maxR-2), maxC, 'r') && corrRightCounter <= 10)
            {
                corrRightCounter++;
            }
            
            return true;
        }
        
    }
    return false;
}

bool Dungeon::checkOverlap(int minR, int maxR, int minC, int maxC)
{
    // if in the range of the new room there is already a blank space
    // then there is overlap
    for(int r = minR-1; r <= maxR; r++)
    {
        for(int c = minC-1; c <= maxC; c++)
        {
            if(m_grid[r][c] == ' ')
            {
                return true;
            }
        }
    }
    return false;
}

void Dungeon::setRoom(int minR, int maxR, int minC, int maxC)
{
    // change the characters in the range of the new room to be ' '
    for(int r = minR; r < maxR; r++)
    {
        for(int c = minC; c < maxC; c++)
        {
            m_grid[r][c] = ' ';
        }
    }
}

bool Dungeon::generateCorridor(int r, int c, char direction)
{
    // based on the direction, see if another room can be found within 6 moves.
    // if found, set the corridor and adjust the grid characters.
    int counter = 0;
    int sr = r;
    int sc = c;
    
    switch(direction)
    {
        case 'd':
            do
            {
                counter++;
                r++;
                if(m_grid[r][c] == ' ')
                {
                    setCorridor(sr, sc, direction);
                    return true;
                }
            } while(counter <= 6 && r > 1 && r < DUNGEON_ROWS - 1);
            return false;
            break;
        case 'r':
            do
            {
                counter++;
                c++;
                if(m_grid[r][c] == ' ')
                {
                    setCorridor(sr, sc, direction);
                    return true;
                }
            } while(counter <= 6 && c > 1 && c < DUNGEON_COLUMNS - 1);
            return false;
            break;
        default:
            break;
    }
    return false;
}

void Dungeon::setCorridor(int r, int c, char direction)
{
    // change the grid characters in the path of the corridor to ' ' based on the direction of the corridor
    switch(direction)
    {
        case 'd':
            while(m_grid[r][c] != ' ')
            {
                m_grid[r][c] = ' ';
                r++;
            }
            break;
        case 'r':
            while(m_grid[r][c] != ' ')
            {
                m_grid[r][c] = ' ';
                c++;
            }
            break;
        default:
            break;
    }
}
