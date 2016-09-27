#include<iostream>
#include <SDL.h>
#include "ioManager.h"
#include <string>
class Hud{
public:
  Hud(const std::string& hudname); 
  const IOManager& io;
  void drawHUD(SDL_Surface*)const;
  void drawHUDdynamic(SDL_Surface* screen,int helt)const;
private:
  string name;
  const int HudStartX;
  const int HudStartY;
  const int HUD_WIDTH;
  const int HUD_HEIGHT;
};
