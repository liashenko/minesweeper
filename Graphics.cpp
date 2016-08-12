#include "Graphics.h"

#include <cstdio>
#include <string>

Graphics::Graphics(int screenWidth, int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	SDL_Init(SDL_INIT_VIDEO);
	//Create window
	window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	loadImages();
}

void Graphics::loadImages()
{
	//load images
	string path = "";
	for (int i = 0; i < 9; i++)
	{
		path = "resources/" + to_string(i) + ".png";
		img[i] = IMG_LoadTexture(renderer, path.c_str());
		if (!img[0])
		{
			cout << "cant load image " + to_string(i);
		}
	}
	img[9] = IMG_LoadTexture(renderer, "resources/closed.png");
	img[10] = IMG_LoadTexture(renderer, "resources/bomb.png");
	img[11] = IMG_LoadTexture(renderer, "resources/exploded_bomb.png");
}

void Graphics::render(Board board)
{
	SDL_RenderClear(renderer);

	for (int i = 1; i < Board::HEIGHT + 1; i++)
	{
		for (int j = 1; j < Board::WIDTH + 1; j++)
		{
			//closed cell
			int val = 9;
			if (board.isOpened(i, j))
			{
				val = board.getValue(i, j);
				if (val == -1)
				{
					//bomb
					val = 10;
				}
				else if (val == -2)
				{
					//exploded bomb
					val = 11;
				}
			}
			// put the location where we want the texture to be drawn into a rectangle
			SDL_Rect texr;
			texr.w = 20;
			texr.h = 20;
			texr.x = (j - 1) * 20;
			texr.y = (i - 1) * 20;
			// copy the texture to the rendering context
			SDL_RenderCopy(renderer, img[val], NULL, &texr);
		}
	}
	// flip the backbuffer
	// this means that everything that we prepared behind the screens is actually shown
	SDL_RenderPresent(renderer);
}


Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}
