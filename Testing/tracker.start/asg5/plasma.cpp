#include <cmath>
#include "plasma.h"
#include "gamedata.h"
#include "ioManager.h"
#include "frameFactory.h"

Plasma::Plasma(const std::string & str): 
name(str),
myVelocity(Gamedata::getInstance().getXmlInt(name+ "/speedX"), Gamedata::getInstance().getXmlInt(name+ "/speedY")),
plasmaFrame(FrameFactory::getInstance().getFrames(name)),
plasmaList()
{  }

Plasma ::Plasma (const Plasma& p):
name(p.name),
myVelocity(p.myVelocity),
plasmaFrame(p.plasmaFrame),
plasmaList(p.plasmaList)
{  }

void Plasma::shoot(const Vector2f& pos, const Vector2f& objVel)
{
    Sprite s(name, pos,objVel);
    plasmaList.push_back(s);
}

void Plasma::draw()const 
{std::list<Sprite>:: const_iterator itr = plasmaList.begin();
while(itr != plasmaList.end())
    {itr->draw();
    ++itr;
    }
    //std::cout<<"From Draw" <<std::endl;
}

void Plasma::update(Uint32 ticks)
{
std::list<Sprite>::iterator itr = plasmaList.begin();
while(itr != plasmaList.end())
{ itr->update(ticks);
  //if()
    ++itr;}

}

int Plasma::smartCheck(const Drawable* obj)
{
  std::list<Sprite>::const_iterator bitr = plasmaList.begin();
  while(bitr!=plasmaList.end()){
     Vector2f pos= bitr->getPosition();
     float localHeight = bitr->getFrame()->getHeight();
     float objHeight = obj->getFrame()->getWidth();
     if(obj->X()-pos[0] < 100)
     {
       if( pos[1]+localHeight > obj->Y() && 
           pos[1]+localHeight/2< obj->Y()+objHeight/2 ) 
       {
         return 2; //go down
       }
       else if( (pos[1]+localHeight/2 >= obj->Y()+objHeight/2 && 
           pos[1] < obj->Y()+objHeight )  )      
       {
         return 1; //go up
       }
     }
     ++bitr;
  }  
  return 0;
}

