#include "vegeta.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "explodingSprite.h"

Vegeta::~Vegeta()
{
  delete explosion;

}

Vegeta::Vegeta(const std::string& name):
  Drawable(name, 
        Vector2f(Gamedata::getInstance().getXmlInt(name+ "/startLoc/x"),
        Gamedata::getInstance().getXmlInt(name+ "/startLoc/y")),
        Vector2f(Gamedata::getInstance().getXmlInt(name+"/movSpeedX"),
                    Gamedata::getInstance().getXmlInt(name+"/movSpeedY"))),
  frames(FrameFactory::getInstance().getFrames(name)),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  explosion(NULL),
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

/*Vegeta::Vegeta(const std::string& name, const Vector2f& pos, const Vector2f& vel,
               const std::vector<Frame*>& frm):
  Drawable(name, pos, vel), 
 frames(frm),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  explosion(NULL),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frame[0]->getHeight()),
  movSpeedX( Gamedata::getInstance().getXmlInt(name+"/movSpeedX") ),
  movSpeedY( Gamedata::getInstance().getXmlInt(name+"/movSpeedY") ),
  direction( 1 ),
  
    VegetaLeft(false),
  VegetaRight(false),
  VegetaIdle(true)
{ }*/

Vegeta::Vegeta(const Vegeta& s) :
  Drawable(s), 
  frames(s.frames),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  explosion(s.explosion),
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

  if (explosion) {
    explosion->draw();
    return;
  }
    Uint32 x =static_cast<Uint32>(X());
    Uint32 y =static_cast<Uint32>(Y());
    frames[currentFrame]->draw(x,y); 

    /*std::cout<<"Vegeta X"<<x<<std::endl;
    std::cout<<"Vegeta Y"<<y<<std::endl;*/

}

void Vegeta::explode() { 
  if ( explosion ) return;
  else{
  //setHealth(getHealth()-20);
  Sprite sprite(getName(), getPosition(), getVelocity(), getFrame());
  explosion = new ExplodingSprite(sprite);
  }
}
void Vegeta::update(Uint32 ticks) 
{

  if ( explosion ) {
    explosion->update(ticks);
    if ( explosion->chunkCount() == 0 ) {
      delete explosion;
      explosion = NULL;
    } 
    return;
}

advanceFrame(ticks);
  Uint8 *keyPressed = SDL_GetKeyState(NULL);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);



  
  //vertical movement
  if(keyPressed[SDLK_w])
  {
    if(keyPressed[SDLK_s])
    {
      
      velocityY(0);
      velocityX(0);
    }
    else{
    if(Y() > 0)
      velocityY( -movSpeedY );
    else
      Y(0);
  }
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
  VegetaRight =false;
  
  }
  //horizontal movement
  if(keyPressed[SDLK_d])
  {
    if(keyPressed[SDLK_a])
    {
      VegetaIdle =true;
  VegetaLeft =false;
  VegetaRight =true;
  //Vegetastop=false;
  velocityY(0);
  velocityX(0);
    }
    else
    {
    VegetaIdle =false;
  VegetaLeft =false;
  VegetaRight =true;
  
  if(X() < worldWidth-frameWidth)
      velocityX( movSpeedY );
    else
      X(worldWidth-frameWidth);
    direction = 1;
}
       
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
         //std::cout<<"called idle"<<std::endl;
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