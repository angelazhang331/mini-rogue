#include "Monster.h"
#include "Weapons.h"
#include "Scrolls.h"
#include "Dungeon.h"
#include "Game.h"
#include "Player.h"
#include "globals.h"
#include "utilities.h"

#include <cstdlib>
#include <vector>
#include <algorithm>

/// MONSTER

Monster::Monster(int hp, Weapon* w, int a, int s, int d, int sl, Game* g, std::string at): Actor(hp, w, a, s, d, sl, g, at){
    
}

Monster::~Monster() {
    
}

// GAME PLAY HELPER FUNCTION

bool Monster::checkMove(int r, int c) const {
    // check that the monster can move onto that spot
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

bool Monster::checkAttack(int r, int c) const {
    // check that the monster can attack something on that spot
    switch(game()->dungeon()->at(r, c))
    {
        case PLAYER:
            return true;
            break;
        default:
            break;
    }
    return false;
}

void Monster::killActor() {
    // tell the game that the monster died
    game()->monsterDied(this);
}

/// BOGEYMAN

Bogeyman::Bogeyman(Game* g):Monster(randInt(5, 10), new ShortSword(g), BOGEYMAN_ARMOR, randInt(2, 3), randInt(2, 3), 0, g, "the Bogeyman") {
    
}

Bogeyman::~Bogeyman() {
    delete weapon();
}

std::string Bogeyman::move() {
    
    // if the player is asleep, don't move
    if(sleep() > 0)
        return "";
    
    // if within smell range, move one step towards the player
    // if right next to the player, then attack
    int distance = abs(row() - game()->player()->row()) + abs(col() - game()->player()->col());
    if(distance <= BOGEYMAN_SMELL)
    {
        if(row() < game()->player()->row())
        {
            if(checkMove(row() + 1, col()))
                setRow(row() + 1);
            else if(checkAttack(row() + 1, col()))
                return attack(game()->player());
        }
        else if(row() > game()->player()->row())
        {
            if(checkMove(row() - 1, col()))
                setRow(row() - 1);
            else if(checkAttack(row() - 1, col()))
                return attack(game()->player());
        }
        else if(col() < game()->player()->col())
        {
            if(checkMove(row(), col() + 1))
                setCol(col() + 1);
            else if(checkAttack(row(), col() + 1))
                return attack(game()->player());
        }
        else if(col() > game()->player()->col())
        {
            if(checkMove(row(), col() - 1))
                setCol(col() - 1);
            else if(checkAttack(row(), col() - 1))
                return attack(game()->player());
        }
    }
    return "";
}

void Bogeyman::drop() {
    // there is a 1 in 10 chance that this monster will drop a weapon
    if(trueWithProbability(1./10.))
    {
        // if there is not object at that spot, add new object to the game
        if(game()->objectAt(row(), col()) == nullptr)
        {
            Object* temp = new MagicAxe(game());
            temp->setRow(row());
            temp->setCol(col());
            game()->addObject(temp);
        }
    }
}

void Bogeyman::display() const {
    // place monster character onto dungeon grid
    game()->dungeon()->set(row(), col(), BOGEYMAN);
}

// SNAKEWOMAN

Snakewoman::Snakewoman(Game* g):Monster(randInt(20, 25), new MagicFangs(g), SNAKEWOMAN_ARMOR, SNAKEWOMAN_STRENGTH, SNAKEWOMAN_DEX, 0, g, "the Snakewoman"){
    
}

Snakewoman::~Snakewoman() {
    delete weapon();
}

std::string Snakewoman::move() {
    // if the monster is asleep, don't move at all
    if(sleep() > 0)
        return "";
    // if within smell range, move one step towards the player
    // if right next to the player, then attack
    int distance = abs(row() - game()->player()->row()) + abs(col() - game()->player()->col());
    if(distance <= SNAKEWOMAN_SMELL)
    {
        if(row() < game()->player()->row())
        {
            if(checkMove(row() + 1, col()))
                setRow(row() + 1);
            else if(checkAttack(row() + 1, col()))
                return attack(game()->player());
        }
        else if(row() > game()->player()->row())
        {
            if(checkMove(row() - 1, col()))
                setRow(row() - 1);
            else if(checkAttack(row() - 1, col()))
                return attack(game()->player());
        }
        else if(col() < game()->player()->col())
        {
            if(checkMove(row(), col() + 1))
                setCol(col() + 1);
            else if(checkAttack(row(), col() + 1))
                return attack(game()->player());
        }
        else if(col() > game()->player()->col())
        {
            if(checkMove(row(), col() - 1))
                setCol(col() - 1);
            else if(checkAttack(row(), col() - 1))
                return attack(game()->player());
        }
    }
    return "";
}

void Snakewoman::drop() {
    // there is a 1 in 3 chance that this monster drops a weapon
    if(trueWithProbability(1./3.))
    {
        // if there is no object already there,
        if(game()->objectAt(row(), col()) == nullptr)
        {
            // add new object to the game
            Object* temp = new MagicFangs(game());
            temp->setRow(row());
            temp->setCol(col());
            game()->addObject(temp);
        }
    }
}

void Snakewoman::display() const {
    // place monster character onto dungeon grid
    game()->dungeon()->set(row(), col(), SNAKEWOMAN);
}

// DRAGON

Dragon::Dragon(Game* g):Monster(randInt(20, 25), new LongSword(g), DRAGON_ARMOR, DRAGON_STRENGTH, DRAGON_DEX, 0, g, "the Dragon"){
    setMaxHp(hitpoints());
}

Dragon::~Dragon() {
    delete weapon();
}

std::string Dragon::move() {
    // if the monster is asleep, don't move at all
    if(sleep() > 0)
        return "";
    // there is a one in ten chance that the dragon regenerates one hit point this turn
    if(trueWithProbability(1./10.))
    {
        incHP(1);
    }
    // if the player is within the dragon's smell distance, attack ( dragon does not move )
    int distance = abs(row() - game()->player()->row()) + abs(col() - game()->player()->col());
    if(distance <= DRAGON_SMELL)
    {
        if(row() < game()->player()->row())
        {
            if(checkAttack(row() + 1, col()))
                return attack(game()->player());
        }
        else if(row() > game()->player()->row())
        {
            if(checkAttack(row() - 1, col()))
                return attack(game()->player());
        }
        else if(col() < game()->player()->col())
        {
            if(checkAttack(row(), col() + 1))
                return attack(game()->player());
        }
        else if(col() > game()->player()->col())
        {
            if(checkAttack(row(), col() - 1))
                return attack(game()->player());
        }
    }
    return "";
}

void Dragon::drop() {
    // the dragon will always drop a scroll if there is no object already placed there
    if(game()->objectAt(row(), col()) == nullptr)
    {
        // randomly determine the type of scroll dropped
        Object* temp = nullptr;
        switch(randInt(1,5))
        {
            case 1:
                temp = new Teleportation(game());
                break;
            case 2:
                temp = new Strength(game());
                break;
            case 3:
                temp = new Health(game());
                break;
            case 4:
                temp = new Armor(game());
                break;
            case 5:
                temp = new Dexterity(game());
                break;
            default:
                break;
        }
        temp->setRow(row());
        temp->setCol(col());
        game()->addObject(temp);
    }
}

void Dragon::display() const {
    // add monster character to the dungeon grid
    game()->dungeon()->set(row(), col(), DRAGON);
}

// GOBLIN

Goblin::Goblin(Game* g, int sd):Monster(randInt(15, 20), new ShortSword(g), GOBLIN_ARMOR, GOBLIN_STRENGTH, GOBLIN_DEX, 0, g, "the Goblin"){
    m_smellDis = sd;
}

Goblin::~Goblin() {
    delete weapon();
}

std::string Goblin::move() {
    // if the monster is asleep, don't move at all
    if(sleep() > 0)
        return "";
    // if the player is right next to the monster, attack
    int distance = abs(row() - game()->player()->row()) + abs(col() - game()->player()->col());
    if(distance == 1)
    {
        if(row() < game()->player()->row())
        {
            if(checkAttack(row() + 1, col()))
                return attack(game()->player());
        }
        else if(row() > game()->player()->row())
        {
            if(checkAttack(row() - 1, col()))
                return attack(game()->player());
        }
        else if(col() < game()->player()->col())
        {
            if(checkAttack(row(), col() + 1))
                return attack(game()->player());
        }
        else if(col() > game()->player()->col())
        {
            if(checkAttack(row(), col() - 1))
                return attack(game()->player());
        }
    }
    // if the player is within smell distance, then call recursive move function
    else if (distance <= m_smellDis)
    {
        // call the recursive move function in each direction
        int up = goblinMoveHelper(row()-1, col(), game()->player()->row(), game()->player()->col(), m_smellDis-1);
        int left = goblinMoveHelper(row(), col()-1, game()->player()->row(), game()->player()->col(), m_smellDis-1);
        int down = goblinMoveHelper(row()+1, col(), game()->player()->row(), game()->player()->col(), m_smellDis-1);
        int right = goblinMoveHelper(row(), col()+1, game()->player()->row(), game()->player()->col(), m_smellDis-1);
        
        // determine which direction reaches the player in the least amount of steps
        
        // add all directions that don't lead into a dead end into a vector and find the shortest distance
        std::vector<int> moveDirection;
        
        if(up != -1)
        {
            moveDirection.push_back(up);
        }
        if(left != -1)
        {
            moveDirection.push_back(left);
        }
        if(down != -1)
        {
            moveDirection.push_back(down);
        }
        if(right != -1)
        {
            moveDirection.push_back(right);
        }
        
        if(moveDirection.size() != 0)
        {
            
            sort(moveDirection.begin(), moveDirection.end());
            
            int min = moveDirection[0];
            
            // move in the direction of the shortest distance
            if(min == up)
            {
                if(checkMove(row()-1, col()))
                {
                    setRow(row()-1);
                }
            }
            else if(min == left)
            {
                if(checkMove(row(), col()-1))
                {
                    setCol(col()-1);
                }
            }
            else if(min == down)
            {
                if(checkMove(row()+1, col()))
                {
                    setRow(row()+1);
                }
            }
            else if(min == right)
            {
                if(checkMove(row(), col()+1))
                {
                    setCol(col()+1);
                }
            }
        }
    }
    return "";
}

int Goblin::goblinMoveHelper(int gr, int gc, int pr, int pc, int steps)
{
    // if the monster is attempting to move out of bounds, return -1
    if(gr < 0 || gr >= DUNGEON_ROWS || gc < 0 || gc >= DUNGEON_COLUMNS)
        return -1;
    
    // if there is something in that direction, return -1
    char move = game()->dungeon()->at(gr, gc);
    switch(move)
    {
        case WALL:
        case BOGEYMAN:
        case SNAKEWOMAN:
        case DRAGON:
        case GOBLIN:
            return -1;
            break;
    }
    
    // if the goblin is already next to the player, return 1
    int distance = abs(gr - pr) + abs(gc - pc);
    if(distance == 1)
    {
        return 1;
    }
    // else if the goblin is too far away from the player, return -1
    else if (distance > steps)
    {
        return -1;
    }
    
    //check each direction and record how many steps to reach the player from that direction
    int up = goblinMoveHelper(gr-1, gc, pr, pc, steps-1);
    int left = goblinMoveHelper(gr, gc-1, pr, pc, steps-1);
    int right = goblinMoveHelper(gr, gc+1, pr, pc, steps-1);
    int down = goblinMoveHelper(gr+1, gc, pr, pc, steps-1);
    
    // put all values that aren't -1 into a vector to find the shortest distance
    std::vector<int> directions;
    if(up != -1)
    {
        directions.push_back(up+1);
    }
    if(left != -1)
    {
        directions.push_back(left+1);
    }
    if(right != -1)
    {
        directions.push_back(right+1);
    }
    if(down != -1)
    {
        directions.push_back(down+1);
    }
    
    if(directions.size() == 0)
    {
        return -1;
    }
    
    // find minimum and return that value
    sort(directions.begin(), directions.end());
    return directions[0];
}


void Goblin::drop() {
    // there is a one in three chance that the goblin drops a weapon
    if(trueWithProbability(1./3.))
    {
        // if there is not already an object there
        if(game()->objectAt(row(), col()) == nullptr)
        {
            // randomly determine what the object type is and then add it to the game.
            Object* temp = nullptr;
            switch(randInt(1,2))
            {
                case 1:
                    temp = new MagicFangs(game());
                    break;
                case 2:
                    temp = new MagicAxe(game());
                    break;
                default:
                    break;
            }
            temp->setRow(row());
            temp->setCol(col());
            game()->addObject(temp);
        }
    }
}

void Goblin::display() const {
    // add monster character onto the dungeon grid
    game()->dungeon()->set(row(), col(), GOBLIN);
}
