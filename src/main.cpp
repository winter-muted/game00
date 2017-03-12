

#include "main.hpp"

int main() {

  // Load the SDL context
  bool success = init();

  if (!loadResources) {
    std::cout << "Could not load media!\n";
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  }
  LTexture background;
  background.loadFromFile("resources/background.png");

  // start the game loop
  bool quit = false;
  SDL_Event e;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      // read events
      if (e.type == SDL_Quit)
        quit = true;

      // process events
      //   Character.handleEvent(e);
      //   Character.move(Level);
      //   Character.positionCamera(camera)
      //
      // update rendering
      SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderClear(gRenderer);

      SDL_RenderPresent(gRenderer);

      // end the game
    }
    close();
  }
}
