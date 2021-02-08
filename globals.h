//
//  globals.h
//  CS 32 Project 3
//
//  Created by Angela Zhang on 5/14/20.
//  Copyright © 2020 Angela Zhang. All rights reserved.
//

#ifndef globals_h
#define globals_h

// GAME SETUP CONSTANTS
const int DUNGEON_COLUMNS = 70;
const int DUNGEON_ROWS = 18;

const int MAX_INVENTORY_SIZE = 26;

// PLAYER CONSTANTS
const int PLAYER_HP = 20;
const int PLAYER_ARMOR = 2;
const int PLAYER_STRENGTH = 2;
const int PLAYER_DEXTERITY = 2;
const int PLAYER_SLEEP = 0;
const int PLAYER_CHEAT_HP = 50;
const int PLAYER_CHEAT_STRENGTH = 9;

const int BOGEYMAN_ARMOR = 2;
const int BOGEYMAN_SMELL = 5;

const int SNAKEWOMAN_STRENGTH = 2;
const int SNAKEWOMAN_DEX = 3;
const int SNAKEWOMAN_ARMOR = 3;
const int SNAKEWOMAN_SMELL = 3;

const int DRAGON_STRENGTH = 4;
const int DRAGON_DEX = 4;
const int DRAGON_ARMOR = 4;
const int DRAGON_SMELL = 1;

const int GOBLIN_STRENGTH = 3;
const int GOBLIN_DEX = 1;
const int GOBLIN_ARMOR = 1;

// EXTRA INPUT CONSTANTS
const char PICK_UP_OBJECT = 'g';
const char WIELD_WEAPON = 'w';
const char READ_SCROLL = 'r';
const char INVENTORY = 'i';
const char DESCEND = '>';
const char QUIT = 'q';
const char CHEAT = 'c';

// BOARD SYMBOLS
const char WALL = '#';
const char SPACE = ' ';
const char STAIRWAY = '>';
const char GOLDEN_IDOL = '&';
const char WEAPON = ')';
const char SCROLL = '?';
const char PLAYER = '@';
const char BOGEYMAN = 'B';
const char DRAGON = 'D';
const char GOBLIN = 'G';
const char SNAKEWOMAN = 'S';

// WEAPON VALUES
const int MACE_DEX = 0;
const int MACE_DAMAGE = 2;
const int SS_DEX = 0;
const int SS_DAMAGE = 2;
const int LS_DEX = 2;
const int LS_DAMAGE = 4;
const int MA_DEX = 5;
const int MA_DAMAGE = 5;
const int MF_DEX = 3;
const int MF_DAMAGE = 2;

#endif /* globals_h */
