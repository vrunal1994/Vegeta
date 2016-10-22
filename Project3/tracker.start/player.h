#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "drawable.h"
#include "sprite.h"
#include <string>
#include "gamedata.h"
#include "ioManager.h"



class Player: public Drawable
{
public:
 Player(const std::string&);
 Player(const Player&);
 //virtual ~Player(){d};
 virtual void draw()const;
 virtual void update(Uint32 ticks);
 virtual const Frame* getFrame() const {return frames[currentFrame];}
 

 protected:
 const std::vector<Frame*> frames;
  int worldWidth;
  int worldHeight;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;

  int movSpeedX;
  int movSpeedY;
  int direction;


 void advanceFrame(Uint32 ticks);
  Player& operator=(const Player&);
  };
#endif
