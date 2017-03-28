#include "main.hpp"

/* Initialize the global SDL context, defined in main.hpp
    Return 1 on success, report error otherwise*/
bool
init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        debug("Could not initialize at SDL_INIT_VIDEO");
        success = false;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"))
            debug("Linear texture filtering not enabled");
        // create the global window
        gWindow = SDL_CreateWindow("game00", SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            success = false;
            debug("Could not create SDL_Window");
        }
        else
        {
            // create the global renderer
            gRenderer = SDL_CreateRenderer(gWindow,-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            if (gRenderer == NULL)
            {
                success = false;
                debug("Could not create SDL_Renderer");
            }
            // Set default draw color
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    success = false;
                    debug("Could not init SDL_image!");
                }
            }
        }
    }
    return success;
}


void
teardown()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();

}

/////////////////////////////////////////////////////////////////
// ENGINE
void
Engine::registerPlayer(Player* player)
{
    if (player != NULL)
        mPlayer = player;
    else
        debug("Tried to register NULL player!");
}

void
Engine::registerLevel(Level* level)
{
    if (level != NULL)
        mLevel = level;
    else
        debug("Tried to register NULL level!");
}

void
Engine::registerEntity(Entity* entity)
{
    if (entity != NULL)
        mEntityList.push_back(entity);
    else
        debug("Tried to register NULL entity!");
}

/* Get the most recent keyboard event from SDL.  If it is quit, make
    make sure to return 0 */
bool
Engine::processInput()
{
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
            return false;

        mPlayer->processInput(e);
        return true;
    }
    return true;
}

/* The input is used by player to move and interact.
    After doing so, update the state of all entities */
void
Engine::updateEntityState()
{
    mPlayer->interact(mLevel,mEntityList,mRecentInput);

    // go through the entity list, and see if they need to be deleted
    for (size_t i = 0; i < mEntityList.size(); i++)
        if (mEntityList[i]->isDead())
            mEntityList.erase(mEntityList.begin()+i);


}

void
Engine::updateRenderPipeline()
{
    mLevel->render();
    mPlayer->render();
    for (size_t i = 0; i < mEntityList.size(); i++)
        mEntityList[i]->render();
}

void
Engine::render()
{
    SDL_RenderPresent(gRenderer);
    SDL_RenderClear(gRenderer);
}

void
Engine::quit()
{
    mLevel->free();
    mPlayer->free();

    for (size_t i = 0; i < mEntityList.size(); i++)
        mEntityList[i]->free();

}
/////////////////////////////////////////////////////////////////
// LEVEL

/* for now, code for just a single background image */
void
Level::init(Texture* texture)
{
    if (texture != NULL)
        mTexture = texture;
    else
        debug("Tried to set level texture to NULL");

    // Create an SDL_Rect that is the collision box in the level
    // SDL_Rect* collisionBox = new SDL_Rect {20,20,20,20};
    mCollisionRect.push_back(new SDL_Rect {0,400,800,20});
    // mCollisionRect.push_back(new SDL_Rect {250,250,30,30});




}

/* we always render the entire level texture */
void
Level::render()
{
    if (mTexture != NULL)
        mTexture->render(0,0);
    else
        debug("Tried to render NULL level texture");

    // render all SDL_Rect that are the placeholder collision boxes
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
    for (size_t i = 0; i < mCollisionRect.size(); i++)
    {
        if (mCollisionRect[i] != NULL)
            SDL_RenderFillRect(gRenderer,mCollisionRect[i]);
    }

}

void
Level::free()
{
    for (size_t i = 0; i < mCollisionRect.size(); i++)
    {
        delete mCollisionRect[i];
        mCollisionRect[i] = NULL;
    }

    mTexture->free();
    mTexture = NULL;
}

std::vector<SDL_Rect*>
Level::getCollisionBox()
{
    return mCollisionRect;
}
/////////////////////////////////////////////////////////////////
// ENTITY

void
Entity::render()
{
    mTexture->render(mXPos,mYPos);
}

void
Entity::free()
{
    mTexture->free();
    mTexture = NULL;

    for (size_t i = 0; i < mCollisionRect.size(); i++)
    {
        delete mCollisionRect[i];
        mCollisionRect[i] = NULL;
    }
}

