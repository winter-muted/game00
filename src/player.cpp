#include "player.hpp"

Player::Player(LTexture* characterTexture)
{
    mCharacterTexture = characterTexture;
}

Player::~Player()
{
    mCharacterTexture = NULL;
}

void
Player::move()
{

}

void
Player::render(IOContext & io)
{
    mCharacterTexture->render(io,mPosx,mPosy);
}
