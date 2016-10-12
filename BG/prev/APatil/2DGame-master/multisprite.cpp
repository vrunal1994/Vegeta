#include "multisprite.h"
#include "gamedata.h"
#include "explodingSprite.h"
MultiSprite:: ~MultiSprite(){
  delete explosion;
}
void MultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
          currentFrame = (currentFrame+1) %numberOfFrames;
	  timeSinceLastFrame = 0;
	}
}
MultiSprite::MultiSprite( const std::string& name, 
                          const std::vector<Frame*>& f) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/loc/x"), 
		   (rand()%2?1:-1)*getRandom(Gamedata::getInstance().getXmlInt(name+"/cushion"),Gamedata::getInstance().getXmlInt(name+"/loc/y"))
), 
           Vector2f(getRandom(
                    Gamedata::getInstance().getXmlInt(name+"/cushion"),
                    Gamedata::getInstance().getXmlInt(name+"/speed/x")),
		0)
  ),
  smart(false),
  explosion(NULL),
  frames( f ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  player(false),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  girlBoundHorizontal(0)
{ }

void MultiSprite::draw() const { 
  if (explosion) {
    explosion->draw();
    return;
  }
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  if(!girlBoundHorizontal){
    frames[currentFrame]->draw(x, y);
  }
  else
  {
    frames[currentFrame]->drawSpin(x, y);
}
}
bool MultiSprite::IAmExploding()const{
  if(explosion)return true;
  else return false;
}
void MultiSprite::explode() { 
  if ( explosion ) return;
  Sprite sprite(getName(), getPosition(), getVelocity(), getFrame());
  explosion = new ExplodingSprite(sprite); 
}
void MultiSprite::reset(){
  X(worldWidth-frameWidth);
}
void MultiSprite::update(Uint32 ticks) { 
  if ( explosion ) {
    explosion->update(ticks);
    if ( explosion->chunkCount() == 0 ) {
      delete explosion;
      explosion = NULL;
    }
    return;
}
  advanceFrame(ticks);
  Vector2f deltaDistance = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() - deltaDistance);

  if ( X() < 0) { 
  reset();   
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) ); 
 }
}
