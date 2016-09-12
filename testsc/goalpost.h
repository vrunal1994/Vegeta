#include <iostream>
#include "iomanager.h"

class Goalpost{
public:
Goalpost(const std::string& imagepath);
  ~Goalpost();
  void update();
  void freesurface();
  void draw() const;
private:
  const IOManager& io;
  bool setColorKey;
  SDL_Surface * const screen;
  SDL_Surface* image;
  float imagewidth;
  float imageheight;
  Goalpost(const Goalpost&);
  Goalpost& operator=(const Goalpost&);
};