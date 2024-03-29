#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "io.hpp"
#include "global.hpp"

class IOContext;

// #include "io.hpp"


class LTexture {
public:
  LTexture();

  ~LTexture();

  void loadFromFile(std::string path, IOContext & io);

  void render(IOContext & io, int x, int y, Rect* sprite= NULL);

  void free();

private:

    void renderTexture(IOContext & io,int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

  SDL_Texture *mTexture;

  int mWidth;
  int mHeight;
};

#endif
