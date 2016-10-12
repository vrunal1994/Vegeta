#include <iostream>
#include <string>
#include <iomanip>
#include "vector2f.h"
#include "multisprite.h"
#include "twoWayMultiSprite.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"
#include "extractSurface.h"
#include <algorithm>


Manager::~Manager() { 
  SDL_FreeSurface(scaledSpriteSurface);
  
  for (unsigned i = 0; i < scaledSprites.size(); ++i) {
    delete scaledSprites[i];
  }
  scaledSprites.clear();  
}
class ScaledSpriteCompare {
public:
  bool operator()(const ScaledSprite* lhs, const ScaledSprite* rhs) {
    return lhs->getScale() < rhs->getScale();
  }
};

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  hud(),
  drawHud(false),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  scaledSpriteSurface( io.loadAndSet(Gamedata::getInstance().getXmlStr("ball/file"), 
              Gamedata::getInstance().getXmlBool("ball/transparency")) ),
  world1("back1", Gamedata::getInstance().getXmlInt("back1/factor") ),
world2("back2", Gamedata::getInstance().getXmlInt("back2/factor") ),
world3("back3", Gamedata::getInstance().getXmlInt("back3/factor") ),
world4("back4", Gamedata::getInstance().getXmlInt("back4/factor") ),

  viewport( Viewport::getInstance() ),
  scaledSprites(),
   player("player"),

  makeVideo( false ),
  frameCount( 0 ),
  username(  Gamedata::getInstance().getXmlStr("username") ),
  title( Gamedata::getInstance().getXmlStr("screenTitle") ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") )
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  SDL_WM_SetCaption(title.c_str(), NULL);
  atexit(SDL_Quit);
     makescaledSprites();
  viewport.setObjectToTrack(player.getSprite());
}

void Manager::makescaledSprites() {
  unsigned numberOfscaledSprites = Gamedata::getInstance().getXmlInt("numberOfSprites");
  scaledSprites.reserve( numberOfscaledSprites );

  for (unsigned i = 0; i < numberOfscaledSprites; ++i) {
    scaledSprites.push_back( new ScaledSprite("ball", scaledSpriteSurface) );
  }
  sort(scaledSprites.begin(), scaledSprites.end(), ScaledSpriteCompare());
}

void Manager::printscaledSprites() const {
  for (unsigned i = 0; i < scaledSprites.size(); ++i) {
    std::cout << scaledSprites[i]->getScale() << std::endl;
  }
}

void Manager::draw()  {
  world1.draw();
for (unsigned i = 0; i < scaledSprites.size()/4; ++i){
    scaledSprites[i]->draw();

  }
world2.draw();
for (unsigned i = scaledSprites.size()/4 ; i < scaledSprites.size()/2; ++i){
    scaledSprites[i]->draw();
  }
world3.draw();
for (unsigned i = scaledSprites.size()/2 ; i < scaledSprites.size()*(3/4); ++i){
    scaledSprites[i]->draw();
  }
world4.draw();

  

 for (unsigned i = scaledSprites.size()*(3/4) ; i < scaledSprites.size(); ++i){
   scaledSprites[i]->draw();
  }

  
    player.draw();

  if(clock.getSeconds()<2){
    hud.drawHUD(screen, Gamedata::getInstance().getXmlInt("HUD/startX"), Gamedata::getInstance().getXmlInt("HUD/startX"));

    io.printMessageAt("Press F1 to toggle HUD", 10, 70);
  clock.draw();
   io.printMessageAt("Use arrows to control ", 10, 110);
      io.printMessageAt("the player", 10, 130);
}
   else if(drawHud == true){
  hud.drawHUD(screen, Gamedata::getInstance().getXmlInt("HUD/startX"), Gamedata::getInstance().getXmlInt("HUD/startX"));

    io.printMessageAt("Press F1 to toggle HUD", 10, 70);
  clock.draw();
  io.printMessageAt("Use arrows to control ", 10, 110);
      io.printMessageAt("the player", 10, 130);

 }
  io.printMessageAt(title, 10, 450);
 
  viewport.draw();

  SDL_Flip(screen);
}

 void Manager::makeFrame() {
  std::stringstream strm;
  strm << "frames/" << username<< '.' 
       << std::setfill('0') << std::setw(4) 
       << frameCount++ << ".bmp";
  std::string filename( strm.str() );
  std::cout << "Making frame: " << filename << std::endl;
  SDL_SaveBMP(screen, filename.c_str());
}


void Manager::update() {
  clock.update();
  Uint32 ticks = clock.getTicksSinceLastFrame();

   for (unsigned i = 0; i < scaledSprites.size(); ++i) {
    scaledSprites[i]->update(ticks);
  }
  player.update(ticks);
  player.stop();
 
  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }
  world1.update();
  world2.update();
  world3.update();
  world4.update();
  viewport.update(); // always update viewport last
}

void Manager::play() {
  SDL_Event event;

  bool done = false;
  bool keyCatch = false;
  while ( not done ) {

    SDL_PollEvent(&event);
    Uint8 *keystate = SDL_GetKeyState(NULL);
    if (event.type ==  SDL_QUIT) { done = true; break; }
    if(event.type == SDL_KEYUP) { 
      keyCatch = false; 
    }
    if(event.type == SDL_KEYDOWN) {
      if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
        done = true;
        break;
      }
      
      if (keystate[SDLK_s] && !keyCatch) {
        keyCatch = true;
        clock.toggleSloMo();
      }
  if ( keystate[SDLK_F1] ) {

          if(drawHud == true) drawHud = false ;
          else if(drawHud == false) drawHud = true;

        }
    
    }
 if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }
        
    if (keystate[SDLK_LEFT]) {
      player.left();
    }
    if (keystate[SDLK_RIGHT]) {
      player.right();
    }
    if (keystate[SDLK_UP]) {
      player.up();
    }
    if (keystate[SDLK_DOWN]) {
      player.down();
    }

    draw();
    SDL_Flip(screen);

    update();
  }
}
