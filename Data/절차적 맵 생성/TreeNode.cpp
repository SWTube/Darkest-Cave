#include "CTreeNode.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void Tree::setRoom(int _rowSize, int _colSize) {
	Tree::parent = NULL;
	Tree::left = NULL;
	Tree::right = NULL;

	Tree::info.rowSize = _rowSize;
	Tree::info.colSize = _colSize;

	Tree::info.size = new int* [_rowSize];
	for (int row = 0; row < _rowSize; row++) {
		Tree::info.size[row] = new int[_colSize];
		for (int col = 0; col < _colSize; col++) {
			Tree::info.size[row][col] = 0;
		}
		Tree::info.size[row][0] = 1;
		Tree::info.size[row][_colSize - 1] = 1;
	}
	for (int col = 0; col < _colSize; col++) {
		Tree::info.size[0][col] = 1;
		Tree::info.size[_rowSize - 1][col] = 1;
	}
}

Tree* Tree::goRoot() {
	Tree* location = this;
	while (location->parent != NULL) {
		location = location->parent;
	}
	return location;
}

void Tree::devideRoom() {
	Tree::devideRoom_col();
	Tree::devideRoom_row();
	Tree* location = this;
	location = location->left;
	if (location->info.colSize <= 5 || location->info.rowSize <= 5) {
		return;
	}
	else {
		location->devideRoom();
	}
		
}

void Tree::devideRoom_row() {
	// 랜덤 시드 설정
	srand((unsigned int)time(NULL));
	int rand_num = rand() % (Tree::info.rowSize - 5) + 5;

	Tree::left = new Tree;
	Tree::right = new Tree;
	Tree::left->parent = this;
	Tree::right->parent = this;

	Tree::left->info.rowSize = rand_num;
	Tree::left->info.colSize = Tree::info.colSize;

	Tree::right->info.rowSize = Tree::info.rowSize - Tree::left->info.rowSize;
	Tree::right->info.colSize = Tree::info.colSize;

	for (int col = 0; col < Tree::info.colSize; col++) {
		Tree::info.size[Tree::left->info.rowSize - 1][col] = 1;
		Tree::info.size[Tree::left->info.rowSize][col] = 1;
	}

	Tree::left->info.size = Tree::info.size;
	//Tree::right->info.size = Tree::info.size;


	/*
	for (int row = 0; row < Tree::left->info.rowSize; row++) {
		for (int col = 0; col < Tree::left->info.colSize; col++) {
			Tree::left->info.size[row][col] = Tree::info.size[row][col];
		}
	}

	for (int row = 0; row < Tree::right->info.rowSize; row++) {
		for (int col = 0; col < Tree::right->info.colSize; col++) {
			Tree::right->info.size[row][col] = Tree::info.size[row + Tree::left->info.rowSize][col];
		}
	}
	*/

	/*
	Tree::left->info.size = new int* [Tree::left->info.rowSize];
	for (int row = 0; row < Tree::left->info.rowSize; row++) {
		Tree::left->info.size[row] = new int[Tree::left->info.colSize];
		for (int col = 0; col < Tree::left->info.colSize; col++) {
			Tree::left->info.size[row][col] = 0;
		}
		Tree::left->info.size[row][0] = 1;
		Tree::left->info.size[row][Tree::left->info.colSize - 1] = 1;
	}
	for (int col = 0; col < Tree::left->info.colSize; col++) {
		Tree::left->info.size[0][col] = 1;
		Tree::left->info.size[Tree::left->info.rowSize - 1][col] = 1;
	}

	Tree::right->info.size = new int* [Tree::right->info.rowSize];
	for (int row = 0; row < Tree::right->info.rowSize; row++) {
		Tree::right->info.size[row] = new int[Tree::right->info.colSize];
		for (int col = 0; col < Tree::right->info.colSize; col++) {
			Tree::right->info.size[row][col] = 0;
		}
		Tree::right->info.size[row][0] = 1;
		Tree::right->info.size[row][Tree::right->info.colSize - 1] = 1;
	}
	for (int col = 0; col < Tree::right->info.colSize; col++) {
		Tree::right->info.size[0][col] = 1;
		Tree::right->info.size[Tree::right->info.rowSize - 1][col] = 1;
	}
	*/
}

void Tree::devideRoom_col() {
	// 랜덤 시드 설정
	srand((unsigned int)time(NULL));
	int rand_num = rand() % (Tree::info.colSize - 5) + 5;

	Tree::left = new Tree;
	Tree::right = new Tree;
	Tree::left->parent = this;
	Tree::right->parent = this;

	Tree::left->info.rowSize = Tree::info.rowSize;
	Tree::left->info.colSize = rand_num;

	Tree::right->info.rowSize = Tree::info.rowSize;
	Tree::right->info.colSize = Tree::info.colSize - Tree::left->info.colSize;

	for (int row = 0; row < Tree::info.rowSize; row++) {
		Tree::info.size[row][Tree::left->info.colSize - 1] = 1;
		Tree::info.size[row][Tree::left->info.colSize] = 1;
	}
	
	Tree::left->info.size = Tree::info.size;
	/*
	Tree::left->info.size = new int*[Tree::left->info.rowSize];
	for (int row = 0; row < Tree::left->info.rowSize; row++) {
		Tree::left->info.size[row] = new int[Tree::left->info.colSize];
		for (int col = 0; col < Tree::left->info.colSize; col++) {
			Tree::left->info.size[row][col] = 0;
		}
		Tree::left->info.size[row][0] = 1;
		Tree::left->info.size[row][Tree::left->info.colSize - 1] = 1;
	}
	for (int col = 0; col < Tree::left->info.colSize; col++) {
		Tree::left->info.size[0][col] = 1;
		Tree::left->info.size[Tree::left->info.rowSize - 1][col] = 1;
	}

	Tree::right->info.size = new int* [Tree::right->info.rowSize];
	for (int row = 0; row < Tree::right->info.rowSize; row++) {
		Tree::right->info.size[row] = new int[Tree::right->info.colSize];
		for (int col = 0; col < Tree::right->info.colSize; col++) {
			Tree::right->info.size[row][col] = 0;
		}
		Tree::right->info.size[row][0] = 1;
		Tree::right->info.size[row][Tree::right->info.colSize - 1] = 1;
	}
	for (int col = 0; col < Tree::right->info.colSize; col++) {
		Tree::right->info.size[0][col] = 1;
		Tree::right->info.size[Tree::left->info.rowSize - 1][col] = 1;
	}
	*/
}


void Tree::printRoom() {
	for (int row = 0; row < Tree::info.rowSize; row++) {
		for (int col = 0; col < Tree::info.colSize; col++) {
			cout << Tree::info.size[row][col];
		}
		cout << '\n';
	}
}