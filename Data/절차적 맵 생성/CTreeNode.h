#pragma once

struct Room
{
	int** size;
	int rowSize;
	int colSize;
};


class Tree {
private:
	Room info;
	Tree* left;
	Tree* right;
	Tree* parent;
public:
	void setRoom(int _rowSize, int _colSize);
	Tree* goRoot();
	void devideRoom();
	void devideRoom_row();
	void devideRoom_col();
	void printRoom();
};