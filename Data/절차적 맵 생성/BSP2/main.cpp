#include<iostream>
#include <random>
#include "TreeNode.h"

int main() {
	// 전체 맵 크기
	int maxHeight = 40;
	int maxWidth = 150;

	// 초기 맵 설정
	int** map = new int*[maxHeight];
	for (int i = 0; i < maxHeight; i++) {
		map[i] = new int[maxWidth];
		for (int j = 0; j < maxWidth; j++) {
			map[i][j] = 0;
		}
		map[i][0] = 1;
		map[i][maxWidth - 1] = 1;
	}
	for (int j = 0; j < maxWidth; j++) {
		map[0][j] = 1;
		map[maxHeight - 1][j] = 1;
	}

	// BSP 트리 초기화
	TreeNode root;
	root.setRoot(map, maxHeight, maxWidth);

	//root.devide(map, 9);

	
	// 맵 제작
	root.devide_col(map);
	root.goLeftNode()->devide_row(map);
	root.goRightNode()->devide_row(map);
	root.goLeftNode()->goLeftNode()->devide_col(map);
	root.goLeftNode()->goRightNode()->devide_col(map);
	root.goRightNode()->goLeftNode()->devide_col(map);
	root.goRightNode()->goRightNode()->devide_col(map);
	root.goRightNode()->goRightNode()->goRightNode()->devide_row(map);

	
	root.goLeftNode()->goLeftNode()->goLeftNode()->allocateRoom(map);
	root.goLeftNode()->goLeftNode()->goRightNode()->allocateRoom(map);
	root.goLeftNode()->goRightNode()->goLeftNode()->allocateRoom(map);
	root.goLeftNode()->goRightNode()->goRightNode()->allocateRoom(map);
	root.goRightNode()->goLeftNode()->goLeftNode()->allocateRoom(map);
	root.goRightNode()->goLeftNode()->goRightNode()->allocateRoom(map);
	root.goRightNode()->goRightNode()->goLeftNode()->allocateRoom(map);
	root.goRightNode()->goRightNode()->goRightNode()->goLeftNode()->allocateRoom(map);
	root.goRightNode()->goRightNode()->goRightNode()->goRightNode()->allocateRoom(map);

	root.connectRoom(map, root.goLeftNode()->goLeftNode()->goLeftNode(), root.goLeftNode()->goLeftNode()->goRightNode());
	root.connectRoom(map, root.goLeftNode()->goRightNode()->goLeftNode(), root.goLeftNode()->goRightNode()->goRightNode());
	root.connectRoom(map, root.goRightNode()->goLeftNode()->goLeftNode(), root.goRightNode()->goLeftNode()->goRightNode());
	root.connectRoom(map, root.goRightNode()->goRightNode()->goRightNode()->goLeftNode(), root.goRightNode()->goRightNode()->goRightNode()->goRightNode());

	root.connectRoom_Y(map, root.goLeftNode()->goLeftNode()->goLeftNode(), root.goLeftNode()->goRightNode()->goLeftNode());
	root.connectRoom_Y(map, root.goRightNode()->goLeftNode()->goLeftNode(), root.goRightNode()->goRightNode()->goLeftNode());
	root.connectRoom_X(map, root.goRightNode()->goRightNode()->goLeftNode(), root.goRightNode()->goRightNode()->goRightNode()->goLeftNode());
	root.connectRoom_X(map, root.goLeftNode()->goLeftNode()->goRightNode(), root.goRightNode()->goLeftNode()->goLeftNode());

	/*
	root.goLeftNode()->goLeftNode()->goLeftNode()->printInfo();
	root.goLeftNode()->goLeftNode()->goRightNode()->printInfo();
	root.goLeftNode()->goRightNode()->goLeftNode()->printInfo();
	root.goLeftNode()->goRightNode()->goRightNode()->printInfo();
	root.goRightNode()->goLeftNode()->goLeftNode7()->printInfo();
	root.goRightNode()->goLeftNode()->goRightNode()->printInfo();
	root.goRightNode()->goRightNode()->goLeftNode()->printInfo();
	root.goRightNode()->goRightNode()->goRightNode()->printInfo();
	*/
	// 맵 프린트
	for (int i = 0; i < maxHeight; i++) {
		for (int j = 0; j < maxWidth; j++) {
			if (map[i][j] == 2 || map[i][j] == 3) {
				std::cout << map[i][j];
			}
			else {
				std::cout << ' ';
			}
		}
		std::cout << std::endl;
	}


	// 맵 매모리 삭제
	for (int i = 0; i < maxHeight; i++) {
		delete map[i];
	}
	delete map;

	return 0;
}