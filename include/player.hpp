#ifndef PLAYER_H
#define PLAYER_H

// #include <string>
#include "global.hpp"
#include "entity.hpp"
// #include "io.hpp"
#include "texture.hpp"
//
// class IOContext;
//
class LTexture;

class Player : public Entity {
public:
  Player(LTexture *characterTexture);

  ~Player();

  virtual void move();

  virtual void render(IOContext &io);

  void setAnimationClip(int numClips);

  void setFlyingState(int state);

  void getAnimationClips();

private:
  LTexture *mCharacterTexture = NULL;
  std::vector<Rect*> mClips;

  int mInAir = 0;
};

#endif
