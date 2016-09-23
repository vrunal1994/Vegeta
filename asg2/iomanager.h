#ifndef SINGLE__H
#define SINGLE__H
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include <sstream>
using std::string;


class IOManager {
public:
  static IOManager& getInstance();
  SDL_Surface * getScreen() const { return screen; }
  ~IOManager() { 
    TTF_CloseFont(font);
  }
  SDL_Surface* loadAndSet(const string& filename, bool setcolorkey) const;

  void printMessageAt(const string& msg, Sint16 x, Sint16 y) const;
  
private:
  IOManager();
  IOManager(const IOManager&);
  IOManager& operator=(const IOManager&);
  
  int viewWidth;
  int viewHeight;
  const unsigned MAX_STRING_SIZE;
  SDL_Surface * screen;
  TTF_Font *font;
  SDL_Color color;
  
};
#endif
