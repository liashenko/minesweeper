#include "Game.h"

Game::Game()
{
	_screenWidth = 500;
	_screenHeight = 500;
	_gameState = GameState::RUN;
	_pause = false;
}

Game::~Game()
{
}

void Game::finish(GameFinished result)
{
	if (result == GameFinished::WIN)
	{
		//
	}
	else if (result == GameFinished::LOSS)
	{
		//
	}

	_board.openEveryCell();
	_pause = true;
}

void Game::run()
{
	init();
	
	while (_gameState != GameState::STOP)
	{
		if (_gameState == GameState::RUN)
		{
			//Render
			_graphics.render(_board);
			//Events
			if (_board.isThereSafeCells() == false)
			{
				finish(GameFinished::WIN);
			}
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					_gameState = GameState::STOP;
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (_pause)
					{
						restart();
					}
					else
					{

						int x = event.button.x / 20 + 1;
						int y = event.button.y / 20 + 1;

						cout << x << " " << y << endl;

						if (event.button.button == SDL_BUTTON_LEFT)
						{
							if (_board.getValue(y, x) == -1)
							{
								_board.explodeCell(y, x);
								finish(GameFinished::LOSS);
							}
							else
							{
								_board.openCell(y, x);
							}
						}
					}
				}
				else if (event.type == SDL_KEYDOWN)
				{
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						restart();
					}
				}
			}
		}
	}
}

void Game::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	_graphics = Graphics(_screenWidth, _screenHeight);
	_board = Board(_mines);
}


void Game::restart()
{
	_board = Board(_mines);
	_pause = false;
}