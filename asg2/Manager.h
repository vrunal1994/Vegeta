#include <iostream>
#include <SDL.h>
#include "iomanager.h"
#include "table.h"
#include "ball.h"




class Manager{
public:
	Manager();
	~Manager();
	void play();

private:
	const bool env;
	const IOManager& io;
	SDL_Surface* const screen;
	Table table;
	Ball ball;
	
	bool makeVideo;
	GenerateFrames genframes;
	
	void draw() const;
	void update();
	Manager(const Manager&);
  	Manager& operator=(const Manager&);

};
