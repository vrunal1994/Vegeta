#include "HUD.h"
//#include "aaline.h"
#include <iomanip>
#include "gamedata.h"
//#include "ioManager.h"
//#include "clock.h"


HUD::HUD():
clock(Clock::getInstance()),
io(IOManager::getInstance())
{}

HUD::~HUD(){}
void HUD::drawHUD(SDL_Surface* screen , int x, int y) const 
{

    const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
  Draw_AALine(screen, x, y+Gamedata::getInstance().getXmlInt("HUD/height")/2, 
                      x+Gamedata::getInstance().getXmlInt("HUD/width"),y+Gamedata::getInstance().getXmlInt("HUD/height")/2, 
                      Gamedata::getInstance().getXmlInt("HUD/height"), 0xff, 0xff, 0xff, 0xff/2);
  Draw_AALine(screen, x,y, x+ Gamedata::getInstance().getXmlInt("HUD/height"),y, RED);
  ++clock;
  io.printMessageValueAt("Frames " , clock.getSeconds() ,10, 15);
   io.printMessageValueAt("Seconds: ", clock.getSeconds(), 10, 35); 		// pointer changed to call-by-refernce 
  io.printMessageAt("Press T to switch sprites", 10, 55);
  IOManager::getInstance()
    .printMessageValueAt("Overall avg : ",clock.fps , 10, 140);		// Average of All the frames
 
  IOManager::getInstance()
    .printMessageValueAt("avg for last 200: ",clock.avgFPS, 10, 160);		// Average of last 200 frames

   
  
}