// Brian Malloy        March, 2014

#include <cmath>  // for sqrtf
#include <iostream>
#include "ioManager.h"
#include "aaline.h"

IOManager *IOManager::instance = NULL;

void drawBackground(SDL_Surface* screen) {
  SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255) );
  SDL_Rect dest = {0, 0, 0, 0};
  SDL_BlitSurface( screen, NULL, screen, &dest );
}

void play() {
  SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center"));
  IOManager* io = IOManager::getInstance();
  SDL_Surface * const screen = io->getScreen();
  const Uint32 BLUE = SDL_MapRGB(screen->format, 0x00, 0x00, 0xcd);
  const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
  atexit(SDL_Quit);

  SDL_Event event;
  bool done = false;
  while ( not done ) {
     drawBackground(screen);
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
     // ****************** Draw Horizontal ****************************
     Sint16 y1 = 20;
     io->printMessageCenteredAt("AALine Test", y1);

     y1 += 40;
     Sint16 x1 = 400, x2 = 500;
     io->printStringAfterMessage("1. Horizontal, red, def px thick", 40,y1);
     Draw_AALine(screen, x1,y1, x2,y1, RED);

     y1 += 30;
     io->printStringAfterMessage("2. Horizontal, red, 1.0 px thick", 40, y1);
     Draw_AALine(screen, x1,y1, x2,y1, 8.0f, 0, 0,0, 20);

     y1 += 30;
     io->printStringAfterMessage("3. Horizontal, red, 10.0 px thick", 40, y1);
     Draw_AALine(screen, x1,y1, x2,y1, 10.0f, RED);


     // **************** Vertical and Slant **************************
     Sint16 y2 = 90;
     x1 = 350, y1 = 320, y2 = y1-100;
     io->printStringAfterMessage("4. Vertical, red, def thick", 40, y1);
     Draw_AALine(screen, x1,y1, x1,y2, RED);

     x1 += 40;
     y2 = y1 += 30;
     io->printStringAfterMessage("5. Vertical, red, 1.0 thick", 40, y1);
     Draw_AALine(screen, x1,y1, x1,y1-100, 1.0, RED);

     x1 += 40;
     y2 = y1 += 30;
     io->printStringAfterMessage("6. Vertical, blue, 2.0 thick", 40, y1);
     Draw_AALine(screen, x1,y1, x1,y1-100, 2.0, BLUE);

     x1 += 40;
     y2 = y1 += 30;
     io->printStringAfterMessage("7. Vertical, blue, 10.0 thick", 40, y1);
     Draw_AALine(screen, x1,y1, x1,y1-100, 10.0, BLUE);

     x2 = x1 += 40;
     x2 += 40;
     y2 = y1 += 30;
     io->printStringAfterMessage("8. Slant, blue, 3.0 thick (note antialias)", 40, y1);
     Draw_AALine(screen, x1,y1, x2,y1-100, 3.0, BLUE);

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
