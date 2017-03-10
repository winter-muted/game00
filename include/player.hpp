#ifndef PLAYER_H
#define PLAYER_H

#include "global.hpp"
#include "entity.hpp"

class Player;

class Player : public Entity
{
public:
    Player();

    ~Player();

    virtual void move();

    virtual void render();

};


#endif
