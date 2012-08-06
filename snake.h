#include <iostream>
#include <fstream>
#include <vector>

#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <typeinfo>
#include "snakepart.h"
#include "drawEngine.h"

using namespace std;

#ifndef SNAKE_H
#define SNAKE_H



class snakeclass 
{
	int points, del, width, height;
	char direction;
	bool get;
	snakepart food;
	vector<snakepart> snake;
	SDL_Surface* screen;
	TTF_Font* font;

	drawEngine draw; //drawengine


	void putfood();
	bool collision();
	void movesnake();
public:
	snakeclass();
	~snakeclass();
	void start();


};




#endif