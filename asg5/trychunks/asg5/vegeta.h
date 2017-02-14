#ifndef VEGETA_H
#define VEGETA_H
#include <vector>
#include "drawable.h"
#include "multisprite.h"
#include <string>
#include "gamedata.h"
#include "ioManager.h"


class ExplodingSprite;
class Vegeta: public Drawable
{
public:
 Vegeta(const std::string&);
 Vegeta(const Vegeta&);
/*Vegeta(const std::string&, 
         const Vector2f& pos, const Vector2f& vel, const std::vector<Frame*>& frm);*/
 virtual void draw()const;
 virtual void update(Uint32 ticks);
 virtual const Frame* getFrame() const {return frames[currentFrame];}
  virtual void explode();
  virtual ~Vegeta();
 

 protected:
  //const Frame * frame;

 const std::vector<Frame*> frames;
  int worldWidth;
  int worldHeight;
  ExplodingSprite* explosion;

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
