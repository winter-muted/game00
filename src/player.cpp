#include "player.hpp"

Player::Player(LTexture* characterTexture)
{
    mCharacterTexture = characterTexture;
}

Player::~Player()
{
    mCharacterTexture = NULL;

    for (int i = 0; i < mClips.size(); i++)
        delete mClips[i];
}

void
Player::move()
{

}

void
Player::render(IOContext & io)
{
    if (mInAir == 1)
    {
        mCharacterTexture->render(io,mPosx,mPosy,mClips[0]);
    }
    else
    {
        mCharacterTexture->render(io,mPosx,mPosy,mClips[1]);
    }


}

void
Player::setAnimationClip(int numClips)
{
    mClips.push_back(new Rect(0,0,36,64));
    mClips.push_back(new Rect(37,0,36,64));
}

void
Player::setFlyingState(int state)
{
    mInAir = state;
}

void
Player::getAnimationClips()
{
    for (int i = 0; i < mClips.size(); i++)
    {
        std::cout << mClips[i]->x << "\n";
    }
}
