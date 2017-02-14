#include <vector>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "hud.h"
#include "charizard.h"
#include "scaledSprite.h"
#include "vegeta.h"
#include <list>

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();
  void switchSprite();

private:
  const bool env;
  HUD hud;
  bool drawHud ;
  const IOManager& io;
  Clock& clock;

  SDL_Surface * const screen;
  SDL_Surface * const scaledSpriteSurface;
  World world;
  World mountains;

  Viewport& viewport;
  std::vector<ScaledSprite*> scaledSprites;
  Player* player;
  
  std::list<Drawable*> sprites;
  std::vector<Vegeta* > vegeta;
  std::list<Drawable*>::iterator currentSprite;
  

  bool makeVideo;
  int frameCount;
  const std::string username;
  const std::string title;
  const int frameMax;

  void draw() const;
  void update();
  void makescaledSprites();
  void printscaledSprites() const;

  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void makeFrame();
};
