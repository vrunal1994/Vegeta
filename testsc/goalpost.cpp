#include <iostream>
#include <iomanip>
#include "iomanager.h"
#include "goalpost.h"


Goalpost::Goalpost(const std::string& name):
io( IOManager::getInstance() ),
setColorKey(false),
screen(io.getScreen()),
image(io.loadAndSet(name,setColorKey)),
imagewidth(650),
imageheight(200)
{


}



Goalpost::~Goalpost(){


}

void Goalpost::draw() const { 
Uint16 w = image->w;
  Uint16 h = image->h;
  Sint16 xCoord = static_cast<Sint16>(imagewidth);
  Sint16 yCoord = static_cast<Sint16>(imageheight);
  SDL_Rect src = { 0, 0, w, h };
  SDL_Rect dest = {xCoord, yCoord, 0, 0 };
  SDL_BlitSurface(image, &src, screen, &dest);

}

void Goalpost::freesurface(){
	
	SDL_FreeSurface(image);
}

void Goalpost::update(){


}