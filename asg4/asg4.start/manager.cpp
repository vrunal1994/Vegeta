#include <iostream>
#include <string>
#include <iomanip>
#include "multisprite.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"
#include "twoWayMultiSprite.h"
#include <algorithm>

Manager::~Manager() { 
  // These deletions eliminate "definitely lost" and
  // "still reachable"s in Valgrind.
  for (unsigned i = 0; i < sprites.size(); ++i) {
    delete sprites[i];
  }
 
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
   scaledSpriteSurface( io.loadAndSet(Gamedata::getInstance().getXmlStr("dragonball/file"), 
              Gamedata::getInstance().getXmlBool("dragonball/transparency")) ),
  world("mountains", Gamedata::getInstance().getXmlInt("mountains/factor") ),
  mountains("trees", Gamedata::getInstance().getXmlInt("trees/factor") ),
 
  viewport( Viewport::getInstance() ),
  scaledSprites(),
  player("player"),
  sprites(),
  currentSprite(0),

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

  sprites.push_back( new TwoWayMultiSprite("charizard","charizard1") );
   sprites.push_back( new MultiSprite("bulbasaur") );
   
  sprites.push_back( new Sprite("pokeball") );
  
   makescaledSprites();
  viewport.setObjectToTrack(sprites[currentSprite]);
 
}

void Manager::makescaledSprites() {
  unsigned numberOfscaledSprites = Gamedata::getInstance().getXmlInt("numberOfSprites");
  scaledSprites.reserve( numberOfscaledSprites );

  for (unsigned i = 0; i < numberOfscaledSprites; ++i) {
    scaledSprites.push_back( new ScaledSprite("dragonball", scaledSpriteSurface) );
  }
  sort(scaledSprites.begin(), scaledSprites.end(), ScaledSpriteCompare());
}

void Manager::printscaledSprites() const {
  for (unsigned i = 0; i < scaledSprites.size(); ++i) {
    std::cout << scaledSprites[i]->getScale() << std::endl;
  }
}


void Manager::draw()  const{
  
  world.draw();
  for (unsigned i = 0; i < scaledSprites.size()/2; ++i){
    scaledSprites[i]->draw();

  }
  mountains.draw();
  for (unsigned i = scaledSprites.size()/2 ; i < scaledSprites.size(); ++i){
    scaledSprites[i]->draw();
  }
  
  //clock.display();

  for (unsigned i = 0; i < sprites.size(); ++i) {
    sprites[i]->draw();
  }
player.draw();
  if(clock.getSeconds()<2){
    hud.drawHUD(screen, Gamedata::getInstance().getXmlInt("HUD/startX"), Gamedata::getInstance().getXmlInt("HUD/startX"));

    io.printMessageAt("Press F1 to toggle HUD", 10, 70);
  clock.display();
  io.printMessageAt("Press T to switch sprites", 10, 110);
  io.printMessageAt("Press 2 to multiply pokeballs", 10, 130);
  io.printMessageAt("Press 0 to explode all sprites", 10, 150);
  io.printMessageAt("Press P to pause", 10, 170);
  io.printMessageAt("Press S for slow motion", 10, 190);
   
}
   else if(drawHud == true){
  hud.drawHUD(screen, Gamedata::getInstance().getXmlInt("HUD/startX"), Gamedata::getInstance().getXmlInt("HUD/startX"));

    io.printMessageAt("Press F1 to toggle HUD", 10, 70);
    clock.display();
    io.printMessageAt("Press T to switch sprites", 10, 110);
  io.printMessageAt("Press 2 to multiply pokeballs", 10, 130);
  io.printMessageAt("Press 0 to explode all sprites", 10, 150);
  io.printMessageAt("Press P to pause", 10, 170);
  io.printMessageAt("Press S for slow motion", 10, 190);
  

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

void Manager::switchSprite() {
  currentSprite = (currentSprite+1) % sprites.size();
  viewport.setObjectToTrack(sprites[currentSprite]);

}

void Manager::update() {
  clock.update();
  
  Uint32 ticks = clock.getElapsedTicks();

  
  for (unsigned int i = 0; i < sprites.size(); ++i) {
    sprites[i]->update(ticks);
  }
  for (unsigned i = 0; i < scaledSprites.size(); ++i) {
    scaledSprites[i]->update(ticks);
  }
  player.update(ticks);
  player.stop();
  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }

  world.update();
  mountains.update();
  
  viewport.update(); // always update viewport last
}

void Manager::play() {
  SDL_Event event;
  bool done = false;
  
  while ( not done ) {
  
    while ( SDL_PollEvent(&event) ) {
      Uint8 *keystate = SDL_GetKeyState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
          break;
        }

        if ( keystate[SDLK_t] ) {
          switchSprite();
        }

        if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }
         
   if (keystate[SDLK_F1]) {
          if(drawHud == true) drawHud = false ;
          else if(drawHud == false) drawHud = true;
        }
         
  
        /*switch(event.key.keysym.sym){
        case SDLK_a:
    player.left();  break;
        case SDLK_d:
    player.right(); break; 
        case SDLK_w:
    player.up(); break; 
        case SDLK_s:
    player.down(); break;  
  default:break;
      }*/
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
     
        switch(event.key.keysym.sym){
        case SDLK_a:
    player.left();  break;
        case SDLK_d:
    player.right(); break; 
        case SDLK_w:
    player.up(); break; 
        case SDLK_s:
    player.down(); break; 
  default:break; 
   
     } 
  

    }
    draw();
  
    update();
  }
}