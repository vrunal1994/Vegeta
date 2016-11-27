#include <iostream>
#include <string>
#include <iomanip>
#include "multisprite.h"
#include "sprite.h"
#include "smartSprite.h"
#include "gamedata.h"
#include "manager.h"
#include "twoWayMultiSprite.h"
#include <algorithm>
#include "frameFactory.h"
#include "bullet.h"
#include "smallSprite.h"
#include "explodingAI.h"

Manager::~Manager() { 
  // These deletions eliminate "definitely lost" and
  // "still reachable"s in Valgrind.
  /*std::vector<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    delete (*ptr);
    ++ptr;
  }*/
  for (unsigned i = 0; i < sprites.size(); ++i) {
    delete sprites[i];
  }
     /*for(unsigned i = 0; i< vegeta.size(); ++i)
  {delete vegeta[i];}
 for(unsigned i = 0; i< charizard.size(); ++i)
  {delete charizard[i];}*/

 /*for (unsigned i = 0; i < scaledSprites.size(); ++i) {
    delete scaledSprites[i];
  }
  scaledSprites.clear();*/
  SDL_FreeSurface(scaledSpriteSurface);
  delete hudcontrols;
  delete hudhealthvegeta;
  delete hudhealthcharizard;
  if(resetvar){
Manager mang;
mang.play();
}
  
}

class ScaledSpriteCompare {
public:
  bool operator()(const ScaledSprite* lhs, const ScaledSprite* rhs) {
    return lhs->getScale() < rhs->getScale();
  }
};

Manager::Manager() :
cld(Collider::getInstance()),
resetvar(false),
  vegetaGodMode(false),
  charizardGodMode(false),
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  hudcontrols(new HUD("HUD")),
  hudhealthvegeta(new HUD("HealthVegeta")),
  hudhealthcharizard(new HUD("HealthChari")),
  // bar(),
  drawHud(false),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
   scaledSpriteSurface( io.loadAndSet(Gamedata::getInstance().getXmlStr("dragonball/file"), 
              Gamedata::getInstance().getXmlBool("dragonball/transparency")) ),
  world("mountains", Gamedata::getInstance().getXmlInt("mountains/factor") ),
last("cloud", Gamedata::getInstance().getXmlInt("cloud/factor")),
  mountains("trees", Gamedata::getInstance().getXmlInt("trees/factor") ),
  
 
  viewport( Viewport::getInstance() ),
  scaledSprites(),
  charizard(NULL),
  vegeta(NULL),
  sprites(),
  //vegeta(),
  //charizard(),
  //multisprites(),
  currentSprite(),
  numberofdb(Gamedata::getInstance().getXmlInt("numberOfSprites")),
  gameover(false),
  makeVideo( false ),
  frameCount( 0 ),
  username(  Gamedata::getInstance().getXmlStr("username") ),
  title( Gamedata::getInstance().getXmlStr("screenTitle") ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") )
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  SDL_WM_SetCaption(title.c_str(), NULL);
  atexit(SDL_Quit);
  sprites.push_back(new Charizard("charizard"));
  
  sprites.push_back(new Vegeta("bat"));

  for(signed int  i=0;i<numberofdb
;i++){
  sprites.push_back( 
    new Sprite("dragonball") );
  }  

 /* sprites.push_back( new TwoWayMultiSprite("charizard","charizard1") );
   sprites.push_back( new MultiSprite("bulbasaur") );
   
  sprites.push_back( new Sprite("pokeball") );*/
   
  //vegeta.push_back(new Vegeta("bat"));
 //charizard.push_back(new Charizard("charizard"));
 //multisprites.push_back(new MultiSprite("bat") );
  charizard=dynamic_cast<Charizard*>(sprites[0]);
  vegeta=dynamic_cast<Vegeta*>(sprites[1]);

  currentSprite = sprites.begin();
  viewport.setObjectToTrack(*currentSprite);
  currentSprite++;
   //makescaledSprites();
  
 

 
}

