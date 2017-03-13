#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// set the size of the display
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Global window handle
// static SDL_Window *gWindow = NULL;

// The SDL rendering handle
// static SDL_Renderer *gRenderer = NULL;

bool init(SDL_Window *gWindow,SDL_Renderer *gRenderer);
bool loadResources();
void close(SDL_Window *gWindow,SDL_Renderer *gRenderer);

#endif
