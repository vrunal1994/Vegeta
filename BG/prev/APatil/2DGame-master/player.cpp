#include "player.h"
#include <iostream>
#include "vector2f.h"
#include "clock.h"
#include "frameFactory.h"
#include "explodingSprite.h"
Player:: ~Player(){
  delete explosion;
  std::list<Bullet>::iterator it=bulletList.begin();
  std::list<Bullet>::iterator itf=freeList.begin();
  while(it!=bulletList.end()){
  it=bulletList.erase(it);
}
bulletList.clear();
while(itf!=freeList.end()){
  itf=freeList.erase(itf);
}	
freeList.clear();
}
void Player::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
          if(right){
          currentFrame = (currentFrame+1) %(numberOfFrames);
		if(currentFrame==0)currentFrame=numberOfFrames*3/4;	
 		}
          else if(left){
          currentFrame = (currentFrame+1) %(numberOfFrames/2);
	if(currentFrame==0)currentFrame=numberOfFrames/4;
}
	else if(up){
	 currentFrame=(currentFrame+1)%(numberOfFrames*3/4);
	if(currentFrame==0)currentFrame=numberOfFrames/2;	
	}
	else if(down){
	 currentFrame=(currentFrame+1)%(numberOfFrames/4);
         if(currentFrame==0)currentFrame=0;	
	}
	  timeSinceLastFrame = 0;
	}
}
Player::Player( const std::string& name, 
                          const std::vector<Frame*>& f) :Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ) ,turn(false),shot(false),goneFar(false),win(false),lost(false),explosion(NULL), frames( f ),timeSinceLastFrame( 0 ),left(false),right(false),up(false),
down(false),health(Gamedata::getInstance().getXmlInt("Health/helt")),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  bulletList(),
  freeList()
{ 
}
void Player::toggleLeft(){	  
  currentFrame=numberOfFrames/4;
  left=!left;
}
void Player::toggleRight(){
currentFrame=numberOfFrames*3/4;	  
  right=!right;
}
void Player::toggleUp(){
currentFrame=numberOfFrames/2;
  up=!up;
}
void Player::toggleDown(){
currentFrame=0;
  down=!down;
}
void Player::draw() const{
  if (explosion) {
    explosion->draw();
    return;
  }
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
    frames[currentFrame]->draw(x, y);
std::list<Bullet>::const_iterator itB=bulletList.begin();
while(itB!=bulletList.end()){
(*itB).draw();
itB++;
}
}
void Player::shoot(const std::string& name,const Vector2f& pos,const Vector2f& vel,const Frame* frm){
  if(freeList.empty()){
  if(currentFrame>=numberOfFrames/4 && currentFrame<numberOfFrames/2)
  bulletList.push_back(Bullet(name,pos,vel*-2,frm));
  else if(currentFrame>=numberOfFrames*3/4 && currentFrame<numberOfFrames)
  bulletList.push_back(Bullet(name,pos,vel*2,frm));
}
  else if((currentFrame>=numberOfFrames/4 && currentFrame<numberOfFrames/2)||(currentFrame>=numberOfFrames*3/4 && currentFrame<numberOfFrames)){
    Bullet bul=freeList.front();
    freeList.pop_front();
    bul.reset();
    if(currentFrame>=numberOfFrames/4 && currentFrame<numberOfFrames/2)
       bul.setVelocity(vel*-2);
    else if(currentFrame>=numberOfFrames*3/4 && currentFrame<numberOfFrames)
       bul.setVelocity(vel*2);
  bul.setPosition(pos);
  bulletList.push_back(bul);
}
}
void Player::explode() { 
  if ( explosion ) return;
  else{
  setHealth(getHealth()-20);
  Sprite sprite(getName(), getPosition(), getVelocity(), getFrame());
  explosion = new ExplodingSprite(sprite);
  }
}
void Player::update(Uint32 ticks){
if ( explosion ) {
    explosion->update(ticks);
    if ( explosion->chunkCount() == 0 ) {
      delete explosion;
      explosion = NULL;
    } 
    return;
}
if(left || right||up||down)
  advanceFrame(ticks);
std::list<Bullet>::iterator it=bulletList.begin();
while(it!=bulletList.end()){
  (*it).update(ticks);
      if(it->goneFar()){
        freeList.push_back(*it);
	it=bulletList.erase(it);
      }
it++;
}
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
 win = true;
    setPosition(Vector2f(worldWidth-frameWidth,getPosition()[1]));
   }
  if(Y() < (worldHeight-frameHeight)/1.5){
    setPosition(Vector2f(getPosition()[0],(worldHeight-frameHeight)/1.5));
}
  else if(Y() > (worldHeight-frameHeight))
    setPosition(Vector2f(getPosition()[0],(worldHeight-frameHeight)));
}
