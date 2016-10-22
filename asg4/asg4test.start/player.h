//#ifndef PLAYER__H
//#define PLAYER__H
#include <string>
#include <vector>
#include <list>
#include "drawable.h"
//#include "bullet.h"
//#include "extractSurface.h"

class Player : public Drawable {
 public:
  Player( const std::string& name, const std::vector<Frame*>& f);
  void toggleLeft();
  void toggleRight();
  void toggleUp();
  void toggleDown();
  void draw() const;
  
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
  virtual ~Player();
  void update(Uint32);
  bool turn; 
  
  friend class Manager;
  void advanceFrame(Uint32 ticks);
  void IdleState(Uint32 ticks);
  
  private:
  Player(const Player&);
  Player operator=(const Player&);
  
  const std::vector<Frame *> frames;
  float timeSinceLastFrame;
  bool left;
  bool right;
  bool up;
  bool down;
  bool idle;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  
};
