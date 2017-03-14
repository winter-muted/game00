#ifndef ENGINE_H
#define ENGINE_H

// #include "io.hpp"
// #include "texture.hpp"

#include <vector>
#include <iostream>

#include "entity.hpp"
#include "io.hpp"
#include "texture.hpp"

// class Entity; // placeholder so it will compile
class IOContext;
class LTexture;


class EngineBase
{
public:
    EngineBase();
    ~EngineBase();

    virtual void registerEnvironment(LTexture* background);

    virtual void registerEntity(Entity* entity);

    virtual bool process(IOContext & io);

    virtual void updateRenderPipeline(IOContext & io);



private:
    std::vector<Entity*> mEntity;

    LTexture* mBackground = NULL;
};




#endif
