#include <iostream>
#include "iomanager.h"

class Table{
public:
Table(const std::string& imagepath);
  ~Table();
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
  Table(const Table&);
  Table& operator=(const Table&);
};