#include <vector>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "HUD.h"
#include "player.h"
#include "scaledSprite.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();
  void switchSprite();

private:
  const bool env;
  const IOManager& io;
  Clock& clock;
  HUD hud;
  bool drawHud;
  SDL_Surface * const screen;
  SDL_Surface * const orbSurface;
  std::vector<ScaledSprite*> orbs;
  World world;
  World mid;
  World last;
  Viewport& viewport;
  std::vector<Drawable*> sprites;
  std::vector<Player* > player;
  int currentSprite;

  bool makeVideo;
  int frameCount;
  const std::string username;
  const std::string title;
  const int frameMax;

  void draw() const;
  void update();
  void makeOrbs();
  void printOrbs() const;

  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void makeFrame();
};
