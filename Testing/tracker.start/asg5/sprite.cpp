#include <cmath>
#include "sprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "explodingSprite.h"

Sprite::Sprite(const std::string& name) :
   Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x")+Gamedata::getInstance().getRandInRange(0,500), 
 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")+Gamedata::getInstance().getRandInRange(0,500) 
), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX")+Gamedata::getInstance().getRandInRange(-195,300), 
 
                    Gamedata::getInstance().getXmlInt(name+"/speedY")+Gamedata::getInstance().getRandInRange(0,300)
) 
           ),
    explosion(NULL),
  frame( FrameFactory::getInstance().getFrame(name) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  Xaxis(),
  maxDistance(Gamedata::getInstance().getXmlInt(name+ "/maxDistance")),
  tooFar(false), hasExploded(false)

{ }

Sprite::Sprite(const string& n, const Vector2f& pos, const Vector2f& vel):
  Drawable(n, pos, vel), 
  explosion(NULL),
  frame( FrameFactory::getInstance().getFrame(n) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  Xaxis(pos[0]),
  maxDistance(Gamedata::getInstance().getXmlInt(n+ "/maxDistance")),
  tooFar(false), hasExploded(false)
{ }

Sprite::Sprite(const string& n, const Vector2f& pos, const Vector2f& vel,
               const Frame* frm):
  Drawable(n, pos, vel),
  explosion(NULL), 
  frame( frm ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  Xaxis(pos[0]),
  maxDistance(Gamedata::getInstance().getXmlInt(n+ "/maxDistance")),
  tooFar(false), hasExploded(false)

{ }

Sprite::Sprite(const Sprite& s) :
  Drawable(s), 
   explosion(s.explosion),
  frame(s.frame),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
 worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  Xaxis(),
  maxDistance(s.maxDistance),
  tooFar(false), hasExploded(false)

{ }

Sprite& Sprite::operator=(const Sprite& rhs) {
  Drawable::operator=( rhs );
 explosion = rhs.explosion;
  frame = rhs.frame;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}




void Sprite::draw() const { 
  if (explosion) {
    explosion->draw();
    return;
  }
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y); 
}

void Sprite::explode() { 
  if ( explosion ) return;
  explosion = new ExplodingSprite(*this); 
}



int Sprite::getDistance(const Sprite *obj) const { 
  return hypot(X()-obj->X(), Y()-obj->Y());
}

void Sprite::update(Uint32 ticks) { 
  
if ( explosion ) {
    explosion->update(ticks);
    if ( explosion->chunkCount() == 0 ) {
      delete explosion;
      explosion = NULL;
    }
    return;
  }
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
    tooFar = true;
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
    tooFar =true;
  }  
}
