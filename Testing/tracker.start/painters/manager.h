#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>

#include "ioManager.h"
#include "clock.h"
#include "gamedata.h"
#include "scaledSprite.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();

private:
  const bool env;
  const Gamedata& gdata;
  const IOManager& io;
  Clock& clock;

  SDL_Surface *screen;
  SDL_Surface * const orbSurface;
  SDL_Surface * const backSurface;
  Frame backFrame;
  // The vector must be pointers to ScaledSprite because there
  // is no SDL function to copy a Surface, probably because it
  // would be an expensive operation. Thus, due to the value 
  // semantics of STL containers, we use pointers:
  std::vector<ScaledSprite*> orbs;

  void draw() const;
  void update();
  void makeOrbs();
  void printOrbs() const;
  Manager(const Manager&);
  Manager& operator=(const Manager&);
};
