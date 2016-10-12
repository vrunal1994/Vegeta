#include <list>
#include <vector>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "scaledSprite.h"
#include "collider.h"
#include "hud.h"
#include "sound.h"
class Manager {
public:
  Manager ();
  ~Manager ();
  void play();
  void switchSprite();
  int getRandom();
  Collider& cld;
  bool resetvar;
  void toggleToGod();
private:
  bool Godmode;
  const bool env;
  const Gamedata& gdata;
  const IOManager& io;
  Clock& clock;
  bool HudShow;
  SDL_Surface * const screen;
  SDL_Surface * const orbSurface;
  World world;
  World world1;
  World world2;
  World world3;
  World world4;
  World world5;
  bool start;
  Player* player;
  Hud* hud1;
  Hud* hud2;
  Viewport& viewport;
  std::vector<SDL_Surface*> surfaces;
  std::vector<ScaledSprite*> orbs;
  std::list<Drawable*> sprites;
  std::list<Drawable*>::iterator currentSprite;
  void checkForCollisions();
  bool makeVideo;
  int frameCount;
  const std::string username;
  const std::string title;
  const int frameMax;
  const int maxCount;
  void draw() const;
  void safeDistance();
  void update();
  void makeOrbs();
  void printOrbs() const;
  void smartingit();
  float safedistance;
  bool reduc;
  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void makeFrame();
};
