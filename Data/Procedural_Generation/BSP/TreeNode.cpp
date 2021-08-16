#include<iostream>
#include<random>
#include"TreeNode.h"

void TreeNode::setRoot(int** _map, int _height, int _width) {
	this->info.height = _height;
	this->info.width = _width;
	this->info.points_x = 0;
	this->info.points_y= 0;

	// 자식, 부모 노드 초기화
	this->leftNode = NULL;
	this->rightNode = NULL;
	this->parentNode = NULL;
}

void TreeNode::devide_col(int** _map) {
	//균등 분포 정의 맵 크기의 30% ~ 70%
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(this->info.width * 3 / 10, this->info.width * 7 / 10);

	int _height = this->info.height;
	int _width = dis(gen);

	// 왼쪽 자식 노드 초기화
	this->leftNode = new TreeNode;
	this->leftNode->info.height = _height;
	this->leftNode->info.width = _width;
	this->leftNode->info.points_x = this->info.points_x;
	this->leftNode->info.points_y = this->info.points_y;
	this->leftNode->parentNode = this;
	this->leftNode->info.parent_devide_type = 0;

	// 오른쪽 자식 노드 초기화
	this->rightNode = new TreeNode;
	this->rightNode->info.height = this->info.height;
	this->rightNode->info.width = this->info.width - _width + 1;
	this->rightNode->info.points_x = this->info.points_x + _width - 1;
	this->rightNode->info.points_y = this->info.points_y;
	this->rightNode->parentNode = this;
	this->rightNode->info.parent_devide_type = 0;

	// 경계선 긋기
	for (int i = this->info.points_y + 1; i < this->info.points_y + this->info.height - 1; i++) {
		_map[i][this->info.points_x + _width - 1] = 1;
	}
}

void TreeNode::devide_row(int** _map) {
	//균등 분포 정의 맵 크기의 30% ~ 70%
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(this->info.height * 3 / 10, this->info.height * 7 / 10);
	
	int _height = dis(gen);
	int _width = this->info.width;

	// 왼쪽 자식 노드 초기화
	this->leftNode = new TreeNode;
	this->leftNode->info.height = _height + 1;
	this->leftNode->info.width = _width;
	this->leftNode->info.points_x = this->info.points_x;
	this->leftNode->info.points_y = this->info.points_y;
	this->leftNode->parentNode = this;
	this->leftNode->info.parent_devide_type = 1;

	// 오른쪽 자식 노드 초기화
	this->rightNode = new TreeNode;
	this->rightNode->info.height = this->info.height - _height;
	this->rightNode->info.width = this->info.width;
	this->rightNode->info.points_x = this->info.points_x;
	this->rightNode->info.points_y = this->info.points_y + _height;
	this->rightNode->parentNode = this;
	this->rightNode->info.parent_devide_type = 1;

	// 경계선 긋기
	for (int i = this->info.points_x; i < this->info.points_x + this->info.width; i++) {
		_map[this->info.points_y + _height][i] = 1;
	}
}

TreeNode* TreeNode::goLeftNode() {
	return this->leftNode;
}

TreeNode* TreeNode::goRightNode() {
	return this->rightNode;
}

int TreeNode::getHeight() {
	return this->info.height;
}
int TreeNode::getWidth() {
	return this->info.width;
}

int TreeNode::getX() {
	return this->info.points_x;
}
int TreeNode::getY() {
	return this->info.points_y;

}

void TreeNode::allocateRoom(int** _map) {
	// 벽에서 1,2,3칸 떨어짐
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(2,3);

	int start_h = this->info.points_y + dis(gen);
	int end_h = this->info.points_y + this->info.height - dis(gen);

	int start_w = this->info.points_x + dis(gen);
	int end_w = this->info.points_x + this->info.width - dis(gen);

	this->info.room_points_x = start_w;
	this->info.room_points_y = start_h;
	this->info.room_height = end_h - start_h;
	this->info.room_width = end_w - start_w;

	for (int i = start_h; i < end_h; i++) {
		for (int j = start_w; j < end_w; j++) {
			_map[i][j] = 2;
		}
	}
}

