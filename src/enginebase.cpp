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

    // for now, just use a simple keymap
    // these keys map to the character

    switch (key) {
        case SDL_QUIT:
            return 1;
            break;
        case SDLK_w:
            std::cout << "w\n";
            break;
        case SDLK_a:
            std::cout << "a\n";
            break;
        case SDLK_s:
            std::cout << "s\n";
            break;
        case SDLK_d:
            std::cout << "d\n";
            break;
        case SDLK_SPACE:
            mEntity[0]->setFlyingState(1);
            std::cout << "space\n";
            break;
    }

    return 0;
}

void
EngineBase::updateRenderPipeline(IOContext & io)
{
    if (!mBackground == NULL)
        mBackground->render(io,0,0,NULL);
    if (mEntity.size() >=1)
        mEntity[0]->render(io);

}
