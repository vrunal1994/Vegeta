#include <iostream>
#include <string>
#include <iomanip>
#include "multisprite.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"
#include <algorithm>
#include <cmath>

class ScaledSpriteCompare{
  public:
  bool operator() (const ScaledSprite* lhs, const ScaledSprite* rhs){
    return lhs->getScale() < rhs->getScale();
  }
};
Manager::~Manager() { 
  // These deletions eliminate "definitely lost" and
  // "still reachable"s in Valgrind.
  for (unsigned i = 0; i < sprites.size(); ++i) {
    delete sprites[i];
  }
  SDL_FreeSurface(orbSurface);
  for(unsigned i=0; i<orbs.size(); ++i)
  {delete orbs[i];}
  orbs.clear();
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  hud(),
  drawHud(false),
  screen( io.getScreen() ),
  orbSurface(io.loadAndSet(Gamedata::
      getInstance().getXmlStr("redorb/file"), Gamedata::
      getInstance().getXmlBool("redorb/transparency"))),
  orbs(),
  world("back", Gamedata::getInstance().getXmlInt("back/factor")),
  mid("fore", Gamedata::getInstance().getXmlInt("fore/factor")),
  last("cloud", Gamedata::getInstance().getXmlInt("cloud/factor")),
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
  sprites.push_back( new MultiSprite("bat") );
  sprites.push_back( new MultiSprite("joker") );
 // sprites.push_back( new MultiSprite("batFlip") );
 // sprites.push_back( new MultiSprite("jokerFlip") );
  sprites.push_back( new Sprite("batCall") );
  viewport.setObjectToTrack(sprites[currentSprite]);
  makeOrbs();
  printOrbs();
}

void Manager::draw() const {
  world.draw();
  mid.draw();
  last.draw();
  for (unsigned i = 0; i < sprites.size(); ++i) {
    sprites[i]->draw();
  }
  for (unsigned i = 0; i < orbs.size(); ++i) {
    orbs[i]->draw();
  }
  clock.display();
  clock.update();
  //io.printMessageValueAt("Frames " , clock.getFrames() ,10, 5);
  //io.printMessageValueAt("Seconds: ", clock.getSeconds(), 10, 20); 		// pointer changed to call-by-refernce 
  //io.printMessageAt("Press T to switch sprites", 10, 45);
  io.printMessageAt(title, 10, 460);		// Y axis value to print Screen name.
  viewport.draw();
  if(clock.getSeconds() < 5 )
  { hud.drawHUD(screen, 10, 10); }
  if(drawHud)
  { hud.drawHUD(screen, 10, 10); }

  SDL_Flip(screen);
}

void Manager::makeFrame() {
  std::stringstream strm;
  strm << "frames/" << username<< '.' 
       << std::setfill('0') << std::setw(4) 
       << frameCount++ << ".bmp";
  std::string filename( strm.str() );
  std::cout << "Making frame: " << filename << std::endl;
  //io.printMessageValueAt("Frames count" ,frameCount, 10,5);
  SDL_SaveBMP(screen, filename.c_str());
}

void Manager::switchSprite() {
  currentSprite = (currentSprite+1) % sprites.size();
  viewport.setObjectToTrack(sprites[currentSprite]);
}

void Manager::update() {
	  
  ++clock;		// new update function created in Clock to increment clock instance variable values
 
  Uint32 ticks = clock.getElapsedTicks();			// pointer changed to call-by-refernce 

  static unsigned int lastSeconds =clock.getSeconds();			// pointer changed to call-by-refernce 
  if ( clock.getSeconds() - lastSeconds == 5 ) {				// pointer changed to call-by-refernce 
    lastSeconds = clock.getSeconds();						// pointer changed to call-by-refernce 
    //switchSprite();
  }
  
  for (unsigned int i = 0; i < sprites.size(); ++i) {
    sprites[i]->update(ticks);
  }
  for (unsigned i = 0; i < orbs.size(); ++i) {
    orbs[i]->update(ticks);
  }
  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }
  world.update();
  mid.update();
  last.update();
  viewport.update(); // always update viewport last
}

void Manager::makeOrbs() {
  unsigned numberOfOrbs = Gamedata::getInstance().getXmlInt("numberOfOrbs");
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
        if ( keystate[SDLK_s] ) {
          clock.toggleSloMo();				// pointer changed to call-by-refernce 
        }
        if ( keystate[SDLK_p] ) {
          if ( clock.isPaused() ) clock.unpause();		// pointer changed to call-by-refernce 
          else clock.pause();				// pointer changed to call-by-refernce 
        }
        if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }
        if (keystate[SDLK_F1] ) {
          if(drawHud == false) drawHud =true;
          else if(drawHud) drawHud =false; 
          
        }
      }
    }
    draw();
    update();
  }
}
