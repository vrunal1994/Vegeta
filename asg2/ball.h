#include <iostream>
#include "iomanager.h"
#include "generateFrames.h"

class Ball{
public:
Ball(const std::string& imagepath);
  ~Ball();
  bool update();
  void freesurface();
  void draw() const;

  bool getPrintGoal() const { return printgoal; }
  
private:
  const IOManager& io;
  bool setColorKey;
  SDL_Surface * const screen;
  SDL_Surface* image;
  float imagewidth;
  float imageheight;
  
  float textwidth;
  float textheight;
  float speed_per_tick;
  const float INCR_X;
  const float X_VELOCITY;
  const float Width;
  const unsigned int DT;
  
   bool printgoal;
   int angle;
  Ball(const Ball&);
  Ball& operator=(const Ball&);
};