void Manager::makescaledSprites() {
  /*unsigned numberOfscaledSprites = Gamedata::getInstance().getXmlInt("numberOfSprites");
  scaledSprites.reserve( numberOfscaledSprites );

  for (unsigned i = 0; i < numberOfscaledSprites; ++i) {
    scaledSprites.push_back( new ScaledSprite("dragonball", scaledSpriteSurface) );
  }
  sort(scaledSprites.begin(), scaledSprites.end(), ScaledSpriteCompare());*/
}

void Manager::printscaledSprites() const {
  /*for (unsigned i = 0; i < scaledSprites.size(); ++i) {
    std::cout << scaledSprites[i]->getScale() << std::endl;
  }*/
}

void Manager::checkForCollisions()
{
  static SDLSound sound;
   std::list<flamethrower>::const_iterator fth = charizard->flamethrowerList.begin();
   std::list<smallSprite>::const_iterator pls = vegeta->bullets.bulletList.begin();
    while(fth != charizard->flamethrowerList.end())
    {
        if(!vegetaGodMode && cld.collidedWithVegeta(*fth,vegeta))
     { 
      //std::cout<<"Collided with Vegeta"<<std::endl;
      //io.printMessageAt("Collided with Vegeta", 427, 240);
          vegeta->explode();  
          sound[5];
     }
      
     ++ fth;
    }

    while( pls != vegeta->bullets.bulletList.end())
    {if(!charizardGodMode && cld.collidedWithChari(*pls, charizard))
      {//std::cout<<"Collision with Chari"<<std::endl;
      charizard->explode();
      sound[5];
    }
     ++ pls;
    }
    /*Sprite* player = static_cast<Sprite*>( sprites[1] );
  for (unsigned i = 2; i < sprites.size(); ++i) {
    ExplodingAI* e = dynamic_cast<ExplodingAI*>(sprites[i]);
    Sprite* sprite = static_cast<Sprite*>( sprites[i] );
    if ( e && e->chunkCount() == 0 ) { 
      // Make a smart sprite
      sprites[i] = new SmartSprite(sprite->getName(), 
        sprite->getPosition(), *player); 
      delete sprite;
     // ++numberOfSmart;
    }
    if ( !e && cld.collidedWithDragonBall(player,e) ) { 
      sprites[i] = new ExplodingAI(sprite);
      delete sprite;
     // if ( numberOfGreen ) --numberOfGreen;
    }
  }*/



    std::vector<Drawable*>::const_iterator sprite = sprites.begin();
    sprite++;
    sprite++;
    while(sprite!=sprites.end())
    {
      Sprite* e=dynamic_cast<Sprite*>(*sprite);
      
      if( !e->IAmExploding() && cld.collidedWithDragonBall(vegeta,e))
      {  
          (e)->explode(); 

     }
    /* if ( e  ) { 
      // Make a smart sprite
      Sprite* sprite = static_cast<Sprite*>(sprite);
     Sprite* player1 = static_cast<Sprite*>( sprites[1] );
     
      sprite = new SmartSprite(sprite->getName(), 
        sprite->getPosition(), *player1); 
       delete sprite;


    }*/


  sprite++;
    }

    SDL_Flip(screen);
}

void Manager::draw()  const{

  world.draw();
  /*for (unsigned i = 0; i < scaledSprites.size()/3; ++i){
    scaledSprites[i]->draw();

  }*/
   last.draw();
/*for (unsigned i = scaledSprites.size()/3 ; i < scaledSprites.size()*2/3; ++i){
    scaledSprites[i]->draw();
  }*/
  mountains.draw();
  /*for (unsigned i = scaledSprites.size()*2/3 ; i < scaledSprites.size(); ++i){
    scaledSprites[i]->draw();
  }*/
  /*for (unsigned i = 0; i < scaledSprites.size(); ++i){
    scaledSprites[i]->draw();

  }*/
  std::vector<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    (*ptr)->draw();
    ++ptr;
  }
  //last.draw();
 // vegeta[0]->draw();
  
  //charizard[0]->draw();
  //multisprites[0]->draw();
    io.printMessageAt("Vegeta Health", 700, 30);

  hudhealthvegeta->drawHUDdynamic(screen,vegeta->getHealth());
 
io.printMessageAt("Charizard Health", 700, 80);
  hudhealthcharizard->drawHUDdynamic(screen,charizard->getHealth());
  
  if(charizardGodMode)
  { io.printMessageAt("Charizard God Mode On", 650, 140);}
