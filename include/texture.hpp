#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "global.hpp"

class LTexture {
public:
  LTexture();

  ~LTexture();

  void loadFromFile(std::string path);

  void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0,
              SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

  void free();

private:
  SDL_Texture *mTexture;

  int mWidth;
  int mHeight;
};

#endif
