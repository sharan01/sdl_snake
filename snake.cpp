#include "snake.h"


/* to do list
 * make menu
 * top scores saving
 * better colors
 */

snakeclass::snakeclass()
{
	

	//window width and height
	width =800;
	height=400;
	//init SDL and ttf
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_WM_SetCaption ("Snake", NULL);
	font = TTF_OpenFont("lucida.ttf", 16);
	screen = SDL_SetVideoMode(width,height, 32, SDL_SWSURFACE);

	for(int i=0; i<5; i++)
	{
		snake.push_back(snakepart(40+i, 10));
	}
	points = 0;
	del = 80;
	get = false;
	direction = 'l';
	srand(time(0));
	putfood();

	// SDL draw rect edges of the game
	draw.drawRect(0,0, SDL_MapRGB(screen->format, 252, 138, 0),width, 10);
	draw.drawRect(0,0, SDL_MapRGB(screen->format, 252, 138, 0),10, height-20);
	draw.drawRect(0,370, SDL_MapRGB(screen->format, 252, 138, 0),width, 10);
	draw.drawRect(width-10,0, SDL_MapRGB(screen->format, 252, 138, 0),10, height-20);
	
	
	for(auto &i : snake)
	{
		draw.drawRect(i.x*10,i.y*10, SDL_MapRGB(screen->format, 39, 198, 247));
		cout << typeid ( i ).name() << endl;
	}

} //end snake constructor
snakeclass::~snakeclass()
{
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();	
}

// put food
void snakeclass::putfood()
{
	while(1)
	{
		int tmpx=rand()%width/10+1;
		int tmpy=rand()%height/10+1;
		for(auto &i : snake)
		{	
			if(i.x == tmpx && i.y == tmpy)
				continue;	
		}
		
		if(tmpx>=width/10-20|| tmpy>=height/10-30)
			continue;
		food.x=tmpx;
		food.y=tmpy;
		break;
	}
	draw.drawRect(food.x*10, food.y*10, SDL_MapRGB(screen->format, 123,255,0)); // light green
}
	



bool snakeclass::collision()
{
	//collisuon will walls
	if(snake[0].x==0 || snake[0].x==width-1 || snake[0].y==0 || snake[0].y==height-3)
	{
		return true;
	}

	//collsiosn wil itlself	
	
	for(int i=2; i<snake.size(); i++)
	{
		if(snake[0].x== snake[i].x && snake[0].y== snake[i].y) // he gave it zero =================================================
			return true;
	}
	// collsion with food
	if(snake[0].x==food.x && snake[0].y == food.y)
	{
		get=true;
		//put another food
		putfood();
		points+=10;
		char c[5];
		sprintf(c, "%d", points);
		SDL_Surface* text;
		SDL_Color white = {255, 255, 255};
		text = TTF_RenderText_Solid(font, c, white);
		SDL_Rect tmp = {0, 380};
		// black rectangle to dlete points postion
		draw.drawRect(0, 380, SDL_MapRGB(screen->format, 0, 0, 0), 100, 20);
		SDL_BlitSurface(text, NULL, screen, &tmp);
		SDL_FreeSurface(text);
		
		if((points%80)==0 && del>0)
			del-=20;
	}
	else
		get = false;

	return false;
}

// moving snake

void snakeclass::movesnake()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if(event.type==SDL_KEYDOWN)
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_LEFT:
					if(direction!='r')
						direction='l';
					break;
				case SDLK_UP:
					if(direction!='d')
						direction='u';
					break;
				case SDLK_DOWN:
					if(direction!='u')
						direction='d';
					break;
				case SDLK_RIGHT:
					if(direction!='l')
						direction='r';
					break;
				case SDLK_ESCAPE:
					direction='q';
				break;
			}
		}
		else if(event.type==SDL_QUIT)
			direction='q';

	}				

	if(!get)
	{
		draw.drawRect(snake[snake.size()-1].x*10, snake[snake.size()-1].y*10, SDL_MapRGB(screen->format, 0, 0, 0));
		snake.pop_back();
	}
	if(direction=='l')
		snake.insert(snake.begin(), snakepart(snake[0].x-1, snake[0].y));
	else if(direction=='r')
		snake.insert(snake.begin(), snakepart(snake[0].x+1, snake[0].y));
	else if(direction=='u')
		snake.insert(snake.begin(), snakepart(snake[0].x, snake[0].y-1));
	else if(direction=='d')
		snake.insert(snake.begin(), snakepart(snake[0].x, snake[0].y+1));

	draw.drawRect(snake[0].x*10, snake[0].y*10, SDL_MapRGB(screen->format, 39, 198, 247));
}


void snakeclass::start()
{
	while(1)
	{
		if(collision())
		{
			SDL_Surface* messege;

			SDL_Color brown = {255, 123, 98};
			messege = TTF_RenderText_Solid(font, "GAME OVER!", brown);
			SDL_Rect gameover = {640/2-40, 170};
			SDL_BlitSurface(messege, NULL, screen, &gameover);//=========================================================================================
			SDL_FreeSurface(messege);
			SDL_Flip(screen);
			SDL_Delay(6000);
			break;
		}
	
		movesnake();
		if(direction=='q')
			break;

		SDL_Flip(screen);
		SDL_Delay(del);
	}
}