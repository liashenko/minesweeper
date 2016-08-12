#pragma once

#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <string>
#include "Board.h"

using namespace std;

class Graphics
{
public:
	Graphics();
	Graphics(int screenWidth, int screenHeight);
	~Graphics();
	void loadImages();
	void render(Board board);
private:
	int screenWidth;
	int screenHeight;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *img[12];
};

