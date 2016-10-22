#include "ioManager.h"
#include "clock.h"
#include "aaline.h"

class HUD

{
    public:
        HUD();
        ~HUD();
        void drawHUD(SDL_Surface* screen , int x, int y ) const;    
    private:
    
        Clock& clock;
        const IOManager& io;
        HUD(const HUD&);
        HUD& operator=(const HUD&);

};