if(vegetaGodMode)
{
  io.printMessageAt("Vegeta God Mode On", 650, 160);
}
  //clock.display();
/*std::list<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    (*ptr)->draw();
    ++ptr;
  }*/

  /*for (unsigned i = 0; i < sprites.size(); ++i) {
    sprites[i]->draw();
  }*/
//player.draw();
  if(clock.getSeconds()<2){
    hudcontrols->drawHUD(screen, Gamedata::getInstance().getXmlInt("HUD/startX"), Gamedata::getInstance().getXmlInt("HUD/startX"));

    io.printMessageAt("Press F1 to toggle HUD", 10, 70);
  clock.display();
  io.printMessageAt("Press A to Turn Vegeta Left", 10, 110);
  io.printMessageAt("Press D to Turn Vegeta Right", 10, 130);
  io.printMessageAt("Press arrow keys fpr Charizard", 10, 150);
  io.printMessageAt("Press Space bar Speed up vegeta", 10, 170);
  io.printMessageValueAt("BulletList: ", static_cast<Charizard*>(charizard)->getFlameListSize(), 10, 190);
     io.printMessageValueAt("FreeList: ",  static_cast<Charizard*> (charizard)->getFreeListSize(), 10, 210);
      io.printMessageValueAt("PlasmaList: ", static_cast<Vegeta*>(vegeta)->getBulletlistSize(), 10, 230);
       io.printMessageAt("Press E to Shoot Plasma with Vegeta", 10, 250);
  io.printMessageAt("Press R_Ctrl to Soot Fireballs with Charlizard", 10, 270);
    // io.printMessageValueAt("PasmaFreeList: ",  static_cast<Vegeta*> (vegeta[0])->getBulletlistSize(), 10, 250);

  //io.printMessageAt("Press no buttons return to idle state ", 10, 190);
   
}
   else if(drawHud == true){
  hudcontrols->drawHUD(screen, Gamedata::getInstance().getXmlInt("HUD/startX"), Gamedata::getInstance().getXmlInt("HUD/startX"));

    io.printMessageAt("Press F1 to toggle HUD", 10, 70);
    clock.display();
    io.printMessageAt("Press A to Turn Vegeta Left", 10, 110);
  io.printMessageAt("Press D to Turn Vegeta Right", 10, 130);
  io.printMessageAt("Press arrow keys to turn Charizard", 10, 150);
  io.printMessageAt("Press Space bar Speed up vegeta", 10, 170);
   io.printMessageValueAt("BulletList: ", static_cast<Charizard*>(charizard)->getFlameListSize(), 10, 190);
     io.printMessageValueAt("FreeList: ",  static_cast<Charizard*> (charizard)->getFreeListSize(), 10, 210);
     io.printMessageValueAt("PlasmaList: ", static_cast<Vegeta*>(vegeta)->getBulletlistSize(), 10, 230);
     io.printMessageAt("Press E to Shoot Plasma with Vegeta", 10, 250);
  io.printMessageAt("Press R_Ctrl to Soot Fireballs with Charlizard", 10, 270);
     //io.printMessageValueAt("PasmaFreeList: ",  static_cast<Vegeta*> (vegeta[0])->getFreelistSize(), 10, 250);
  //io.printMessageAt("Press S for slow motion", 10, 190);
  

 }

 if(vegeta->lost){
io.printMessageAt("Vegeta has Lost",300 , 200);
io.printMessageAt("Press r to restart the game",300 , 220);
}

if(charizard->lost){
io.printMessageAt("charizard has Lost",300 , 200);
io.printMessageAt("Press r to restart the game",300 , 220);
}
 //bar.draw();
  
  io.printMessageAt(title, 10, 450);
  
  viewport.draw();

  SDL_Flip(screen);
}

void Manager::makeFrame() {
  std::stringstream strm;
  strm << "frames/" << username<< '.' 
       << std::setfill('0') << std::setw(4) 
       << frameCount++ << ".bmp";
  std::string filename( strm.str() );
  std::cout << "Making frame: " << filename << std::endl;
  SDL_SaveBMP(screen, filename.c_str());
}

