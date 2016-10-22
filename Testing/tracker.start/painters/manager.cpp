#include <cmath>
#include <algorithm>
#include "manager.h"

class ScaledSpriteCompare {
public:
  bool operator()(const ScaledSprite* lhs, const ScaledSprite* rhs) {
    return lhs->getScale() < rhs->getScale();
  }
};

Manager::~Manager() { 
  SDL_FreeSurface(orbSurface);
  SDL_FreeSurface(backSurface);
  for (unsigned i = 0; i < orbs.size(); ++i) {
    delete orbs[i];
  }
  orbs.clear();
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  gdata( Gamedata::getInstance() ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  orbSurface( io.loadAndSet(gdata.getXmlStr("redorb/file"), 
              gdata.getXmlBool("redorb/transparency")) ),
  backSurface( io.loadAndSet(gdata.getXmlStr("back/file"), 
              gdata.getXmlBool("back/transparency")) ),
  backFrame(backSurface,
                gdata.getXmlInt("back/width"), 
                gdata.getXmlInt("back/height"), 
                gdata.getXmlInt("back/src/x"), 
                gdata.getXmlInt("back/src/y")
  ),
  orbs()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  atexit(SDL_Quit);
  makeOrbs();
  printOrbs();
}

void Manager::makeOrbs() {
  unsigned numberOfOrbs = gdata.getXmlInt("numberOfOrbs");
  orbs.reserve( numberOfOrbs );
  for (unsigned i = 0; i < numberOfOrbs; ++i) {
    orbs.push_back( new ScaledSprite("redorb", orbSurface) );
  }
  sort(orbs.begin(), orbs.end(), ScaledSpriteCompare());
}

void Manager::printOrbs() const {
  for (unsigned i = 0; i < orbs.size(); ++i) {
    std::cout << orbs[i]->getScale() << std::endl;
  }
}

void Manager::draw() const {
  backFrame.draw(0,0);
  for (unsigned i = 0; i < orbs.size(); ++i) {
    orbs[i]->draw();
  }
}

void Manager::update() {
  Uint32 ticks = clock.getElapsedTicks();
  for (unsigned i = 0; i < orbs.size(); ++i) {
    orbs[i]->update(ticks);
  }
}

void Manager::play() {
  SDL_Event event;

  bool done = false;
  bool keyCatch = false;
  //printOrbs();
  while ( not done ) {
    draw();
    SDL_Flip(screen);
    update();

    SDL_PollEvent(&event);
    if (event.type ==  SDL_QUIT) { break; }
    if(event.type == SDL_KEYUP) { keyCatch = false; }
    if(event.type == SDL_KEYDOWN) {
      switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE : done = true; break;
        case SDLK_q      : done = true; break;
        case SDLK_p      : {
          if (!keyCatch) {
            keyCatch = true;
            if ( clock.isPaused() ) clock.unpause();
            else clock.pause();
          }
          break;
        }
        default          : break;
      }
    }
  }
}