bool
Entity::isCollision(std::vector<SDL_Rect*> A)
{
    // int leftA,leftB;
    // int rightA,rightB;
    // int topA,topB;
    // int bottomA,bottomB;
    //
    // for (size_t i = 0; i < A.size(); i++)
    // {
    //     leftA = A[i]->x;
    //     rightA = A[i]->x + A[i]->w;
    //     topA = A[i]->y;
    //     bottomA = A[i]->y + A[i]->h;
    //
    //     // iterate through B collision boxes
    //     for (size_t j = 0; j < mCollisionRect.size(); j++)
    //     {
    //
    //         leftB = mCollisionRect[j]->x;
    //         rightB = mCollisionRect[j]->x + mCollisionRect[j]->w;
    //         topB = mCollisionRect[j]->y;
    //         bottomB = mCollisionRect[j]->y + mCollisionRect[j]->h;
    //
    //         // if any side does not overlap, there is no collision;
    //         if ((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB) == false)
    //         {
    //             return true;
    //         }
    //     }
    //
    // }
    // else return no collision
    // return false;

    int leftA,leftB;
    int rightA,rightB;
    int topA,topB;
    int bottomA,bottomB;

    for (size_t i = 0; i < mCollisionRect.size(); i++)
    {
        leftA = mCollisionRect[i]->x;
        rightA = mCollisionRect[i]->x + mCollisionRect[i]->w;
        topA = mCollisionRect[i]->y;
        bottomA = mCollisionRect[i]->y + mCollisionRect[i]->h;

        // iterate through B collision boxes
        for (size_t j = 0; j < A.size(); j++)
        {

            leftB = A[j]->x;
            rightB = A[j]->x + A[j]->w;
            topB = A[j]->y;
            bottomB = A[j]->y + A[j]->h;

            // if any side does not overlap, there is no collision;
            if( ( ( bottomA <= topB ) || ( topA >= bottomB ) || ( rightA <= leftB ) || ( leftA >= rightB ) ) == false )
            {
                return true;
            }
        }

    }
    // else return no collision
    return false;
}

std::vector<SDL_Rect*>
Entity::getCollisionBox()
{
    return mCollisionRect;
}

/////////////////////////////////////////////////////////////////
// PLAYER

void
Player::init(Texture* texture, int xpos, int ypos)
{
    if (texture != NULL)
        mTexture = texture;
    else
        debug("Entity tried to initialize on NULL texture");

    mXPos = xpos;
    mYPos = ypos;
    mVelX = 0;
    mVelY = 0;
    mWidth = 75;
    mHeight = 64;

    // set the initial position collision box(es)
    // for now, just have one collision box
    mCollisionRect.push_back(new SDL_Rect {xpos,ypos,mWidth,mHeight});


}

void
Player::render()
{
    // do the clip specific code
    SDL_Rect* clip = NULL;
    mTexture->render(mXPos,mYPos,clip);

}

void
Player::processInput(SDL_Event & e)
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {

            case SDLK_w:
            {
                mIsFlying = 1;
                mVelY -= 25;
                break;
            }
            // case SDLK_s:
            //     mVelY += 1;
            //     break;
            case SDLK_a:
                mVelX -= 1;
                break;
            case SDLK_d:
                mVelX += 1;
                break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            // case SDLK_w:
            // {
            //     mVelY += 1;
            //     break;
            // }
            // case SDLK_s:
            //     mVelY -= 1;
            //     break;
            case SDLK_a:
                mVelX += 1;
                break;
            case SDLK_d:
                mVelX -= 1;
                break;
        }
    }
    // std::cout << e.key.keysym.sym << std::endl;
}
void
Player::interact(Level* level,std::vector<Entity*> & entityList, int action)
{

    bool levelCollision;

    moveX();

    levelCollision = isCollision(level->getCollisionBox());

    if (mXPos < 0 || mXPos > SCREEN_WIDTH)
    {
        unmoveX();
    }

    moveY();

    levelCollision = isCollision(level->getCollisionBox());

    if (mYPos < 0 || mYPos > SCREEN_HEIGHT)
    {
        unmoveY();
    }

    if (levelCollision)
    {
        mIsFlying = 0;
        unmoveY();
    }


    for (size_t i = 0; i < entityList.size(); i++)
    {
        if (isCollision(entityList[i]->getCollisionBox()))
        {
            entityList[i]->die();
            break;
        }
    }

}


