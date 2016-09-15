#include <iostream>
#include "iomanager.h"
#include "generateFrames.h"

class Football{
public:
Football(const std::string& imagepath);
  ~Football();
  bool update();
  void freesurface();
  void draw() const;
  void draw1() const;
  bool update1();
private:
  const IOManager& io;
  bool setColorKey;
  SDL_Surface * const screen;
  SDL_Surface* image;
  float imagewidth;
  float imageheight;
  float imagewidth1;
  float imageheight1;
  const float INCR_X;
  const float X_VELOCITY;
  const float Width;
  const unsigned int DT;
  bool makeVideo;

  GenerateFrames genframes;
   bool printgoal;
  Football(const Football&);
  Football& operator=(const Football&);
};