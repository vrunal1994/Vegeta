#ifndef MULTISPRITE__H
#define MULTISPRITE__H
#include <string>
#include <vector>
#include "drawable.h"
class ExplodingSprite;
class MultiSprite : public Drawable {
public:
/*MultiSprite( const std::string& name, 
                          const std::vector<Frame*>& f,bool ply);*/
  MultiSprite(const std::string&, const std::vector<Frame*>&);
  virtual ~MultiSprite();

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
  virtual void explode();
  bool smart;
  bool IAmExploding()const;
protected:
 ExplodingSprite* explosion;
  const std::vector<Frame *> frames;
  int worldWidth;
  int worldHeight;
  bool player;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;
  //bool spinstarVertical;
  bool girlBoundHorizontal;
  void reset();
  void advanceFrame(Uint32 ticks);
  MultiSprite(const MultiSprite&);
  MultiSprite& operator=(const MultiSprite&);
};
#endif
