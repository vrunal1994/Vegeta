#include "charizard.h"
#include <iostream>
#include "vector2f.h"
#include "clock.h"
#include "frameFactory.h"
#include "explodingSprite.h"
Player:: ~Player(){
  std::list<flamethrower>::iterator it=flamethrowerList.begin();
  std::list<flamethrower>::iterator itf=freeList.begin();
  while(it!=flamethrowerList.end()){
  it=flamethrowerList.erase(it);
}
flamethrowerList.clear();
while(itf!=freeList.end()){
  itf=freeList.erase(itf);
} 
freeList.clear();
  
}

void Player::goLeft(Uint32 ticks){
  timeSinceLastFrame += ticks;
  if (timeSinceLastFrame > frameInterval) {
     currentFrame = (currentFrame+1) %(numberOfFrames);
          
    if(currentFrame==0)currentFrame=numberOfFrames/2;
    timeSinceLastFrame = 0;
  }

}

void Player::goRight(Uint32 ticks){
  timeSinceLastFrame += ticks;
  if (timeSinceLastFrame > frameInterval) {
     
            currentFrame = (currentFrame+1) %(numberOfFrames/2);
  if(currentFrame==0)currentFrame=0;
    timeSinceLastFrame = 0;
  }

}

void Player::goUp(Uint32 ticks){
  timeSinceLastFrame += ticks;
  if (timeSinceLastFrame > frameInterval) {
     if(currentFrame<4)
    {
        currentFrame = (currentFrame+1) %(numberOfFrames/2);
  if(currentFrame==0)currentFrame=0;

    }
      else
      {
           currentFrame = (currentFrame+1) %(numberOfFrames);
    if(currentFrame==0)currentFrame=numberOfFrames/2;
      }
    timeSinceLastFrame = 0;
  }

}

void Player::goDown(Uint32 ticks){
  timeSinceLastFrame += ticks;
  if (timeSinceLastFrame > frameInterval) {
     if(currentFrame<4)
    {
        currentFrame = (currentFrame+1) %(numberOfFrames/2);
  if(currentFrame==0)currentFrame=0;

    }
      else
      {
           currentFrame = (currentFrame+1) %(numberOfFrames);
    if(currentFrame==0)currentFrame=numberOfFrames/2;
      }
    timeSinceLastFrame = 0;
  }

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
   
    if(currentFrame<4)
    {
        currentFrame = (currentFrame+1) %(numberOfFrames/2);
  if(currentFrame==0)currentFrame=0;

    }
      else
      {
           currentFrame = (currentFrame+1) %(numberOfFrames);
    if(currentFrame==0)currentFrame=numberOfFrames/2;
      }
	
	}
	else if(down){
   

     if(currentFrame<4)
    {
        currentFrame = (currentFrame+1) %(numberOfFrames/2);
  if(currentFrame==0)currentFrame=0;

    }
      else
      {
           currentFrame = (currentFrame+1) %(numberOfFrames);
    if(currentFrame==0)currentFrame=numberOfFrames/2;
      }
	    
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
down(false),idle(true),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  flamethrowerList(),
  freeList(),
  direction( 1 )
 
  
{ 
  //std::cout<<"callled"<<currentFrame<<std::endl;
}
void Player::toggleLeft(){	  
  currentFrame=numberOfFrames/2;
  left=true;
  right=false;
  idle=false;
  direction=0;
}
void Player::toggleRight(){
currentFrame=0;	  
  right=true;
 left=false;
  idle=false;
  direction=1;
}
void Player::toggleUp(){
    up=true;
    down=false;
    idle=false;

}
void Player::toggleDown(){
  
  idle=false;
up=false;
  down=true;  
}
void Player::stop(){
  //setPosition(Vector2f(getPosition()[0],getPosition()[1]));
  idle=true;
  up=false;
  down=false;
  left=false;
  right=false;
}
void Player::draw() const{
 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
  std::list<flamethrower>::const_iterator itB=flamethrowerList.begin();
  while(itB!=flamethrowerList.end()){
  (*itB).draw();
  itB++;
  }
}

void Player :: IdleState(Uint32 ticks) {
  timeSinceLastFrame += ticks;
  if (timeSinceLastFrame > frameInterval ) {
    if(currentFrame<4)
    {
        currentFrame = (currentFrame+1) %(numberOfFrames/2);
  if(currentFrame==0)currentFrame=0;

    }
      else
      {
           currentFrame = (currentFrame+1) %(numberOfFrames);
    if(currentFrame==0)currentFrame=numberOfFrames/2;
      }
    timeSinceLastFrame = 0;
  }
}

void Player::shoot(const std::string& name,const Vector2f& pos,const Vector2f& vel,const Frame* frm){
  if(freeList.empty()){
  if(currentFrame<4)

  flamethrowerList.push_back(flamethrower(name,pos,vel*2,frm));
  else 
  flamethrowerList.push_back(flamethrower(name,pos,Vector2f(-500,320),frm));

}
  else {
    flamethrower fth=freeList.front();
    freeList.pop_front();
    fth.reset();
            if(currentFrame<4)
            {
fth.setPosition(pos);
  fth.setVelocity(vel*2);
}
  else 
  {
    fth.setPosition(pos);
  fth.setVelocity(Vector2f(-500,320));
  
  }
  
  flamethrowerList.push_back(fth);
}
}
void Player::update(Uint32 ticks){

Uint8 *keystate = SDL_GetKeyState(NULL);
if(!keystate[SDLK_UP]&& !keystate[SDLK_LEFT] && !keystate[SDLK_RIGHT] && !keystate[SDLK_DOWN])
      stop();

  if(idle )
IdleState(ticks);
else if(left && (direction<1))
{
  goLeft(ticks);

}
else if(right && direction)
  goRight(ticks);
else if(up)
  goUp(ticks);
else if(down)
  goDown(ticks);
std::list<flamethrower>::iterator it=flamethrowerList.begin();
while(it!=flamethrowerList.end()){
  (*it).update(ticks);
      if(it->goneFar()){
        freeList.push_back(*it);
  it=flamethrowerList.erase(it);
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
 
    setPosition(Vector2f(worldWidth-frameWidth,getPosition()[1]));
   }
  if(Y() < 0){
    setPosition(Vector2f(getPosition()[0],0));
}
  else if(Y() > (worldHeight-frameHeight))
    setPosition(Vector2f(getPosition()[0],(worldHeight-frameHeight)));
}
