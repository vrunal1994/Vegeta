#include"hud.h"
#include"gamedata.h"
#include "aaline.h"
#include "clock.h"
Hud::Hud(const std::string& hudname):io( IOManager::getInstance() ),
  name(hudname),
  HudStartX(Gamedata::getInstance().getXmlInt(hudname+"/start/x")),
  HudStartY(Gamedata::getInstance().getXmlInt(hudname+"/start/y")),
  HUD_WIDTH(Gamedata::getInstance().getXmlInt(hudname+"/helt")),
  HUD_HEIGHT(Gamedata::getInstance().getXmlInt(hudname+"/height")){}
void Hud::drawHUD(SDL_Surface* screen)const {
  Draw_AALine(screen, HudStartX, HudStartY+HUD_HEIGHT/2, 
                      HudStartX+HUD_WIDTH,HudStartY+HUD_HEIGHT/2, 
                      HUD_HEIGHT, 0xff, 0xff, 0xff, 0xff/2);
  Draw_AALine(screen, HudStartX,HudStartY,HudStartX+HUD_WIDTH,HudStartY, 5,0xff,0,0,0xff);
  Draw_AALine(screen, HudStartX,HudStartY+HUD_HEIGHT,HudStartX+HUD_WIDTH,HudStartY+HUD_HEIGHT, 5,0xff,0,0,0xff);
  Draw_AALine(screen, HudStartX,HudStartY,HudStartX,HudStartY+HUD_HEIGHT,5,0,0,0xff,0xff);
  Draw_AALine(screen, HudStartX+HUD_WIDTH,HudStartY,HudStartX+HUD_WIDTH,HudStartY+HUD_HEIGHT,5,0,0,0xff,0xff);
  Clock::getInstance().draw();
  io.printMessageAt("Press u to cap fps", 45, 45);
}
void Hud::drawHUDdynamic(SDL_Surface* screen,int helt)const{
  io.printMessageAt("Health",HudStartX+10,HudStartY-HUD_HEIGHT);
  Draw_AALine(screen, HudStartX, HudStartY+HUD_HEIGHT/2, 
                      HudStartX+helt,HudStartY+HUD_HEIGHT/2, 
                      HUD_HEIGHT, 0xff, 0x00, 0x00, 0xff);
}
