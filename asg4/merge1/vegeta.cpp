#include "vegeta.h"
#include "gamedata.h"
#include "frameFactory.h"

Vegeta::Vegeta(const std::string& name):
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
  movSpeedX( Gamedata::getInstance().getXmlInt(name+"/movSpeedX") ),
  movSpeedY( Gamedata::getInstance().getXmlInt(name+"/movSpeedY") ),
  direction( 1 ),
    VegetaLeft(false),
  VegetaRight(false),
  VegetaIdle(true)
{ }

Vegeta::Vegeta(const Vegeta& s) :
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
  VegetaLeft(s.VegetaLeft),
  VegetaRight(s.VegetaRight),
  VegetaIdle(s.VegetaIdle)
{ }

void Vegeta::draw() const 
{
    Uint32 x =static_cast<Uint32>(X());
    Uint32 y =static_cast<Uint32>(Y());
    frames[currentFrame]->draw(x,y); 
}

void Vegeta::update(Uint32 ticks) 
{
advanceFrame(ticks);
  Uint8 *keyPressed = SDL_GetKeyState(NULL);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  //vertical movement
  if(keyPressed[SDLK_w])
  {
    if(Y() > 0)
      velocityY( -movSpeedY );
    else
      Y(0);
  }
  else if(keyPressed[SDLK_s])
  {
    if(Y() < worldHeight-frameHeight)
      velocityY( movSpeedY );
    else
      Y(worldHeight-frameHeight);
  }
  else
   { velocityY(0);}
  
  if(!keyPressed[SDLK_d] && !keyPressed[SDLK_a])
  {VegetaIdle =true;
  VegetaLeft =false;
  VegetaRight =false;}
  //horizontal movement
  if(keyPressed[SDLK_d])
  {VegetaIdle =false;
  VegetaLeft =false;
  VegetaRight =true;
    if(X() < worldWidth-frameWidth)
      velocityX( movSpeedY );
    else
      X(worldWidth-frameWidth);
    direction = 1;   
  }
  else if(keyPressed[SDLK_a])
  {
      VegetaIdle =false;
  VegetaLeft =true;
  VegetaRight =false;
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

void Vegeta :: advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval )
    {
        if( VegetaRight && direction) {
         
    currentFrame = ((currentFrame+1) % 3) + 4;
		timeSinceLastFrame = 0;
	}
        if( VegetaIdle ) {
         
    currentFrame = ((currentFrame+1) % 4 ) ;
		timeSinceLastFrame = 0;
	}
    if (timeSinceLastFrame > frameInterval )
    {
        if( VegetaLeft && (direction<1)) {
         
    currentFrame = ((currentFrame+1) % 3) + 7;
		timeSinceLastFrame = 0;
	}
    }
    }
}