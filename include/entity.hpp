#ifndef ENTITY_H
#define ENTITY_H


#include <vector>

#include "io.hpp"


class Entity
{
public:
    Entity() {};

    ~Entity() {};

    virtual void move() = 0;

    virtual void render(IOContext & io);

    // TODO fix this return type;
    void getTexture();



private:
    // x and y positions of entity
    int mPosx;
    int mPosy;

    // x and y velocities
    int mVelx;
    int mVely;

    // SDL rectangles used for collision detection
    // std::vector<SDL_Rect> mCollisionBoxes;

    // SDL Texture to render for this entity



};



#endif
