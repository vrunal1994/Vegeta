#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "vector2f.h"
#include "multisprite.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"
#include "frameFactory.h"
class ScaledSpriteCompare {
public:
  bool operator()(const ScaledSprite* lhs, const ScaledSprite* rhs) {
    return lhs->getScale() < rhs->getScale();
  }
};
Manager::Manager() :
  cld(Collider::getInstance()),
  resetvar(false),
  Godmode(false),
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  gdata( Gamedata::getInstance() ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  HudShow(true),
  screen( io.getScreen() ),
  orbSurface( io.loadAndSet(gdata.getXmlStr("redorb/file"), 
              gdata.getXmlBool("redorb/transparency")) ),
  world("layer",gdata.getXmlInt("layer/factor")),
  world1("layer1", gdata.getXmlInt("layer1/factor") ),
  world2("layer2", gdata.getXmlInt("layer2/factor") ),
  world3("layer3", gdata.getXmlInt("layer3/factor") ),
  world4("layer4", gdata.getXmlInt("layer4/factor") ),
  world5("conclusion",gdata.getXmlInt("conclusion/factor")),
  start(true),
  player(NULL),
  hud1(new Hud("Controls")),
  hud2(new Hud("Health")),
  viewport( Viewport::getInstance() ),
  surfaces(),
  orbs(),
  sprites(),
  currentSprite(),
  makeVideo(false),
  frameCount(0),
  username(  gdata.getXmlStr("username") ),
  title( gdata.getXmlStr("screenTitle") ),
  frameMax( gdata.getXmlInt("frameMax") ),
  maxCount(gdata.getXmlInt("greenorb/count")),
  safedistance(0),
  reduc(false)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  SDL_WM_SetCaption(title.c_str(), NULL);
  atexit(SDL_Quit);
  sprites.push_back(new Player("girl",FrameFactory::getInstance().getFrames("girl")));
  unsigned numberOfZombies = gdata.getXmlInt("numberOfZombies");
  for (unsigned i = 0; i < numberOfZombies; ++i) {
    sprites.push_back(new MultiSprite("zombie",FrameFactory::getInstance().getFrames("zombie")));
}
  player=dynamic_cast<Player*>(sprites.front());
  currentSprite = sprites.begin();
  viewport.setObjectToTrack(*currentSprite);
  currentSprite++;
  makeOrbs();
  printOrbs();
}
Manager::~Manager() { 
  std::list<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    delete (*ptr);
    ++ptr;
  }
  SDL_FreeSurface(orbSurface);
  for (unsigned i = 0; i < orbs.size(); ++i) {
    delete orbs[i];
  }
delete hud1;
delete hud2;
  orbs.clear();
if(resetvar){
Manager mang;
mang.play();
}
}
int Manager::getRandom(){
  int num=gdata.getRandInRange(0,100);
  num*=rand()%2?-1:1;
  return num;
}
void Manager::checkForCollisions(){
static SDLSound sound; 
  std::list<Drawable*>::const_iterator sprite = sprites.begin();
  sprite ++;
  if(!Godmode)
    while(sprite!=sprites.end()){
      if(!(dynamic_cast<MultiSprite*>(*sprite))->IAmExploding())
      if(cld.collidedWithPlayer(player,*sprite)){  
          player->explode();	
     }
  sprite++;
}
  sprite=sprites.begin();
  sprite++;
    std::list<Bullet>::const_iterator bullet = player->bulletList.begin();
    while(bullet != player->bulletList.end())
    {
     while(sprite!=sprites.end())
     {
      if(cld.collidedWith(*bullet,*sprite))
     { 
         (*sprite)->explode();
	 sound[0];
     }
      ++sprite;
     }
     ++ bullet;
    }

}
void Manager::makeOrbs() {
  unsigned numberOfOrbs = gdata.getXmlInt("numberOfOrbs");
  orbs.reserve( numberOfOrbs );
  for (unsigned i = 0; i < numberOfOrbs; ++i) {
    orbs.push_back( new ScaledSprite("redorb", orbSurface) );
  }
  sort(orbs.begin(), orbs.end(), ScaledSpriteCompare());
}

void Manager::printOrbs() const {
  for (unsigned i = 0; i < orbs.size(); ++i) {
    std::cout << orbs[i]->getScale() << std::endl;
  }
}

