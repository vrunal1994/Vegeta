//#ifndef PLAYER__H
//#define PLAYER__H
#include <string>
#include <vector>
#include <list>
#include "drawable.h"
#include "bullet.h"
//#include "extractSurface.h"
class ExplodingSprite;
class Player : public Drawable {
 public:
  Player( const std::string& name, const std::vector<Frame*>& f);
  void toggleLeft();
  void toggleRight();
  void toggleUp();
  void toggleDown();
  void draw() const;
  void shoot(const std::string& name,const Vector2f& pos,const Vector2f& vel,const Frame* frm);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
  virtual ~Player();
  void update(Uint32);
  bool turn; 
  bool shot;
  bool goneFar;
  int getHealth()const{return health;}
  void setHealth(int h){health=h;}
  friend class Manager;
  void advanceFrame(Uint32 ticks);
  virtual void explode();
  bool win;
  bool lost;
  private:
  Player(const Player&);
  Player operator=(const Player&);
  ExplodingSprite* explosion;
  const std::vector<Frame *> frames;
  float timeSinceLastFrame;
  bool left;
  bool right;
  bool up;
  bool down;
  int health;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  std::list<Bullet>bulletList;
  std::list<Bullet>freeList;
};
