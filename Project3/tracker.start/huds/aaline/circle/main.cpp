// Brian Malloy, Data-driven, Object Oriented 2D Game Development

#include <cmath>  // for sqrtf
#include <iostream>
#include "ioManager.h"
#include "aaline.h"

const int NO_OF_POINTS = 360;
#ifndef PI
#define PI 3.1415926535897
#endif

#define RAD2DEG (180/PI)
#define DEG2RAD (PI/180)

#define DegToRad(x) ((x)*DEG2RAD)
#define RadToDeg(x) ((x)*RAD2DEG)

IOManager *IOManager::instance = NULL;

void drawBackground(SDL_Surface* screen) {
  SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255) );
  SDL_Rect dest = {0, 0, 0, 0};
  SDL_BlitSurface( screen, NULL, screen, &dest );
}

void drawCircle(SDL_Surface* screen) {
  const Uint32 BLUE = SDL_MapRGB(screen->format, 0x00, 0x00, 0xcd);
  IOManager::getInstance()->
    printMessageCenteredAt("Using aaline to draw a Circle",20);
  Sint16 x = 320;
  Sint16 y = 240;
  Draw_Pixel(screen, x, y, 0,0,0, 255);
  Sint16 radius = 50;
  Draw_AALine(screen, x+5,y, x+100,y, BLUE);

  int step = 360/NO_OF_POINTS;
  for (int theta = 0; theta < 360; theta += step) {
    Draw_Pixel(screen, x + radius * cos(DegToRad(theta)), 
               y + radius * sin(DegToRad(theta)), 0xff, 0, 0,255);
  }
}

void playGame() {
  SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center"));
  IOManager* io = IOManager::getInstance();
  SDL_Surface * const screen = io->getScreen();
  atexit(SDL_Quit);

  SDL_Event event;
  bool done = false;
  while ( not done ) {
    Uint8 *keystate = SDL_GetKeyState(NULL);
    if ( SDL_PollEvent(&event) )
    switch (event.type) {
      case SDL_QUIT: {
        done = true;
        break;
      }
      case SDL_KEYDOWN: {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
          break;
        }
      }
    }
    drawBackground(screen);
    drawCircle(screen);
    SDL_Flip(screen);
  }
  delete io;
}

int main() {
  try {
    playGame();
  }
  catch (const string& msg) { std::cout << msg << std::endl; }
  catch (...) {
    std::cout << "Oops, someone threw an exception!" << std::endl;
  }
  return 0;
}
