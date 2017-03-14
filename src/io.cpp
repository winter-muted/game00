#include "io.hpp"

bool
IOContext::init(int SCREEN_WIDTH, int SCREEN_HEIGHT) {
  // Initialization flag
  bool success = true;
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    std::cout << "SDL could not initialize! Error: " << SDL_GetError() << "\n";
    success = false;
  } else {
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
      std::cout << "Warn: Linear texture filtering not enabled\n";

    // Create window
    mWindow = SDL_CreateWindow("game00", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (mWindow == NULL) {
      std::cout << "WIndow not created! Error: " << SDL_GetError() << "\n";
      success = false;
    } else {
      // Create the window renderer
      mRenderer = SDL_CreateRenderer(
          mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (mRenderer == NULL) {
        std::cout << "Renderer not created! Error: " << SDL_GetError() << "\n";
        success = false;
      }
      // enable various rendering features
      else {
        // draw black
        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        // this code taken from lazyfoo. why are we bitwise anding?
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
          std::cout << "SDL_image could not init! Error: " << IMG_GetError()
                    << "\n";
          success = false;
        }
      }
    }
  }
  return success;
}

void
IOContext::draw()
{   
    SDL_RenderPresent(mRenderer);
    SDL_RenderClear(mRenderer);
}

SDL_Renderer*
IOContext::getRenderer()
{
    return mRenderer;
}

void
IOContext::close()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    mWindow = NULL;
    mRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

int
IOContext::getInput()
{

    SDL_Event e;

    while (SDL_PollEvent(&e) != 0)
    {
        switch (e.type) {
            case SDL_KEYDOWN:
                return e.key.keysym.sym;
            case SDL_QUIT:
                return SDL_QUIT;
        }
    }
    return 0;



}