void TreeNode::connectRoom(int** _map, TreeNode* room1, TreeNode* room2) {
	if (room1->parentNode == room2->parentNode) {
		if (room1->info.parent_devide_type == 0) {
			// 겹치는 부분 찾기(Y좌표)
			int overlap_y_start;
			int overlap_y_end;
			for (int i = room2->info.room_points_y; i < room2->info.room_points_y + room2->info.room_height; i++) {
				if (i >= room1->info.room_points_y && i < room1->info.room_points_y + room1->info.room_height) {
					overlap_y_start = i;
					break;
				}
			}
			for (int i = overlap_y_start; i < room2->info.room_points_y + room2->info.room_height; i++) {
				if (i >= room1->info.room_points_y + room1->info.room_height) {
					overlap_y_end = i - 1;
					break;
				}
				overlap_y_end = i;
			}
			
			for (int i = room1->info.room_points_x + room1->info.room_width; i < room2->info.room_points_x; i++) {
				_map[(overlap_y_start + overlap_y_end) / 2 - 1][i] = 3;
				_map[(overlap_y_start + overlap_y_end) / 2][i] = 3;
				_map[(overlap_y_start + overlap_y_end) / 2 + 1][i] = 3;
			}
		}
		else {
			// 겹치는 부분 찾기(X좌표)
			int overlap_x_start;
			int overlap_x_end;
			for (int i = room2->info.room_points_x; i < room2->info.room_points_x + room2->info.room_width; i++) {
				if (i >= room1->info.room_points_x && i < room1->info.room_points_x + room1->info.room_width) {
					overlap_x_start = i;
					break;
				}
			}
			for (int i = overlap_x_start; i < room2->info.room_points_x + room2->info.room_width; i++) {
				if (i >= room1->info.room_points_x + room1->info.room_width) {
					overlap_x_end = i - 1;
					break;
				}
				overlap_x_end = i;
			}

			for (int i = room1->info.room_points_y + room1->info.room_height; i < room2->info.room_points_y; i++) {
				_map[i][(overlap_x_start + overlap_x_end) / 2 - 1] = 3;
				_map[i][(overlap_x_start + overlap_x_end) / 2] = 3;
				_map[i][(overlap_x_start + overlap_x_end) / 2 + 1] = 3;
			}
		}
	}
	else {
		// 부모들도 이어야 함
	}
}

void TreeNode::connectRoom_Y(int** _map, TreeNode* room1, TreeNode* room2) {
	// 겹치는 부분 찾기(X좌표)
	int overlap_x_start;
	int overlap_x_end;
	for (int i = room2->info.room_points_x; i < room2->info.room_points_x + room2->info.room_width; i++) {
		if (i >= room1->info.room_points_x && i < room1->info.room_points_x + room1->info.room_width) {
			overlap_x_start = i;
			break;
		}
	}
	for (int i = overlap_x_start; i < room2->info.room_points_x + room2->info.room_width; i++) {
		if (i >= room1->info.room_points_x + room1->info.room_width) {
			overlap_x_end = i - 1;
			break;
		}
		overlap_x_end = i;
	}

	for (int i = room1->info.room_points_y + room1->info.room_height; i < room2->info.room_points_y; i++) {
		_map[i][(overlap_x_start + overlap_x_end) / 2 - 1] = 3;
		_map[i][(overlap_x_start + overlap_x_end) / 2] = 3;
		_map[i][(overlap_x_start + overlap_x_end) / 2 + 1] = 3;
	}
}

void TreeNode::connectRoom_X(int** _map, TreeNode* room1, TreeNode* room2) {
	// 겹치는 부분 찾기(Y좌표)
	int overlap_y_start;
	int overlap_y_end;
	for (int i = room2->info.room_points_y; i < room2->info.room_points_y + room2->info.room_height; i++) {
		if (i >= room1->info.room_points_y && i < room1->info.room_points_y + room1->info.room_height) {
			overlap_y_start = i;
			break;
		}
	}
	for (int i = overlap_y_start; i < room2->info.room_points_y + room2->info.room_height; i++) {
		if (i >= room1->info.room_points_y + room1->info.room_height) {
			overlap_y_end = i - 1;
			break;
		}
		overlap_y_end = i;
	}

	for (int i = room1->info.room_points_x + room1->info.room_width; i < room2->info.room_points_x; i++) {
		_map[(overlap_y_start + overlap_y_end) / 2 - 1][i] = 3;
		_map[(overlap_y_start + overlap_y_end) / 2][i] = 3;
		_map[(overlap_y_start + overlap_y_end) / 2 + 1][i] = 3;
	}
}

// 각 방의 정보 프린트
void TreeNode::printInfo() {
	std::cout << "방 높이: " << this->info.height << std::endl;
	std::cout << "방 길이: " << this->info.width << std::endl;
	std::cout << "방 x좌표: " << this->info.points_x << std::endl;
	std::cout << "방 y좌표: " << this->info.points_y << std::endl;
	/*
	if (this->leftNode != NULL) {
		std::cout << "왼쪽 자식 방 높이: " << this->leftNode->info.height << std::endl;
		std::cout << "왼쪽 자식 방 길이: " << this->leftNode->info.width << std::endl;
		std::cout << "왼쪽 자식 방 x좌표: " << this->leftNode->info.points_x << std::endl;
		std::cout << "왼쪽 자식 방 y좌표: " << this->leftNode->info.points_y << std::endl;
	}
	
	if (this->rightNode != NULL) {
		std::cout << "오른쪽 자식 방 높이: " << this->rightNode->info.height << std::endl;
		std::cout << "오른쪽 자식 방 길이: " << this->rightNode->info.width << std::endl;
		std::cout << "오른쪽 자식 방 x좌표: " << this->rightNode->info.points_x << std::endl;
		std::cout << "오른쪽 자식 방 y좌표: " << this->rightNode->info.points_y << std::endl;
	}
	*/
}

// 각 할당된 방의 정보 프린트
void TreeNode::printRoomInfo() {
	std::cout << "할당된 방 높이: " << this->info.room_height << std::endl;
	std::cout << "할당된 방 길이: " << this->info.room_width << std::endl;
	std::cout << "할당된 방 x좌표: " << this->info.room_points_x << std::endl;
	std::cout << "할당된 방 y좌표: " << this->info.room_points_y << std::endl;
}