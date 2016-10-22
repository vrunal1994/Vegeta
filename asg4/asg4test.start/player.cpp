#include "player.h"
#include <iostream>
#include "vector2f.h"
#include "clock.h"
#include "frameFactory.h"
#include "explodingSprite.h"
Player:: ~Player(){
  
}
void Player::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
          if(right){
            currentFrame = (currentFrame+1) %(numberOfFrames/2);
  if(currentFrame==0)currentFrame=0;
          	
 		}
          else if(left){
          currentFrame = (currentFrame+1) %(numberOfFrames);
    if(currentFrame==0)currentFrame=numberOfFrames/2;
}
	else if(up){
	 //currentFrame=(currentFrame+1)%(numberOfFrames*3/4);
	//if(currentFrame==0)currentFrame=numberOfFrames/2;	
	}
	else if(down){
	// currentFrame=(currentFrame+1)%(numberOfFrames/4);
    //    if(currentFrame==0)currentFrame=0;	
	}
	  timeSinceLastFrame = 0;
	}
}
Player::Player( const std::string& name, 
                          const std::vector<Frame*>& f) :Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ) ,turn(false), frames( f ),timeSinceLastFrame( 0 ),left(false),right(false),up(false),
down(false),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
  
{ 
}
void Player::toggleLeft(){	  
  currentFrame=numberOfFrames/2;
  left=!left;
}
void Player::toggleRight(){
currentFrame=0;	  
  right=!right;
}
void Player::toggleUp(){
//currentFrame=numberOfFrames/2;
  up=!up;
}
void Player::toggleDown(){
//currentFrame=0;
  down=!down;
}
void Player::draw() const{
 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
    frames[currentFrame]->draw(x, y);

}


void Player::update(Uint32 ticks){

if(left || right||up||down)
  advanceFrame(ticks);

  if(left && !right)
    setPosition(Vector2f(getPosition()[0]-getVelocity()[0] * static_cast<float>(ticks)*0.001,getPosition()[1]));
  else if(right && !left)
    setPosition(Vector2f(getPosition()[0]+getVelocity()[0] * static_cast<float>(ticks)*0.001,getPosition()[1]));
  if(up && !down)
    setPosition(Vector2f(getPosition()[0],getPosition()[1]-getVelocity()[1] * static_cast<float>    (ticks)*0.001));
  else if(down && !up)
   setPosition(Vector2f(getPosition()[0],getPosition()[1]+getVelocity()[1] * static_cast<float>(ticks)*0.001));
  if(X() < 0){
    setPosition(Vector2f(0,getPosition()[1]));
}
  else if(X() > (worldWidth-frameWidth)){
 
    setPosition(Vector2f(worldWidth-frameWidth,getPosition()[1]));
   }
  if(Y() < 0){
    setPosition(Vector2f(getPosition()[0],0));
}
  else if(Y() > (worldHeight-frameHeight))
    setPosition(Vector2f(getPosition()[0],(worldHeight-frameHeight)));
}
