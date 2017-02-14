#include <iostream>
#include <iomanip>
#include "iomanager.h"

using std::string;

IOManager& IOManager::getInstance() {
  static IOManager io;
  return io;
}

IOManager::IOManager( ) :
 
    viewWidth(854),
    viewHeight(480),
    MAX_STRING_SIZE(50),
   
    screen(SDL_SetVideoMode(viewWidth, viewHeight, 0, SDL_DOUBLEBUF)),
    font( NULL ), 
    color()
{
  if (screen == NULL) { 
    throw string("Unable to set video mode; screen is NULL in IOMAnager"); 
  }
  if ( TTF_Init() == -1 ) {
    throw string("TTF_Init failed: ") + TTF_GetError();
  }
  font = TTF_OpenFont(
         "font/dyslexic-bold.otf", 
         30
         );
  if ( !font ) {
    throw string("TTF_OpenFont failed: ") + TTF_GetError();
  }
  color.r = 0;
  color.g = 0;
  color.b = 0;
  color.unused = 0;
  SDL_EnableUNICODE( SDL_ENABLE );
  atexit(TTF_Quit);
}

SDL_Surface* IOManager::loadAndSet(const string& filename, bool setcolorkey) const {
  SDL_Surface *tmp = IMG_Load(filename.c_str());
  if (tmp == NULL) {
    throw string("Unable to load bitmap ")+filename;
  }
  if ( setcolorkey ) {
    Uint32 colorkey = SDL_MapRGB(tmp->format, 255, 255, 255);
    SDL_SetColorKey(tmp, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey);
  }
  // Optimize the strip for fast display
  SDL_Surface *image = SDL_DisplayFormatAlpha(tmp);
  if (image == NULL) {
    image = tmp;
  } 
  else {
    SDL_FreeSurface(tmp);
  }
  return image;
}

void IOManager::printMessageAt(const string& msg, Sint16 x, Sint16 y) const {
   Uint16 zero = 0;
   SDL_Rect dest = {x,y,zero,zero};
   SDL_Surface * stext = TTF_RenderText_Blended(font, msg.c_str(), color);
   if (stext) {
     SDL_BlitSurface( stext, NULL, screen, &dest );
     SDL_FreeSurface(stext);
   }
   else {
     throw 
     string("Couldn't allocate text sureface in printMessageAt");
   }
}




