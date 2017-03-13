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

    // inform the engine of the existence of each entity
    engine.registerEnvironment(&backgroundTexture);

    bool quit = false;
    while(!quit)
    {
        // quit if neccesary.
        // otherwise, tell the game engine what events
        // have occured, and let it take action
        quit = engine.process(io);
        // quit = engine.checkExit();

        engine.updateRenderPipeline();
        // access input from io context
        // character.processInput(io);
        // update render state
        // background.render(io,0,0);
        // draw updated state
        io.draw();
    }

    // close all the textures that were created
    backgroundTexture.free();
    characterTexture.free();
    io.close();

}
