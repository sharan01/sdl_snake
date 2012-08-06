#include "drawEngine.h"


void drawEngine::drawRect(unsigned short x, unsigned short y, Uint32 color, unsigned short w, unsigned short h)
{
	SDL_Rect tmp = {x,y,w,h};
	SDL_FillRect(SDL_GetVideoSurface(), &tmp, color);
}