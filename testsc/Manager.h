#include <iostream>
#include <SDL.h>
#include "iomanager.h"
#include "ground.h"
#include "football.h"
#include "goalpost.h"



class Manager{
public:
	Manager();
	~Manager();
	void play();

private:
	const bool env;
	const IOManager& io;
	SDL_Surface* const screen;
	Ground ground;
	Football fball;
	bool makeVideo;
	GenerateFrames genframes;
	//Goalpost gpost;
	void draw() const;
	void update();
	Manager(const Manager&);
  	Manager& operator=(const Manager&);

};
