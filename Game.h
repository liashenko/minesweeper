#pragma once

#include "Graphics.h"
#include "Board.h"

enum class GameState { RUN = 1, STOP = 2};
enum class GameFinished { WIN = 0, LOSS = 1 };
enum class GameDifficulty {EASY = 40, MEDIUM = 70, HARD = 120};

class Game
{
public:
	Game();
	~Game();
	void run();
	void init();
	void restart();
	void finish(GameFinished result);
private:
	int _screenWidth;
	int _screenHeight;
	bool _pause;
	int _mines = (int)GameDifficulty::MEDIUM;
	Board _board;
	Graphics _graphics;
	GameState _gameState;
	SDL_Event event;
};

