#include <cmath>
#include "bullet.h"
#include "gamedata.h"
#include "ioManager.h"
Bullet::Bullet(const string& n, const Vector2f& pos, const Vector2f& vel,const Frame* frm):Sprite(n, pos, vel,frm),startPos(pos),distance(0){ 
	startPos=getPosition();
}

Bullet::Bullet(const Bullet& s) :Sprite(s),startPos(s.startPos),distance(s.distance){ }
void Bullet::update(Uint32 ticks){
   Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
   setPosition(getPosition() + incr);
   distance+=(hypot(incr[0],incr[1]));
}
bool Bullet::goneFar(){
   return distance>Gamedata::getInstance().getXmlInt("bullet/range");
}
void Bullet::reset() {
   distance = 0;
}


