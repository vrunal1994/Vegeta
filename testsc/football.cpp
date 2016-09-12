#include <iostream>
#include <iomanip>
#include "iomanager.h"
#include "football.h"


Football::Football(const std::string& name):
io( IOManager::getInstance() ),
setColorKey(false),
screen(io.getScreen()),
image(io.loadAndSet(name,setColorKey)),
imagewidth(-image->w),
imageheight(350),
INCR_X(0.3),
X_VELOCITY(300.0),
Width(854),
DT(17u)
{


}



Football::~Football(){


}

void Football::draw() const { 
Uint16 w = image->w;

  Uint16 h = image->h;
  Sint16 xCoord = static_cast<Sint16>(imagewidth);
  Sint16 yCoord = static_cast<Sint16>(imageheight);
  SDL_Rect src = { 0, 0, w, h };
  SDL_Rect dest = {xCoord, yCoord, 0, 0 };

  SDL_BlitSurface(image, &src, screen, &dest);

}

void Football::freesurface(){
	
	SDL_FreeSurface(image);
}

void Football::update(){

	if(imagewidth<=Width-image->w){

		static unsigned int remainder = 0u; // ***
  static unsigned int currentTicks = 0u;
  static unsigned int prevTicks = SDL_GetTicks();
  currentTicks = SDL_GetTicks();
  unsigned int elapsedTicks = currentTicks - prevTicks + remainder; // ***

  if( elapsedTicks > DT ) { // ***

  float incr = X_VELOCITY * DT * 0.001; // ***
  imagewidth += incr;
 /* imageheight-=incr;*/
  prevTicks = currentTicks;
  remainder = elapsedTicks - DT;
  io.printMessageAt("Goal", 400, 70);

	}	
	
}
else{
  
}



}