#include <iostream>
#include <iomanip>
#include "iomanager.h"
#include "ball.h"
#include <math.h>
#include "SDL/SDL_rotozoom.h"

Ball::Ball(const std::string& name):
io( IOManager::getInstance() ),
setColorKey(true),
screen(io.getScreen()),
image(io.loadAndSet(name,setColorKey)),
imagewidth(0),
imageheight(240),
textwidth(1),
textheight(1),
speed_per_tick(5),
INCR_X(0.3),
X_VELOCITY(300.0),
Width(854),
DT(17u),
printgoal(false),
angle(0)
{


}



Ball::~Ball(){


}

void Ball::draw() const { 
Uint16 w = image->w;

  Uint16 h = image->h;
  Sint16 xCoord = static_cast<Sint16>(imagewidth);
  Sint16 yCoord = static_cast<Sint16>(imageheight);
  SDL_Rect src = { 0, 0, w, h };
  SDL_Rect dest = {xCoord, yCoord, 0, 0 };
  /*SDL_Surface* rotatedimage=rotozoomSurface(image,angle,
    1.0,0);*/
  SDL_BlitSurface(image, &src, screen, &dest);
  //SDL_FreeSurface(rotatedimage);
  if(printgoal){
    // std::cout<<angle <<std::endl;
    io.printMessageAt("Goal",textwidth,textheight);
    SDL_Flip(screen);

  }
}




void Ball::freesurface(){
	
	SDL_FreeSurface(image);

}



bool Ball::update(){

  static unsigned int remainder = 0u; // ***
  static unsigned int currentTicks = 0u;
  static unsigned int count=0u;
  static unsigned int prevTicks = SDL_GetTicks();
  currentTicks = SDL_GetTicks();
  unsigned int elapsedTicks = currentTicks - prevTicks + remainder; // ***

  if( elapsedTicks > DT ) { 


  if(angle>=360){
    angle-=360;
  }
  else if(angle<360){
    angle+=360;
  }

  if(count>0 && imagewidth<=Width-image->w) {
    angle+=3;
    //float speed_per_tick = 5;
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
    
  
      return true;
  }
  else{
    if( textwidth<=457 && textheight<=240){
      //textheight +=5;
      //float incr = X_VELOCITY * DT * 0.001; // ***
  textwidth += 10;
    textheight+=5;
      //textwidth+=5;
      printgoal=true;
    }
    prevTicks = currentTicks;
      remainder = elapsedTicks - DT; 
   
    return true;
  }

  }




if((imagewidth>=0 && imagewidth<=352) && (imageheight>=240 && imageheight<=416) ){
angle+=3;
    // ***
      //float speed_per_tick = 5;
    float delta_x = 353 - imagewidth;
    float delta_y = 416 - imageheight;
    float goal_dist = sqrt( (delta_x * delta_x) + (delta_y * delta_y) );

    float ratio = speed_per_tick / goal_dist;
    float x_move = ratio * delta_x ; 
    float y_move = ratio * delta_y;
     imagewidth += x_move  ; 
   imageheight += y_move ;
   prevTicks = currentTicks;
      remainder = elapsedTicks - DT;  

  return true;
  }




  else if((imagewidth>=352 && imagewidth<=854) && (imageheight>=240 && imageheight<=418)){

    angle+=3;

    //float speed_per_tick = 5;
    float delta_x = 790 - imagewidth;
    float delta_y = 240 - imageheight;
    float goal_dist = sqrt( (delta_x * delta_x) + (delta_y * delta_y) );

    float ratio = speed_per_tick / goal_dist;
    float x_move = ratio * delta_x ; 
    float y_move = ratio * delta_y;
     imagewidth += x_move  ; 
     imageheight += y_move ;
     prevTicks = currentTicks;
      remainder = elapsedTicks - DT;  

    
  return true;
  }

  else if(imagewidth >=550 && imageheight<=Width-image->w){
    //float speed_per_tick = 5;
    float delta_x = 510 - imagewidth;
    float delta_y = 0 - imageheight;
    float goal_dist = sqrt( (delta_x * delta_x) + (delta_y * delta_y) );

    float ratio = speed_per_tick / goal_dist;
    float x_move = ratio * delta_x ; 
    float y_move = ratio * delta_y;
     imagewidth += x_move  ; 
     imageheight += y_move ;
     prevTicks = currentTicks;
      remainder = elapsedTicks - DT;  
     
  
  return true;
  }
  else if( imageheight<=480 && imagewidth<=Width-image->w){
    count++;
    //float speed_per_tick = 5;
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
    
 
  return true;
  }
   else{
       
    return false;

  }
       
	
}
else{
  return false;
}
}


  