void
Player::moveX()
{

    mXPos += mVelX;

    for (size_t i = 0; i < mCollisionRect.size(); i++)
    {
        mCollisionRect[i]->x += mVelX;
    }
}

void
Player::unmoveX()
{
    mXPos -= mVelX;

    for (size_t i = 0; i < mCollisionRect.size(); i++)
    {
        mCollisionRect[i]->x -= mVelX;
    }
}

void
Player::moveY()
{
    if (mIsFlying)
        mVelY += 0.5;

    mYPos += mVelY;

    for (size_t i = 0; i < mCollisionRect.size(); i++)
    {
        mCollisionRect[i]->y += mVelY;
    }
}

void
Player::unmoveY()
{
    mYPos -= mVelY;

    for (size_t i = 0; i < mCollisionRect.size(); i++)
    {
        mCollisionRect[i]->y -= mVelY;
    }
}


void
Player::die()
{
    // the player can't die (yet)
}

bool
Player::isDead()
{
    return mIsDead;
}

/////////////////////////////////////////////////////////////////
// COIN
void
Coin::init(Texture* texture,int xpos,int ypos)
{
    if (texture != NULL)
        mTexture = texture;
    else
        debug("Coin tried to initialize on NULL texture");

    mXPos = xpos;
    mYPos = ypos;
    mWidth = 79;
    mHeight = 68;

    mCollisionRect.push_back(new SDL_Rect {mXPos,mYPos,mWidth,mHeight});
}

void
Coin::render()
{
    mTexture->render(mXPos,mYPos);
}

void
Coin::die()
{
    mIsDead = 1;
}

bool
Coin::isDead()
{
    return mIsDead;
}

/////////////////////////////////////////////////////////////////
// TEXTURE
bool
Texture::loadFromFile(std::string path)
{
    free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        // color key image
        SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,0,0xFF,0xFF));

        newTexture = SDL_CreateTextureFromSurface(gRenderer,loadedSurface);

        if (newTexture == NULL)
        {
            debug("Could not create texture from sdl surface!");
        }
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }

    mTexture = newTexture;
    return mTexture != NULL;
}

void
Texture::free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void
Texture::render(int x, int y, SDL_Rect* clip,double angle,SDL_Point* center, SDL_RendererFlip flip)
{
    // set the rendering space
    SDL_Rect renderQuad = {x,y,mWidth,mHeight};

    // set the dimensions of the image to render
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    // render to the screen
    SDL_RenderCopyEx(gRenderer,mTexture,clip,&renderQuad,angle,center,flip);
}

int main() {

    bool success = init();


    if (success) // start the game loop if SDL loads correctly
    {
        // load resources
        Texture playerTexture;
        Texture levelTexture;
        Texture coinTexture;

        if (!playerTexture.loadFromFile("resources/player.png"))
        {
            debug("could not load player image");
            exit(3);
        }
        if (!levelTexture.loadFromFile("resources/level.png"))
        {
            debug("could not load level image");
            exit(3);
        }
        if (!coinTexture.loadFromFile("resources/coin.png"))
        {
            debug("could not load coin image");
            exit(3);
        }
        Engine engine;
        Level level;
        Player player;
        Coin coin;

        player.init(&playerTexture,0,0);
        level.init(&levelTexture);
        coin.init(&coinTexture,400,40);
        engine.registerPlayer(&player);
        engine.registerLevel(&level);
        engine.registerEntity(&coin);

        // start the game loop
        bool running = true;
        while (running)
        {
            // processInput() returns 0 when SDL_QUIT is signaled, 1 otherwise
            running = engine.processInput();

            engine.updateEntityState();
            engine.updateRenderPipeline();
            engine.render();

        }
        engine.quit();
        teardown();

    }

}
