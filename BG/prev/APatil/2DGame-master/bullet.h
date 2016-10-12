#ifndef BULLET__H
#define BULLET__H
#include <string>
#include "sprite.h"

class Bullet : public Sprite {
public:
  Bullet(const std::string&, 
         const Vector2f& pos, const Vector2f& vel, const Frame*);
  Bullet(const std::string&, const Vector2f& pos, const Vector2f& vel);

  Bullet(const Bullet& s);
  virtual ~Bullet() { } 
  void reset();
bool goneFar();
  Bullet& operator=(const Bullet&);
  void update(Uint32);	
private:
  Vector2f startPos;
  float distance;
};
#endif