void Manager::draw() const {
  if(start)
  world.draw();
  else{
    world1.draw();
    world2.draw();
    world3.draw();
    for (unsigned i = 0; i < orbs.size()/2; ++i) {
      orbs[i]->draw();
    }
  world4.draw();
  for (unsigned i = orbs.size()/2; i < orbs.size(); ++i) {
    orbs[i]->draw();
  }
  std::list<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    (*ptr)->draw();
    ++ptr;
  }
  if(player->win)
  world5.draw();
  else{
  io.printMessageAt(title, 300, 10);
  hud2->drawHUDdynamic(screen,player->getHealth());
  
    if(HudShow){
      hud1->drawHUD(screen);
      io.printMessageAt("Good vs Evil", 340, 20);
      io.printMessageAt("The control for game is", 50, 100);
      io.printMessageAt("Press a to move left", 50, 120);
      io.printMessageAt("Press d to move right", 50, 140);   
      io.printMessageAt("Press w to move up", 50, 160);
      io.printMessageAt("Press s to move down", 50, 180);
      io.printMessageAt("Press h for shooting ", 50, 200);
      io.printMessageAt("Press G to play in God mode", 50, 220);
      io.printMessageAt("Press r to restart", 50, 240);
      io.printMessageValueAt("bulletList:",player->bulletList.size(),50, 260);
      io.printMessageValueAt("freeList:",player->freeList.size(),50, 280);

    }
}
if(player->lost){
io.printMessageAt("Player has Lost",300 , 200);
io.printMessageAt("Press r to restart the game",300 , 220);
}
}
   //viewport.draw();

   SDL_Flip(screen);
}

// Move this to IOManager
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
  ++currentSprite;
  if ( currentSprite == sprites.end() ) {
    currentSprite = sprites.begin();
  }
  viewport.setObjectToTrack(*currentSprite);
} 

void Manager::update() {
  clock.update();
  Uint32 ticks = clock.getTicksSinceLastFrame();
  if(clock.getSeconds()==gdata.getXmlInt("Controls/autoDisappearTime"))HudShow=0;
  for (unsigned i = 0; i < orbs.size(); ++i) {
    orbs[i]->update(ticks);
  } 
  safeDistance();
  smartingit();
  std::list<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    (*ptr)->update(ticks);
    ++ptr;
  }
  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }
  checkForCollisions() ;
  world1.update();
  world2.update();
  world3.update();
  world4.update();
  viewport.update(); // always update viewport last
}
void Manager::smartingit(){
  std::list<Drawable*>::iterator it = sprites.begin();
  it++;
  while(it!=sprites.end()){
  if((dynamic_cast<MultiSprite*>(*it))->smart){
    if(player->X() < (*it)->X()){
      if(player->Y() > (*it)->Y())
        (*it)->setVelocity(Vector2f((*it)->velocityX(),-50));
      else 
        (*it)->setVelocity(Vector2f((*it)->velocityX(),50));
    }
    else
       (*it)->setVelocity(Vector2f((*it)->velocityX(),0));
    }
  it++;
}
}

void Manager::safeDistance(){
  std::list<Drawable*>::iterator it = sprites.begin();
  it++;
  while(it!=sprites.end()){
    safedistance=hypot((player->X() - (*it)->X()),(player->Y() - (*it)->Y()));
    if(safedistance<gdata.getXmlInt("girl/safeDistance"))
      (dynamic_cast<MultiSprite*>(*it))->smart=true;
  it++	;
}
}
void Manager::toggleToGod(){
  Godmode=!Godmode;
}
void Manager::play() {
  SDL_Event event;
  bool done = false;
  clock.start(); 
  static SDLSound sound;
  while ( not done ) {
  if(player->getHealth()<=0)player->lost=true;
    while ( SDL_PollEvent(&event) ) {
      Uint8 *keystate = SDL_GetKeyState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
          break;
        }
if ( keystate[SDLK_SPACE]) {
          start=false;
        }
if(!start){
        if ( keystate[SDLK_t] ) {
          switchSprite();
        }
  	 if ( keystate[SDLK_g] ) {
          toggleToGod();
        }

        if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }
         if (keystate[SDLK_u]) {
          clock.toggleCapFrameRate();    
        }
	 if (keystate[SDLK_F1]) {
          HudShow=!HudShow;;
        }
         if (keystate[SDLK_r]) {
		resetvar=true;
                done=true;
                break;
        }
 	if (keystate[SDLK_h]) {
        player->shoot("greenorb",player->getPosition()+Vector2f(20,20),Vector2f(gdata.getXmlInt("greenorb/speedX")+gdata.getXmlInt("bullet/speedx"),gdata.getXmlInt("greenorb/speedY")+gdata.getXmlInt("bullet/speedy")),FrameFactory::getInstance().getFrame("greenorb"));
        sound[1];
        }
        switch(event.key.keysym.sym){
        case SDLK_a:
	  player->toggleLeft();  break;
        case SDLK_d:
	  sprites.front()->toggleRight(); break; 
        case SDLK_w:
	  sprites.front()->toggleUp(); break; 
        case SDLK_s:
	  sprites.front()->toggleDown(); break;  
	default:break;
      }
}
}
if(!start){	
     if(event.type == SDL_KEYUP){
        switch(event.key.keysym.sym){
        case SDLK_a:
	  sprites.front()->toggleLeft(); break; 
        case SDLK_d:
	  sprites.front()->toggleRight(); break;
        case SDLK_w:
	  sprites.front()->toggleUp(); break;
        case SDLK_s:
	  sprites.front()->toggleDown(); break; 
	default:break; 
	} 
     } 
  }

    }
    draw();
  if(!player->win && !player->lost && !start)
    update();
  }
}
