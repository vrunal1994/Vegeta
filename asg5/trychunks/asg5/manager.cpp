#include <iostream>
#include <string>
#include <iomanip>
#include "multisprite.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"
#include "twoWayMultiSprite.h"
#include <algorithm>
#include "frameFactory.h"

Manager::~Manager() { 
  // These deletions eliminate "definitely lost" and
  // "still reachable"s in Valgrind.
  /*std::list<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    delete (*ptr);
    ++ptr;
  }*/
  /*for (unsigned i = 0; i < sprites.size(); ++i) {
    delete sprites[i];
  }*/
     for(unsigned i = 0; i< vegeta.size(); ++i)
  {delete vegeta[i];}
 for(unsigned i = 0; i< charizard.size(); ++i)
  {delete charizard[i];}

 for (unsigned i = 0; i < scaledSprites.size(); ++i) {
    delete scaledSprites[i];
  }
  scaledSprites.clear();
  
}

class ScaledSpriteCompare {
public:
  bool operator()(const ScaledSprite* lhs, const ScaledSprite* rhs) {
    return lhs->getScale() < rhs->getScale();
  }
};

Manager::Manager() :
cld(Collider::getInstance()),
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  hud(), bar(),
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
  //player(NULL),
  sprites(),
  vegeta(),
  charizard(),
  currentSprite(0),

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
  //sprites.push_back(new Player("charizard",FrameFactory::getInstance().getFrames("charizard")));

 /* sprites.push_back( new TwoWayMultiSprite("charizard","charizard1") );
   sprites.push_back( new MultiSprite("bulbasaur") );
   
  sprites.push_back( new Sprite("pokeball") );*/
   
  vegeta.push_back(new Vegeta("bat"));
 charizard.push_back(new Charizard("charizard"));
  /*player=dynamic_cast<Player*>(sprites.front());
  currentSprite = sprites.begin();*/
   makescaledSprites();
  //viewport.setObjectToTrack(*currentSprite);
  //currentSprite++;
  viewport.setObjectToTrack(charizard[currentSprite]);

 
}

void Manager::makescaledSprites() {
  unsigned numberOfscaledSprites = Gamedata::getInstance().getXmlInt("numberOfSprites");
  scaledSprites.reserve( numberOfscaledSprites );

  for (unsigned i = 0; i < numberOfscaledSprites; ++i) {
    scaledSprites.push_back( new ScaledSprite("dragonball", scaledSpriteSurface) );
  }
  sort(scaledSprites.begin(), scaledSprites.end(), ScaledSpriteCompare());
}

void Manager::printscaledSprites() const {
  for (unsigned i = 0; i < scaledSprites.size(); ++i) {
    std::cout << scaledSprites[i]->getScale() << std::endl;
  }
}

void Manager::checkForCollisions()
{

   std::list<flamethrower>::const_iterator fth = charizard[0]->flamethrowerList.begin();
    while(fth != charizard[0]->flamethrowerList.end())
    {
        if(cld.collidedWithVegeta(*fth,vegeta[0]))
     { 
      std::cout<<"collided"<<std::endl;
  io.printMessageAt("Collided", 427, 240);
          vegeta[0]->explode();  

         //
     }
      
     ++ fth;
    }
    SDL_Flip(screen);
}

void Manager::draw()  const{
  
  world.draw();
  for (unsigned i = 0; i < scaledSprites.size()/3; ++i){
    scaledSprites[i]->draw();

  }
   last.draw();
for (unsigned i = scaledSprites.size()/3 ; i < scaledSprites.size()*2/3; ++i){
    scaledSprites[i]->draw();
  }
  mountains.draw();
  for (unsigned i = scaledSprites.size()*2/3 ; i < scaledSprites.size(); ++i){
    scaledSprites[i]->draw();
  }
  //last.draw();
  vegeta[0]->draw();
  charizard[0]->draw();
  
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
    hud.drawHUD(screen, Gamedata::getInstance().getXmlInt("HUD/startX"), Gamedata::getInstance().getXmlInt("HUD/startX"));

    io.printMessageAt("Press F1 to toggle HUD", 10, 70);
  clock.display();
  io.printMessageAt("Press A to Turn Vegeta Left", 10, 110);
  io.printMessageAt("Press D to Turn Vegeta Right", 10, 130);
  io.printMessageAt("Press arrow keys fpr Charizard", 10, 150);
  io.printMessageAt("Press Space bar Speed up vegeta", 10, 170);
  io.printMessageValueAt("BulletList: ", static_cast<Charizard*>(charizard[0])->getFlameListSize(), 10, 190);
     io.printMessageValueAt("FreeList: ",  static_cast<Charizard*> (charizard[0])->getFreeListSize(), 10, 210);

  //io.printMessageAt("Press no buttons return to idle state ", 10, 190);
   
}
   else if(drawHud == true){
  hud.drawHUD(screen, Gamedata::getInstance().getXmlInt("HUD/startX"), Gamedata::getInstance().getXmlInt("HUD/startX"));

    io.printMessageAt("Press F1 to toggle HUD", 10, 70);
    clock.display();
    io.printMessageAt("Press A to Turn Vegeta Left", 10, 110);
  io.printMessageAt("Press D to Turn Vegeta Right", 10, 130);
  io.printMessageAt("Press arrow keys to turn Charizard", 10, 150);
  io.printMessageAt("Press Space bar Speed up vegeta", 10, 170);
   io.printMessageValueAt("BulletList: ", static_cast<Charizard*>(charizard[0])->getFlameListSize(), 10, 190);
     io.printMessageValueAt("FreeList: ",  static_cast<Charizard*> (charizard[0])->getFreeListSize(), 10, 210);
  //io.printMessageAt("Press S for slow motion", 10, 190);
  

 }
 bar.draw();
  
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
  for (unsigned i = 0; i < scaledSprites.size(); ++i) {
    scaledSprites[i]->update(ticks);
  }
  /*std::list<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    (*ptr)->update(ticks);
    ++ptr;
  }*/
   
   for (unsigned int i = 0; i < vegeta.size(); ++i) {
  vegeta[i]->update(ticks);
  }
   for (unsigned int i = 0; i < charizard.size(); ++i) {
  charizard[i]->update(ticks);
  }
  /*player.update(ticks);
  player.stop();*/
  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }
  checkForCollisions() ;
 bar.update(ticks);
  world.update();
  mountains.update();
  last.update();
  viewport.update(); // always update viewport last
}

void Manager::play() {
  SDL_Event event;
  bool done = false;
  
  
  while ( not done ) {
  
    while ( SDL_PollEvent(&event) ) {
      Uint8 *keystate = SDL_GetKeyState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
          break;
        }

        if ( keystate[SDLK_t] ) {
          switchSprite();
        }

        if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }
         if (keystate[SDLK_h]) {
        charizard[0]->shoot("greenorb",
          charizard[0]->getPosition()+Vector2f(60,10),
          Vector2f(Gamedata::getInstance().getXmlInt("greenorb/speedX")+Gamedata::getInstance().getXmlInt("flamethrower/speedx"),
            Gamedata::getInstance().getXmlInt("greenorb/speedY")+Gamedata::getInstance().getXmlInt("flamethrower/speedy")),
          FrameFactory::getInstance().getFrame("greenorb"));
        
        }
   if (keystate[SDLK_F1]) {
          if(drawHud == true) drawHud = false ;
          else if(drawHud == false) drawHud = true;
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
  
    update();
  }
}
