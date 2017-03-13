#ifndef IO_H
#define IO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

// #include "enginebase.hpp"

class EngineBase;

class IOContext
{
public:
        bool init(int SCREEN_WIDTH, int SCREEN_HEIGHT);

        int getInput();

        void draw();

        SDL_Renderer* getRenderer();

        void close();

private:
    SDL_Window* mWindow;

    // this pointer can be accessed freely be the texture class!!
    SDL_Renderer* mRenderer;

};




#endif
