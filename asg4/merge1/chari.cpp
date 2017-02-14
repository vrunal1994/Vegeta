#include "chari.h"
#include "gamedata.h"
#include "frameFactory.h"

Charizard::Charizard(const std::string& name):
  Drawable(name, 
        Vector2f(Gamedata::getInstance().getXmlInt(name+ "/startLoc/x")),
        Vector2f(Gamedata::getInstance().getXmlInt(name+ "/startLoc/y"))),
  frames(FrameFactory::getInstance().getFrames(name)),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  movSpeedX( Gamedata::getInstance().getXmlInt(name+"/speedX") ),
  movSpeedY( Gamedata::getInstance().getXmlInt(name+"/speedY") ),
  direction( 1 ),
    CharizardLeft(false),
  CharizardRight(false),
  CharizardUp(false),
  CharizardDown(false),
  CharizardIdle(true)
{ }

Charizard::Charizard(const Charizard& s) :
  Drawable(s), 
  frames(s.frames),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight ),
  movSpeedX( s.movSpeedX ),
  movSpeedY( s.movSpeedY ),
  direction( s.direction ),
  CharizardLeft(s.CharizardLeft),
  CharizardRight(s.CharizardRight),
  CharizardUp(s.CharizardUp),
  CharizardDown(s.CharizardDown),
  CharizardIdle(s.CharizardIdle)
{ }

void Charizard::draw() const 
{
    Uint32 x =static_cast<Uint32>(X());
    Uint32 y =static_cast<Uint32>(Y());
    frames[currentFrame]->draw(x,y); 
}

void Charizard::update(Uint32 ticks) 
{
advanceFrame(ticks);
  Uint8 *keyPressed = SDL_GetKeyState(NULL);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  //vertical movement
  if(keyPressed[SDLK_UP])
  {
    if(Y() > 0)
      velocityY( -movSpeedY );
    else
      Y(0);
  }
  else if(keyPressed[SDLK_DOWN])
  {
    if(Y() < worldHeight-frameHeight)
      velocityY( movSpeedY );
    else
      Y(worldHeight-frameHeight);
  }
  else
   { velocityY(0);}
  
  if(!keyPressed[SDLK_LEFT] && !keyPressed[SDLK_RIGHT])
  {CharizardIdle =true;
  CharizardLeft =false;
  CharizardRight =false;}
  //horizontal movement
  if(keyPressed[SDLK_RIGHT])
  {CharizardIdle =false;
  CharizardLeft =false;
  CharizardRight =true;
    if(X() < worldWidth-frameWidth)
      velocityX( movSpeedY );
    else
      X(worldWidth-frameWidth);
    direction = 1;   
  }
  else if(keyPressed[SDLK_LEFT])
  {
      CharizardIdle =false;
  CharizardLeft =true;
  CharizardRight =false;
    if(X() > 0)
      velocityX( -movSpeedY );
    else
      X(0);
    direction = 0;
  }
  else
    velocityX(0);
  
  //superspeed
  if(keyPressed[SDLK_SPACE])
    velocityX( 2*velocityX() );

  //timeSinceLastBullet +=ticks;
//  bullets.update(ticks);
}

void Charizard :: advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval )
    {
        if( CharizardRight && direction) {
         
    currentFrame = (currentFrame+1) %(numberOfFrames/2);
  if(currentFrame==0)currentFrame=0;
		timeSinceLastFrame = 0;
	}
        if( CharizardIdle ) {
         
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
    if (timeSinceLastFrame > frameInterval )
    {
        if( CharizardLeft && (direction<1)) {
         
     currentFrame = (currentFrame+1) %(numberOfFrames);
          
    if(currentFrame==0)currentFrame=numberOfFrames/2;
		timeSinceLastFrame = 0;
	}
    }
    }
}