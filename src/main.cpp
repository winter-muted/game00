const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#include "main.hpp"

int main() {

    IOContext io;
    EngineBase engine;

    io.init(SCREEN_WIDTH,SCREEN_HEIGHT);

    LTexture backgroundTexture;
    LTexture characterTexture;

    backgroundTexture.loadFromFile("resources/background.png",io);
    characterTexture.loadFromFile("resources/character.bmp",io);

    Player character(&characterTexture);
    character.setAnimationClip(2);

    character.getAnimationClips();

    // inform the engine of the existence of each entity
    engine.registerEnvironment(&backgroundTexture);
    engine.registerEntity(&character);

    bool quit = false;
    while(!quit)
    {
        // process io
        quit = engine.process(io);

        // update textures
        engine.updateRenderPipeline(io);

        io.draw();

    }
    std::cout << "exiting sdl loop" << std::endl;
    // std::cin.ignore();

    // close all the textures that were created
    backgroundTexture.free();
    characterTexture.free();
    io.close();

}
