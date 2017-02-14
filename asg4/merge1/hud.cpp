#include"hud.h"
#include "gamedata.h"
void HUD::drawHUD(SDL_Surface*  screen,  int x,  int y) const {

  const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
  Draw_AALine(screen, x, y+Gamedata::getInstance().getXmlInt("HUD/HUD_HEIGHT")/2, 
                      x+Gamedata::getInstance().getXmlInt("HUD/HUD_WIDTH"),y+Gamedata::getInstance().getXmlInt("HUD/HUD_HEIGHT")/2, 
                      Gamedata::getInstance().getXmlInt("HUD/HUD_HEIGHT"), 0xff, 0xff, 0xff, 0xff/2);
  Draw_AALine(screen, x,y, x+ Gamedata::getInstance().getXmlInt("HUD/HUD_WIDTH"),y, RED);
}
