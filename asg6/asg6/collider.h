#include <cmath>
#include "collisionStrategy.h"
#include "vegeta.h"
#include "flamethrower.h"
#include "chari.h"
#include "bullet.h"
#include "smallSprite.h"
class Collider{
  CollisionStrategy* strategy;
  Collider();
  ~Collider();
public:
  static Collider& getInstance();
  bool collidedWithVegeta(const flamethrower c,
  	const Vegeta* d) const ;
  bool collidedWithChari(const smallSprite s, const Charizard* z)const;
  
 
private:
  Collider(const Collider&);
  Collider operator=(const Collider&); 
};



