#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <string>
#include <vector>
#include <iostream>

#include <stdio.h>

// a useful debug macro
#ifdef DEBUG
#define debug(x) std::cout << x << std::endl;
#else
#define debug(x)
#endif

// Forward Declare classes for THIS game
class Engine;
class Level;
class Entity;
class Player;
class Texture;

// define global variables here!
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;

// forward declare global functions
bool init();
void teardown();


// Tape out classes

/* A class to handle the game loop and logic */
// This class has side effects on the global SDL context defined above
class Engine
{
public:

    void registerPlayer(Player* player);
    void registerLevel(Level* level);
    void registerEntity(Entity* entity);

    bool processInput(); // returns 0 when it is time to exit
    void updateEntityState();
    void updateRenderPipeline();
    void render();
    void quit();

private:

    // The pointer to the (unique) player class
    Player* mPlayer = NULL;

    // The pointer to the (unique) level
    Level* mLevel = NULL;

    // the entity list
    std::vector<Entity*> mEntityList;

    // The most recent input received from SDL
    // populated by processInput()
    int mRecentInput = 0;



};

/* A class to hold the level details */
class Level
{
public:

    void init(Texture* texture);
    void render();
    void free();

    std::vector<SDL_Rect*> getCollisionBox();



private:
    Texture* mTexture = NULL;

    std::vector<SDL_Rect*> mCollisionRect;

};

/* A class to represent generic objects */
class Entity
{
public:
    virtual void init(Texture* texture,int xpos, int ypos) = 0;

    void render();
    void free();

    virtual void die() = 0;
    virtual bool isDead() = 0;

    bool isCollision(std::vector<SDL_Rect*>& A);

    std::vector<SDL_Rect*> getCollisionBox();

protected:

    Texture* mTexture;
    std::vector<SDL_Rect*> mCollisionRect;
    bool mIsDead = 0;

};

/* A class to represent the player character */
class Player : public Entity
{
public:

    void init(Texture* texture,int xpos, int ypos);
    void interact(Level* level,std::vector<Entity*>& entityList, int action);

    void die();
    bool isDead();

private:
    int mWidth = 10;
    int mHeight = 10;

};

/* A class to represent the game coins */
class Coin : public Entity
{
public:

    void init(Texture* texture,int xpos, int ypos);

    void die();
    bool isDead();

private:

};

/* Hold the texture for game entities */
class Texture
{
public:

    bool loadFromFile(std::string path);
    void free();
    void render();

private:

};

#endif
