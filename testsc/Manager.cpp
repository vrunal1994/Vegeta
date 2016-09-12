#include <iostream>
#include <string>
#include "Manager.h"



Manager::~Manager(){

}

Manager::Manager():
env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
io( IOManager::getInstance() ),

screen(io.getScreen()),
ground("images/PoolTable.bmp"),
fball("images/ball.bmp")



{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw( std::string("Unable to initialize SDL: ")+ SDL_GetError());
  }
  atexit(SDL_Quit);
}

void Manager::play()
{
	SDL_Event event;
   
  	bool done = false;
  	while ( !done) {
      while ( SDL_PollEvent(&event) ) {
        if (event.type == SDL_QUIT) done = true;
        if (event.type == SDL_KEYDOWN) {
          if (event.key.keysym.sym == SDLK_ESCAPE) done = true;
        }
      }
      draw();
     
      update();
      
      }

  ground.freesurface(); 
  fball.freesurface();  
 // gpost.freesurface();   


      
}

void Manager::draw() const {
  //sky.draw();
  ground.draw();
  fball.draw();
  //gpost.draw();
  SDL_Flip(screen);
  
}

void Manager::update() {
  fball.update();
  
   
  // always update viewport last
}
