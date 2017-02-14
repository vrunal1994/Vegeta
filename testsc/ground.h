#include <iostream>
#include "iomanager.h"

class Ground{
public:
Ground(const std::string& imagepath);
  ~Ground();
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
  Ground(const Ground&);
  Ground& operator=(const Ground&);
};