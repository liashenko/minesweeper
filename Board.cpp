#include "Board.h"

Board::Board(int minesCount)
{
	freeBoard();
	addMines(minesCount);
	fillBoard();
	//printBoard();
}

Board::Board()
{
}

Board::~Board()
{
}

void Board::addMines(int count)
{
	//set mines randomly
	int x, y;
	srand(time(0));
	while (count > 0) {
		x = rand() % WIDTH + 1;
		y = rand() % HEIGHT + 1;
		if (_board[y][x].val == 0)
		{
			_board[y][x].val = -1;
			count--;
		}
	}
}

void Board::freeBoard()
{
	//free board
	for (int i = 0; i < HEIGHT + 2; i++)
	{
		for (int j = 0; j < WIDTH + 2; j++)
		{
			_board[i][j].val = 0;
			_board[i][j].opened = false;
		}
	}
}
void Board::fillBoard()
{
	for (int i = 1; i < HEIGHT; i++)
	{
		for (int j = 1; j < WIDTH; j++)
		{
			if (_board[i][j].val != -1)
			{
				//count bombs around cell
				_board[i][j].val += _board[i - 1][j - 1].val == -1 ? 1 : 0;
				_board[i][j].val += _board[i - 1][j].val == -1 ? 1 : 0;
				_board[i][j].val += _board[i - 1][j + 1].val == -1 ? 1 : 0;
				_board[i][j].val += _board[i][j - 1].val == -1 ? 1 : 0;
				_board[i][j].val += _board[i][j + 1].val == -1 ? 1 : 0;
				_board[i][j].val += _board[i + 1][j - 1].val == -1 ? 1 : 0;
				_board[i][j].val += _board[i + 1][j].val == -1 ? 1 : 0;
				_board[i][j].val += _board[i + 1][j + 1].val == -1 ? 1 : 0;
			}
		}
	}
}

int Board::getValue(int y, int x)
{
	return _board[y][x].val;
}

bool Board::isOpened(int y, int x)
{
	return _board[y][x].opened;
}

void Board::openEveryCell()
{
	for (int i = 0; i < HEIGHT + 2; i++)
	{
		for (int j = 0; j < WIDTH + 2; j++)
		{
			_board[i][j].opened = true;
		}
	}
}

void Board::openCell(int y, int x)
{
	if (x > 0 && x <= Board::WIDTH && y > 0 && y <= Board::HEIGHT)
	{
		if (_board[y][x].opened == false && _board[y][x].val != -1)
		{
			_board[y][x].opened = true;
			if (_board[y][x].val == 0)
			{
				//kind of a flood fill
				openCell(y - 1, x - 1);
				openCell(y - 1, x);
				openCell(y - 1, x + 1);
				openCell(y, x - 1);
				openCell(y, x + 1);
				openCell(y + 1, x - 1);
				openCell(y + 1, x);
				openCell(y + 1, x + 1);
			}
		}
	}
}

bool Board::isThereSafeCells()
{
	for (int i = 1; i < HEIGHT + 1; i++)
	{
		for (int j = 1; j < WIDTH + 1; j++)
		{
			if (_board[i][j].val != -1 && _board[i][j].opened == false)
				return true;
		}
	}
	return false;
}

void Board::explodeCell(int y, int x)
{
	_board[y][x].val = -2;
}


void Board::printBoard()
{
	for (int i = 1; i < HEIGHT + 1; i++)
	{
		for (int j = 1; j < WIDTH + 1; j++)
		{
			if (_board[i][j].val == -1)
				cout << "*" << " ";
			else
				cout << _board[i][j].val << " ";
		}
		cout << endl;
	}
}