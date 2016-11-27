#include <vector>
#include <list>
#include "chunk.h"

class ExplodingAI : public Sprite {
public:
  ExplodingAI(const Sprite* s);
  ~ExplodingAI();
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  void makeChunks(unsigned int);
  bool done() { return chunks.empty(); }
  unsigned int chunkCount() const { return chunks.size(); }
  unsigned int freeCount()  const { return freeList.size(); }
private:
  std::list<Chunk> chunks; // An ExplodingAI is a list of sprite chunks
  std::list<Chunk> freeList; // When a chunk gets out of range it goes here
  std::vector<Frame*> frames; // Each chunk has a Frame
  ExplodingAI(const ExplodingAI&); // Explicit disallow (Item 6)
  ExplodingAI& operator=(const ExplodingAI&); // (Item 6)
};