void Manager::switchSprite() {
  /*++currentSprite;
  if ( currentSprite == sprites.end() ) {
    currentSprite = sprites.begin();
  }
  viewport.setObjectToTrack(*currentSprite);
  viewport.setObjectToTrack(vegeta[0]);*/
  /*currentSprite = (currentSprite+1) % sprites.size();
  viewport.setObjectToTrack(sprites[currentSprite]);
  viewport.setObjectToTrack(vegeta[currentSprite]);*/
  /*currentSprite = (currentSprite+1) % sprites.size();
  viewport.setObjectToTrack(sprites[currentSprite]);*/

}

void Manager::update() {
  clock.update();
  
  Uint32 ticks = clock.getElapsedTicks();

  
  /*for (unsigned int i = 0; i < sprites.size(); ++i) {
    sprites[i]->update(ticks);
  }*/
  /*for (unsigned i = 0; i < scaledSprites.size(); ++i) {
    scaledSprites[i]->update(ticks);
  }*/
  /*std::list<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    (*ptr)->update(ticks);
    ++ptr;
  }*/
   std::vector<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    (*ptr)->update(ticks);
    ++ptr;
  }
   /*for (unsigned int i = 0; i < vegeta.size(); ++i) {
  vegeta[i]->update(ticks);
  }
   for (unsigned int i = 0; i < charizard.size(); ++i) {
  charizard[i]->update(ticks);
  }*/
  
  /*player.update(ticks);
  player.stop();*/
  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }
  checkForCollisions() ;
// bar.update(ticks);
  world.update();
  mountains.update();
  
  viewport.update(); // always update viewport last
}

void Manager::play() {
  SDL_Event event;
  bool done = false;
  static SDLSound sound;
  
  while ( not done ) {
  if(vegeta->getHealth()<=0)
    vegeta->lost=true;
  else if(charizard->getHealth()<=0)
    charizard->lost=true;
    while ( SDL_PollEvent(&event) ) {
      Uint8 *keystate = SDL_GetKeyState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
          break;
        }

        if ( keystate[SDLK_2] ) {
          vegeta->explode();
        }
        if ( keystate[SDLK_t] ) {
          switchSprite();
        }
        if ( keystate[SDLK_c] ) {
          charizardGodMode=!charizardGodMode;
          
        }
        if ( keystate[SDLK_v] ) {
          vegetaGodMode=!vegetaGodMode;
         
        }

        if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }
         if (keystate[SDLK_RCTRL]) {
        charizard->shoot("greenorb",
          charizard->getPosition()+Vector2f(60,10),
          Vector2f(Gamedata::getInstance().getXmlInt("greenorb/speedX")+Gamedata::getInstance().getXmlInt("flamethrower/speedx"),
            Gamedata::getInstance().getXmlInt("greenorb/speedY")+Gamedata::getInstance().getXmlInt("flamethrower/speedy")),
          FrameFactory::getInstance().getFrame("greenorb"));
        sound[1];
        }
   if (keystate[SDLK_F1]) {
          if(drawHud == true) drawHud = false ;
          else if(drawHud == false) drawHud = true;
        }
        if (keystate[SDLK_r]) {
    resetvar=true;
                done=true;
                vegeta->lost=false;
                charizard->lost=false;
                break;
        }
         
    
        /*switch(event.key.keysym.sym){
        case SDLK_LEFT:
    player->toggleLeft();  break;
        case SDLK_RIGHT:
    player->toggleRight(); break; 
        case SDLK_UP:
    player->toggleUp(); break; 
        case SDLK_DOWN:
    player->toggleDown(); break;  
  default:break;
      }*/
}


     /*if(event.type == SDL_KEYUP){
        switch(event.key.keysym.sym){
         case SDLK_LEFT:
    player->toggleLeft();  break;
        case SDLK_RIGHT:
    player->toggleRight(); break; 
        case SDLK_UP:
    player->toggleUp(); break; 
        case SDLK_DOWN:
    player->toggleDown(); break; 
  default:break; 
  } 
     } */
        
  

    }
    draw();
  if(!vegeta->lost && !charizard->lost)
  
    update();
  }
}
