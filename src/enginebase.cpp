#include "enginebase.hpp"

EngineBase::EngineBase()
{

}

EngineBase::~EngineBase()
{

}

void
EngineBase::registerEnvironment(LTexture* background)
{
    if (background != NULL)
        mBackground = background;
    else
        std::cout << "null background pointer\n";
}

void
EngineBase::registerEntity(Entity* entity)
{
    mEntity.push_back(entity);
}

// be sure to return 1 if the quit flag is caught
bool
EngineBase::process(IOContext & io)
{
    int key = io.getInput();

    if (key == SDL_QUIT)
        return 1;

    // for now, just use a simple keymap
    // these keys map to the character
    switch (key) {
        // case SDLK_w:
        //     mEntity[0].move(
        //     break;
        case SDLK_a:
            mEntity[0]->move();
            break;
        case SDLK_s:

            break;
        case SDLK_d:

            break;
        case SDLK_SPACE:

            break;
    }

    return 0;
}

void
EngineBase::updateRenderPipeline(IOContext & io)
{
    mBackground->render(io,0,0);

    mEntity[0]->render(io);

}
