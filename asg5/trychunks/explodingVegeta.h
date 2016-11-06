#include <vector>
#include <list>
#include "chunkVegeta.h"

class ExplodingVegeta : public Vegeta {
public:
  ExplodingVegeta(const Vegeta& s);
  ~ExplodingVegeta();
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  void makeChunks(unsigned int);
  unsigned int chunkCount() const { return chunks.size(); }
  unsigned int freeCount()  const { return freeList.size(); }
private:
  std::list<ChunkVegeta> chunks; // An ExplodingVegeta is a list of Vegeta chunks
  std::list<ChunkVegeta> freeList; // When a chunk gets out of range it goes here
  std::vector<Frame*> frames; // Each chunk has a Frame
  ExplodingVegeta(const ExplodingVegeta&); // Explicit disallow (Item 6)
  ExplodingVegeta& operator=(const ExplodingVegeta&); // (Item 6)
};
