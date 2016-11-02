#ifndef VEGETA_H
#define VEGETA_H
#include <vector>
#include "drawable.h"
#include "sprite.h"
#include <string>
#include "gamedata.h"
#include "ioManager.h"



class Vegeta: public Drawable
{
public:
 Vegeta(const std::string&);
 Vegeta(const Vegeta&);
 
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
  
    bool VegetaLeft;
   bool VegetaRight;
   bool VegetaIdle;


 void advanceFrame(Uint32 ticks);
  Vegeta& operator=(const Vegeta&);
  };
#endif
