#include <list>
#include <vector>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "scaledSprite.h"
#include "player.h"
#include "hud.h"
class Manager {
public:
  Manager ();
  ~Manager ();
  void play();


  //void switchSprite();
//void drawHUD(SDL_Surface*  screen,  int x,  int y);
private:
  const bool env;
  HUD hud;
  bool drawHud ;
  const IOManager& io;
  Clock& clock;
SDL_Surface *  screen;
  SDL_Surface * const scaledSpriteSurface;
   
  World world1;
  World world2;
  World world3;
  World world4;

  Viewport& viewport;
      std::vector<ScaledSprite*> scaledSprites;
    Player player;
  bool makeVideo;
  int frameCount;
  const std::string username;
  const std::string title;
  const int frameMax;

  void draw() ;
  void update();
  void makescaledSprites();
  void printscaledSprites() const;

  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void makeFrame();
};
