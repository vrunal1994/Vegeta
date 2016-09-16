#include <iostream>
#include <iomanip>
#include "iomanager.h"
#include "football.h"
#include <math.h>



Football::Football(const std::string& name):
io( IOManager::getInstance() ),
setColorKey(true),
screen(io.getScreen()),
image(io.loadAndSet(name,setColorKey)),
imagewidth(0),
imageheight(240),
imagewidth1(825),
imageheight1(240),
INCR_X(0.3),
X_VELOCITY(300.0),
Width(854),
DT(17u),
makeVideo(false),
genframes(screen),
printgoal(false)
{


}



Football::~Football(){


}

void Football::draw() const { 
Uint16 w = image->w;

  Uint16 h = image->h;
  Sint16 xCoord = static_cast<Sint16>(imagewidth);
  Sint16 yCoord = static_cast<Sint16>(imageheight);
  SDL_Rect src = { 0, 0, w, h };
  SDL_Rect dest = {xCoord, yCoord, 0, 0 };

  SDL_BlitSurface(image, &src, screen, &dest);

  if(printgoal){
    io.printMessageCenteredAt("Goal",240);
    SDL_Flip(screen);

  }
}

void Football::draw1() const { 
Uint16 w = image->w;

  Uint16 h = image->h;
  Sint16 xCoord = static_cast<Sint16>(imagewidth1);
  Sint16 yCoord = static_cast<Sint16>(imageheight1);
  SDL_Rect src = { 0, 0, w, h };
  SDL_Rect dest = {xCoord, yCoord, 0, 0 };

  SDL_BlitSurface(image, &src, screen, &dest);

  if(printgoal){
    io.printMessageCenteredAt("Goal",240);
    SDL_Flip(screen);

  }
}

void Football::freesurface(){
	
	SDL_FreeSurface(image);
}

