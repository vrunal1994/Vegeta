#include <iostream>
#include <iomanip>
#include "iomanager.h"
#include "table.h"


Table::Table(const std::string& name):
io( IOManager::getInstance() ),
setColorKey(false),
screen(io.getScreen()),
image(io.loadAndSet(name,setColorKey)),
imagewidth(0),
imageheight(0)
{


}



Table::~Table(){


}

void Table::draw() const { 
Uint16 w = image->w;
  Uint16 h = image->h;
  Sint16 xCoord = static_cast<Sint16>(imagewidth);
  Sint16 yCoord = static_cast<Sint16>(imageheight);
  SDL_Rect src = { 0, 0, w, h };
  SDL_Rect dest = {xCoord, yCoord, 0, 0 };
  SDL_BlitSurface(image, &src, screen, &dest);

}

void Table::freesurface(){
	
	SDL_FreeSurface(image);
}

void Table::update(){


}