#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <deque>
#include <numeric>
#include <vector>
#include "clock.h"
#include "gamedata.h"
#include "ioManager.h"

Clock& Clock::getInstance() {
  if ( SDL_WasInit(SDL_INIT_VIDEO) == 0) {
    throw std::string("Must init SDL before Clock");
  }
  static Clock clock; 
  return clock;
}

Clock::Clock() :
  started(false), 
  paused(false), 
  sloMo(false), 
  framesAreCapped(Gamedata::getInstance().getXmlBool("framesAreCapped")), 
  frameCap(Gamedata::getInstance().getXmlInt("frameCap")), 
  frames(0), 
  tickSum(0),
  sumOfAllTicks(0),
  timeAtStart(0), timeAtPause(0),
  currTicks(0), prevTicks(0), ticks(0) 
  {
  start();
}

Clock::Clock(const Clock& c) :
  started(c.started), 
  paused(c.paused), 
  sloMo(c.sloMo), 
  framesAreCapped(c.framesAreCapped), 
  frameCap(c.frameCap), 
  frames(c.frames),
  tickSum(c.tickSum),
  sumOfAllTicks(c.sumOfAllTicks),
  timeAtStart(c.timeAtStart), timeAtPause(c.timeAtPause),
  currTicks(c.currTicks), prevTicks(c.prevTicks), ticks(c.ticks) 
  {
  start();
}

void Clock::display() const { 
  static unsigned int lastFrames = 0;
  static unsigned int oldFrames = 0;
  static unsigned int seconds = getSeconds();

  if ( getSeconds() > seconds ) {
    seconds = getSeconds();
    lastFrames = frames - oldFrames;
    oldFrames = frames;
  }
  unsigned int framecount=200;
  std::deque<unsigned int> capturefps;
  capturefps.reserve(framecount);
  if(capturefps.size()<framecount)
  {
    for (unsigned int i = 0; i < capturefps.size(); ++i)
    {
      /* code */
      capturefps.push_back(lastFrames);
    }
  }
  else if(capturefps.size()>framecount)
  {
    capturefps.pop_front();
    capturefps.push_back(lastFrames);
  }
  IOManager::getInstance().
    printMessageValueAt("fps: ", getFps(), 10, 10);
  IOManager::getInstance()
    .printMessageValueAt("seconds: ", seconds, 10, 30);
  IOManager::getInstance()
    .printMessageValueAt("frames in sec: ", lastFrames, 10, 70);
IOManager::getInstance()
    .printMessageValueAt("framesnew in sec: ", std::accumulate(capturefps.begin(), capturefps.end(), 0.0) / 
    capturefps.size(), 10, 90);
    
}

void Clock::toggleSloMo() {
  if( started && !sloMo ) {
    timeAtPause = SDL_GetTicks() - timeAtStart;
    sloMo = true;
  }
  else if ( started && sloMo ) {
    timeAtStart = SDL_GetTicks() - timeAtPause;
    sloMo = false;
  }
}

int Clock::getFps() const { 
  if ( getSeconds() > 0 && frames > 0) return frames/getSeconds();  
  return 0;
}


unsigned int Clock::getTicks() const { 
  if (paused) return timeAtPause;
  else if ( sloMo ) return 1;
  else return SDL_GetTicks() - timeAtStart; 
}

unsigned int Clock::getElapsedTicks() { 
  if (paused) return 0;
  else if ( sloMo ) return 1;

  currTicks = getTicks();
  ticks = currTicks-prevTicks;
  unsigned int delay = capFrameRate();
  prevTicks = currTicks + delay;
  ticks += delay;
  sumOfAllTicks += ticks;
  return ticks;
}

unsigned int Clock::capFrameRate() const { 
  if ( !framesAreCapped ) return 0u;
  unsigned int delay = std::max(0.0,1000.0/frameCap+0.5 - ticks);
  SDL_Delay( delay );
  return delay;
}
void Clock::update() { 
  if ( paused ) return;
  ++frames;
  
  

}



void Clock::start() { 
  started = true; 
  paused = false; 
  frames = 0;
  timeAtPause = timeAtStart = SDL_GetTicks(); 
}
void Clock::pause() {
  if( started && !paused ) {
    timeAtPause = SDL_GetTicks() - timeAtStart;
    paused = true;
  }
}
void Clock::unpause() {
  if( started && paused ) {
    timeAtStart = SDL_GetTicks() - timeAtPause;
    paused = false;
  }
}

