// Brian Malloy        March, 2014

#include <iostream>
#include "ioManager.h"
#include "aaline.h"
const int HUD_WIDTH = 200;
const int HUD_HEIGHT = 100;

IOManager *IOManager::instance = NULL;

void drawBackground(SDL_Surface* screen) {
  const Uint32 BLUE = SDL_MapRGB(screen->format, 0x00, 0x00, 0xcd);
  SDL_FillRect( screen, NULL, BLUE);
  SDL_Rect dest = {0, 0, 0, 0};
  SDL_BlitSurface( screen, NULL, screen, &dest );
}

void play() {
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
     io->printMessageCenteredAt("Construction of a Heads Up Display", 10);
     SDL_Flip(screen);
  }
  delete io;
}

int main() {
   try {
      play();
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
