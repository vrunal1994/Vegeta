#ifndef CHUNKVEGETA__H
#define CHUNKVEGETA__H

#include <iostream>
#include "vegeta.h"
#include "gamedata.h"

class ChunkVegeta : public Vegeta {
public:
  explicit ChunkVegeta(
    const Vector2f& pos, const Vector2f vel, 
    const string& name, const Frame* fm) :
    Vegeta(name, pos, vel, fm), 
    distance(0), 
    maxDistance(Gamedata::getInstance().getXmlInt(name+"/distance")), 
    tooFar(false) 
  { }
  virtual void update(Uint32 ticks);
  bool goneTooFar() const { return tooFar; }
  void reset() {
    tooFar = false;
    distance = 0;
  }
private:
  float distance;
  float maxDistance;
  bool tooFar;
};
#endif
