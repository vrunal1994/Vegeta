#ifndef PUBLIC_H
#define PUBLIC_H
#include <vector>
#include <list>
#include "drawable.h"
 
class Plasma
{
    public:
        Plasma(const std::string&);
        Plasma(const Plasma&);
        ~Plasma(){};
        void draw() const;
        void update(Uint32 ticks);
        void shoot(const Vector2f& pos, const Vector2f velocity);
    private:
        std::string name;
        Vector2f myVelocity;
        std::vector<Frame*> bulletFrames;
        //std::list<smallSprite> bulletList

};

#endif