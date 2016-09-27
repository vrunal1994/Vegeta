#include <cmath>
#include "collisionStrategy.h"
#include "player.h"
class Collider{
  CollisionStrategy* strategy;
  Collider();
  ~Collider();
public:
  static Collider& getInstance();
  bool collidedWith(const Bullet c,const Drawable* d) const ;
  bool collidedWithPlayer(const Player* c,const Drawable* d) const ;
private:
  Collider(const Collider&);
  Collider operator=(const Collider&); 
};



