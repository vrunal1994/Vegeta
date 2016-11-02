
.#include <iostream>
#include <string>
#include <iomanip>
#include "multisprite.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"
#include "twoWayMultiSprite.h"

Manager::~Manager() { 
  // These deletions eliminate "definitely lost" and
  // "still reachable"s in Valgrind.
  for (unsigned i = 0; i < sprites.size(); ++i) {
    delete sprites[i];
  }
 
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  world("mountains", Gamedata::getInstance().getXmlInt("mountains/factor") ),
  mountains("trees", Gamedata::getInstance().getXmlInt("trees/factor") ),
 
  viewport( Viewport::getInstance() ),
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
  
   
  viewport.setObjectToTrack(sprites[currentSprite]);
 
}

void Manager::draw() const {
  
  world.draw();
  mountains.draw();
  
  clock.display();

  for (unsigned i = 0; i < sprites.size(); ++i) {
    sprites[i]->draw();
  }

  io.printMessageAt("Press T to switch sprites", 10, 45);
  io.printMessageAt("Press 2 to multiply pokeballs", 600, 15);
  io.printMessageAt("Press 0 to explode all sprites", 600, 40);
  io.printMessageAt("Press P to pause", 700, 65);
  io.printMessageAt("Press S for slow motion", 650, 90);
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
         if ( keystate[SDLK_0] ) {
          for (unsigned int i = 0; i < sprites.size(); ++i) {
          sprites[i]->explode();
          }
        }
        
        if ( keystate[SDLK_2] ) {
          unsigned int n = Gamedata::getInstance().getXmlInt("numberOfSprites"); 
          for(unsigned int  i=0;i<n;i++){
              sprites.push_back( 
            new Sprite("pokeball") );
          }
        
        }

        if ( keystate[SDLK_t] ) {
          switchSprite();
        }
        if ( keystate[SDLK_s] ) {
          clock.toggleSloMo();
        }
        if ( keystate[SDLK_p] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }
      }
    }
    draw();
    update();
  }
}
