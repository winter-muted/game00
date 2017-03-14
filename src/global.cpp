// #include "global.hpp"
//
// bool init(SDL_Window *gWindow,SDL_Renderer *gRenderer) {
//   // Initialization flag
//   bool success = true;
//   // Initialize SDL
//   if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
//     std::cout << "SDL could not initialize! Error: " << SDL_GetError() << "\n";
//     success = false;
//   } else {
//     if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
//       std::cout << "Warn: Linear texture filtering not enabled\n";
//
//     // Create window
//     gWindow = SDL_CreateWindow("game00", SDL_WINDOWPOS_UNDEFINED,
//                                SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
//                                SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//
//     if (gWindow == NULL) {
//       std::cout << "WIndow not created! Error: " << SDL_GetError() << "\n";
//       success = false;
//     } else {
//       // Create the window renderer
//       gRenderer = SDL_CreateRenderer(
//           gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//       if (gRenderer == NULL) {
//         std::cout << "Renderer not created! Error: " << SDL_GetError() << "\n";
//         success = false;
//       }
//       // enable various rendering features
//       else {
//         // draw white
//         SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//         // this code taken from lazyfoo. why are we bitwise anding?
//         int imgFlags = IMG_INIT_PNG;
//         if (!(IMG_Init(imgFlags) & imgFlags)) {
//           std::cout << "SDL_image could not init! Error: " << IMG_GetError()
//                     << "\n";
//           success = false;
//         }
//       }
//     }
//   }
//   return success;
// }
//
// void close(SDL_Window *gWindow,SDL_Renderer *gRenderer) {
//   // Destroy any created textures
//
//   // Destroy SDL renderer and window
//   SDL_DestroyRenderer(gRenderer);
//   SDL_DestroyWindow(gWindow);
//   gWindow = NULL;
//   gRenderer = NULL;
//
//   // Destroy SDL context
//   IMG_Quit();
//   SDL_Quit();
// }
//
// bool loadResources() {
//   return true;
//
//   //
// }
