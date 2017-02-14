#ifndef PLASMA__H
#define PLASMA__H
#include <string>
#include <list>
#include <vector>
#include "sprite.h"

class Plasma  {
public:
 Plasma(const std::string &);
 Plasma(const Plasma&);
 ~Plasma(){};
 void draw()const;
 void shoot(const Vector2f& pos, const Vector2f& objVel);
 void update(Uint32 ticks);
 bool goneFar();
 //bool shoot()const {return plasmaList.empty();}
 int smartCheck(const Drawable* obj);

 private:
 std::string name;
 Vector2f myVelocity;
 std::vector<Frame*> plasmaFrame;
 std::list<Sprite> plasmaList;
 float distance;

};
#endif
