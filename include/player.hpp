#ifndef PLAYER_H
#define PLAYER_H

// #include <string>
#include "entity.hpp"
// #include "io.hpp"
#include "texture.hpp"
//
// class IOContext;
//
class LTexture;

class Player : private Entity
{
public:
    Player(LTexture* characterTexture);

    ~Player();

    virtual void move();

    virtual void render(IOContext & io);


private:
    LTexture* mCharacterTexture = NULL;

};


#endif
