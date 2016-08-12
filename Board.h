#pragma once

#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;


class Board
{
public:
	static const int HEIGHT = 25;
	static const int WIDTH = 25;
	void freeBoard();
	void addMines(int count);
	void fillBoard();
	void printBoard();
	int getValue(int y, int x);
	bool isOpened(int y, int x);
	void openCell(int y, int x);
	void openEveryCell();
	bool isThereSafeCells();
	void explodeCell(int y, int x);
	Board(int minesCount);
	Board();
	~Board();
private:
	struct cell{
		int val;
		bool opened;
	}_board[HEIGHT + 2][WIDTH + 2];
};

