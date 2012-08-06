#include "SDL/SDL.h"

#ifndef DRAWENGINE_H
#define DRAWENGINE_H

class drawEngine
{
public:
	void drawRect(unsigned short x, unsigned short y, Uint32 color, unsigned short w=10, unsigned short h=10);

};

#endif