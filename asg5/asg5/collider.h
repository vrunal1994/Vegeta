#include <cmath>
#include "collisionStrategy.h"
#include "vegeta.h"
#include "flamethrower.h"
class Collider{
  CollisionStrategy* strategy;
  Collider();
  ~Collider();
public:
  static Collider& getInstance();
  bool collidedWithVegeta(const flamethrower c,
  	const Vegeta* d) const ;
 
private:
  Collider(const Collider&);
  Collider operator=(const Collider&); 
};



