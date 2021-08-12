#include<iostream>
#include<random>
#include"TreeNode.h"

int minHeight = 2;
int minWidth = 2;

int numOfRoom;

void TreeNode::setRoot(int** _map, int _height, int _width) {
	this->info.height = _height;
	this->info.width = _width;
	this->info.points_x = 0;
	this->info.points_y= 0;

	// 자식, 부모 노드 초기화
	this->leftNode = NULL;
	this->rightNode = NULL;
	this->parentNode = NULL;

	// 방 개수 초기화
	numOfRoom = 1;

	// 방 번호 호기화
	this->info.num = 1;
}

void TreeNode::devide_col(int** _map) {
	//균등 분포 정의 맵 크기의 40% ~ 60%
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(this->info.width * 4 / 10, this->info.width * 6 / 10);

	int _height = this->info.height;
	int _width;
	do {
		_width = dis(gen);
	} while (_width < minWidth || (this->info.width - _width + 1) < minWidth);

	// 왼쪽 자식 노드 초기화
	this->leftNode = new TreeNode;
	this->leftNode->info.height = _height;
	this->leftNode->info.width = _width;
	this->leftNode->info.points_x = this->info.points_x;
	this->leftNode->info.points_y = this->info.points_y;
	this->leftNode->parentNode = this;
	this->leftNode->info.parent_devide_type = 0;
	this->leftNode->info.num = this->info.num * 2;

	this->leftNode->leftNode = NULL;
	this->leftNode->rightNode = NULL;

	// 오른쪽 자식 노드 초기화
	this->rightNode = new TreeNode;
	this->rightNode->info.height = this->info.height;
	this->rightNode->info.width = this->info.width - _width + 1;
	this->rightNode->info.points_x = this->info.points_x + _width - 1;
	this->rightNode->info.points_y = this->info.points_y;
	this->rightNode->parentNode = this;
	this->rightNode->info.parent_devide_type = 0;
	this->rightNode->info.num = this->info.num * 2 + 1;

	this->rightNode->leftNode = NULL;
	this->rightNode->rightNode = NULL;

	// 경계선 긋기
	for (int i = this->info.points_y + 1; i < this->info.points_y + this->info.height - 1; i++) {
		_map[i][this->info.points_x + _width - 1] = 1;
	}

	// 방개수 추가
	numOfRoom++;
}

void TreeNode::devide_row(int** _map) {
	//균등 분포 정의 맵 크기의 40% ~ 60%
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(this->info.height * 4 / 10, this->info.height * 6 / 10);
	
	int _height;
	do {
		_height = dis(gen);
	} while (_height < minHeight || (this->info.height - _height) < minHeight);
	int _width = this->info.width;

	// 왼쪽 자식 노드 초기화
	this->leftNode = new TreeNode;
	this->leftNode->info.height = _height + 1;
	this->leftNode->info.width = _width;
	this->leftNode->info.points_x = this->info.points_x;
	this->leftNode->info.points_y = this->info.points_y;
	this->leftNode->parentNode = this;
	this->leftNode->info.parent_devide_type = 1;
	this->leftNode->info.num = this->info.num * 2;

	this->leftNode->leftNode = NULL;
	this->leftNode->rightNode = NULL;

	// 오른쪽 자식 노드 초기화
	this->rightNode = new TreeNode;
	this->rightNode->info.height = this->info.height - _height;
	this->rightNode->info.width = this->info.width;
	this->rightNode->info.points_x = this->info.points_x;
	this->rightNode->info.points_y = this->info.points_y + _height;
	this->rightNode->parentNode = this;
	this->rightNode->info.parent_devide_type = 1;
	this->rightNode->info.num = this->info.num * 2 + 1;

	this->rightNode->leftNode = NULL;
	this->rightNode->rightNode = NULL;

	// 경계선 긋기
	for (int i = this->info.points_x; i < this->info.points_x + this->info.width; i++) {
		_map[this->info.points_y + _height][i] = 1;
	}

	// 방개수 추가
	numOfRoom++;
}

TreeNode* TreeNode::goRoot() {
	TreeNode* location = this;
	if (location->parentNode != NULL) {
		location = location->parentNode;
	}

	return location;
}

TreeNode* TreeNode::goRoom(int _num) {
	int __num = _num;
	int check = 0;

	while (__num != 1) {
		__num /= 2;
		check++;
	}

	int* loc = new int[check];

	for (int i = 0; _num != 1; i++) {
		if (_num % 2 == 0) {
			loc[i] = 0;
		}
		else {
			loc[i] = 1;
		}
		_num /= 2;
	}

	TreeNode* location = this->goRoot();

	for (int i = check - 1; i >= 0; i--) {
		if (loc[i] == 0) {
			location = location->leftNode;
		}
		else {
			location = location->rightNode;
		}
	}
	return location;
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

	//_map[start_h][start_w] = this->info.num;
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

void TreeNode::devide(int** _map, int _numOfRoom) {
	int i = 1;
	while (numOfRoom < _numOfRoom) {
		TreeNode* location = this->goRoom(i);
		if (location->info.parent_devide_type == 0) {
			location->devide_row(_map);
		}
		else {
			location->devide_col(_map);
		}
		i++;
	}

	for (int i = numOfRoom; i < 2 * numOfRoom; i++) {
		TreeNode* location = this->goRoom(i);
		if (location->leftNode == NULL || location->rightNode == NULL) {
			location->allocateRoom(_map);
		}
	}

	for (int i = numOfRoom; i < 2 * numOfRoom - 1; i++) {
		TreeNode* location1 = this->goRoom(i);
		TreeNode* location2 = this->goRoom(i + 1);
		this->connectRoom(_map, location1, location2);
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
