#include <iostream>
#include <iomanip>
#include "iomanager.h"
#include "football.h"



Football::Football(const std::string& name):
io( IOManager::getInstance() ),
setColorKey(true),
screen(io.getScreen()),
image(io.loadAndSet(name,setColorKey)),
imagewidth(0),
imageheight(240),
INCR_X(0.3),
X_VELOCITY(300.0),
Width(854),
DT(17u),
makeVideo(false),
genframes(screen),
printgoal(false)
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

  if(printgoal){
    io.printMessageCenteredAt("Goal",240);
    SDL_Flip(screen);

  }
}

void Football::freesurface(){
	
	SDL_FreeSurface(image);
}

bool Football::update(){

static unsigned int remainder = 0u; // ***
  static unsigned int currentTicks = 0u;
  static unsigned int prevTicks = SDL_GetTicks();
  currentTicks = SDL_GetTicks();
  unsigned int elapsedTicks = currentTicks - prevTicks + remainder; // ***

  if( elapsedTicks > DT ) { 



	if(imagewidth<=350 && 430<=Width-image->w ){

		// ***

  float incr = X_VELOCITY * DT * 0.001; // ***
  //std::cout<<incr <<std::endl;
  imagewidth += incr;
  float yincr=X_VELOCITY*DT*0.001*0.5;
  imageheight +=yincr;

  prevTicks = currentTicks;
  remainder = elapsedTicks - DT;
  
  return true;
	}	

  else if(imagewidth<=Width-image->w-40){
  //std::cout<<imagewidth<<std::endl;
//std::cout<<imageheight<<std::endl;
  float incr = 250.0 * DT * 0.001; // ***
  //std::cout<<incr <<std::endl;
  imagewidth += incr;
  float yincr=-250.0*DT*0.001*0.9;
  imageheight +=yincr;
  prevTicks = currentTicks;
  remainder = elapsedTicks - DT;

    
  return true;
  }
 // return true;
  else{
    printgoal=true;
    return false;
    //makeVideo=false;
    
    
  }
  if(makeVideo){
    genframes.makeFrame();
  }
	
}
else{
  return false;
}
//return false;




}