bool Football::update(){

static unsigned int remainder = 0u; // ***
  static unsigned int currentTicks = 0u;
  static unsigned int count=0u;
  static unsigned int prevTicks = SDL_GetTicks();
  currentTicks = SDL_GetTicks();
  unsigned int elapsedTicks = currentTicks - prevTicks + remainder; // ***

  if( elapsedTicks > DT ) { 


    
	/*if(imagewidth<=350 && 430<=Width-image->w ){

		// ***

  float incr = X_VELOCITY * DT * 0.001; // ***
  //std::cout<<incr <<std::endl;
  imagewidth += incr;
  float yincr=X_VELOCITY*DT*0.001*0.5;
  imageheight +=yincr;
  std::cout<<imagewidth<<std::endl;
  std::cout<<imageheight<<std::endl;
  prevTicks = currentTicks;
  remainder = elapsedTicks - DT;
  
  return true;
	}	*/

  if(count>0 && imagewidth<=Width-image->w) {
    float speed_per_tick = 5;
float delta_x = 0 - imagewidth;
float delta_y =455 - imageheight;
float goal_dist = sqrt( (delta_x * delta_x) + (delta_y * delta_y) );

    float ratio = speed_per_tick / goal_dist;
    float x_move = ratio * delta_x ; 
    float y_move = ratio * delta_y;
    if(imagewidth>=40){
     imagewidth += x_move  ; 
    
   imageheight += y_move ;
   prevTicks = currentTicks;
  remainder = elapsedTicks - DT;
  /*std::cout<< "in fifth"<<std::endl;
  std::cout<<imagewidth<<std::endl;
  std::cout<<imageheight<<std::endl;*/
  return true;
  }
  else{
    printgoal=true;
    return false;
  }

  }


if((imagewidth>=0 && imagewidth<=352) && (imageheight>=240 && imageheight<=416) ){

    // ***
  float speed_per_tick = 5;
float delta_x = 353 - imagewidth;
float delta_y = 416 - imageheight;
float goal_dist = sqrt( (delta_x * delta_x) + (delta_y * delta_y) );

    float ratio = speed_per_tick / goal_dist;
    float x_move = ratio * delta_x ; 
    float y_move = ratio * delta_y;
     imagewidth += x_move  ; 
   imageheight += y_move ;




  /*float spriteToDest = atan2(240-416,0-352);
   float spriteToDestAngle=spriteToDest*180/3.14;
   float incr = cos(spriteToDestAngle) * 100;
   float yincr=sin(spriteToDestAngle)*100;
  
 // float incr = X_VELOCITY * DT * 0.001; // ***
  //std::cout<<incr <<std::endl;
  imagewidth += incr;
  //float yincr=X_VELOCITY*DT*0.001*0.5;
  imageheight +=yincr;*/
  /*std::cout<<"In one"<<std::endl;
  std::cout<<imagewidth<<std::endl;
  std::cout<<imageheight<<std::endl;*/
  prevTicks = currentTicks;
  remainder = elapsedTicks - DT;
  
  return true;
  }


/*  else if(imagewidth<=Width-image->w-40 && imageheight>=240){
  //std::cout<<imagewidth<<std::endl;
//std::cout<<imageheight<<std::endl;
   float spriteToDest = atan2(416-240,352-840);
   float spriteToDestAngle=spriteToDest*180/3.14;
   std::cout<<spriteToDestAngle<<std::endl;
   std::cout<<cos(spriteToDestAngle)<<std::endl;
  float incr =250.0 * DT * 0.001; // ***
  //std::cout<<incr <<std::endl;
  imagewidth += incr;
  float yincr=-250.0*DT*0.001*0.9;
  imageheight +=yincr;
  prevTicks = currentTicks;
  remainder = elapsedTicks - DT;

  float incr = cos(spriteToDestAngle) * 100; // ***
  //std::cout<<incr <<std::endl;
  imagewidth += incr;
  float yincr=sin(spriteToDestAngle)*100;
  imageheight +=yincr;
  prevTicks = currentTicks;
  remainder = elapsedTicks - DT;



    
  return true;
  }*/

  else if((imagewidth>=352 && imagewidth<=854) && (imageheight>=240 && imageheight<=418)){



    float speed_per_tick = 5;
float delta_x = 854 - imagewidth;
float delta_y = 240 - imageheight;
float goal_dist = sqrt( (delta_x * delta_x) + (delta_y * delta_y) );

    float ratio = speed_per_tick / goal_dist;
    float x_move = ratio * delta_x ; 
    float y_move = ratio * delta_y;
     imagewidth += x_move  ; 
   imageheight += y_move ;

   /*float  x=352-854;
   float y= 240-416;
    float dist = sqrt(x*x + y*y);
    float yVel = (100 * x / dist) ; 
float xVel = (100 * y / dist) ;
    float spriteToDest = atan2(416-240,352-854);
   float spriteToDestAngle=(spriteToDest)*(180/3.14);
   float incr = cos(spriteToDestAngle) * 100 *DT; // ***
  //std::cout<<incr <<std::endl;
  imagewidth += xVel;
  float yincr=sin(spriteToDestAngle)*100 *DT;
  imageheight+=yVel;*/
  prevTicks = currentTicks;
  remainder = elapsedTicks - DT;
  /*std::cout<< "in second"<<std::endl;
  std::cout<<imagewidth<<std::endl;
  std::cout<<imageheight<<std::endl;*/



    
  return true;
  }

  else if(imagewidth >=457 && imageheight<=Width-image->w){
    float speed_per_tick = 5;
float delta_x = 457 - imagewidth;
float delta_y = 0 - imageheight;
float goal_dist = sqrt( (delta_x * delta_x) + (delta_y * delta_y) );

    float ratio = speed_per_tick / goal_dist;
    float x_move = ratio * delta_x ; 
    float y_move = ratio * delta_y;
     imagewidth += x_move  ; 
   imageheight += y_move ;
   prevTicks = currentTicks;
  remainder = elapsedTicks - DT;
  /*std::cout<< "in third"<<std::endl;
  std::cout<<imagewidth<<std::endl;
  std::cout<<imageheight<<std::endl;*/
  return true;
  }
  else if( imageheight<=480 && imagewidth<=Width-image->w){
    count++;
    float speed_per_tick = 5;
float delta_x = 0 - imagewidth;
float delta_y =480 - imageheight;
float goal_dist = sqrt( (delta_x * delta_x) + (delta_y * delta_y) );

    float ratio = speed_per_tick / goal_dist;
    float x_move = ratio * delta_x ; 
    float y_move = ratio * delta_y;
     imagewidth += x_move  ; 
   imageheight += y_move ;
   prevTicks = currentTicks;
  remainder = elapsedTicks - DT;
 /* std::cout<< "in fourth"<<std::endl;
  std::cout<<imagewidth<<std::endl;
  std::cout<<imageheight<<std::endl;*/
  return true;
  }
   else{
   
    //printgoal=true;
    return false;
    //makeVideo=false;
    
    
  }
   // return true;
  
  /*if(makeVideo){
    genframes.makeFrame();
  }*/
	
}
else{
  return false;
}
}

bool Football::update1(){

static unsigned int remainder = 0u; // ***
  static unsigned int currentTicks = 0u;
  static unsigned int prevTicks = SDL_GetTicks();
  currentTicks = SDL_GetTicks();
  unsigned int elapsedTicks = currentTicks - prevTicks + remainder; // ***

  if( elapsedTicks > DT ) { 



  if(imagewidth1<=460 && 630<=Width-image->w ){

    // ***

  float incr = X_VELOCITY * DT * 0.001; // ***
  //std::cout<<incr <<std::endl;
  imagewidth1 -= incr;
  float yincr=X_VELOCITY*DT*0.001*0.5;
  imageheight1 +=yincr;

  prevTicks = currentTicks;
  remainder = elapsedTicks - DT;
  
  return true;
  } 

  else if(imagewidth1<=Width-image->w-40){
  //std::cout<<imagewidth<<std::endl;
//std::cout<<imageheight<<std::endl;
  float incr = 250.0 * DT * 0.001; // ***
  //std::cout<<incr <<std::endl;
  imagewidth1 += incr;
  float yincr=-250.0*DT*0.001*0.9;
  imageheight1 +=yincr;
  prevTicks = currentTicks;
  remainder = elapsedTicks - DT;

    
  return true;
  }
 // return true;
  else {
    printgoal=true;
    return false;
    //makeVideo=false;
    
    
  }
  if(makeVideo){
    genframes.makeFrame();
  }
  
}
else{
  return false;
}

//return false;




}
