#include "pch.h"
#include<iostream>
#include<random>
#include"TreeNode.h"

int minHeight = 1;
int minWidth = 1;

int numOfRoom;

int* room_queue;
int index = 0;

void TreeNode::setRoot(int** _map, int _height, int _width) {
	this->info.height = _height;
	this->info.width = _width;
	this->info.points_x = 0;
	this->info.points_y = 0;

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

int TreeNode::allocateRoom(int** _map) {
	// 벽에서 1,2,3칸 떨어짐
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(6, 6);

	int start_h = this->info.points_y + dis(gen);
	int end_h = this->info.points_y + this->info.height - dis(gen);

	int start_w = this->info.points_x + dis(gen);
	int end_w = this->info.points_x + this->info.width - dis(gen);

	this->info.room_points_x = start_w;
	this->info.room_points_y = start_h;
	this->info.room_height = end_h - start_h;
	this->info.room_width = end_w - start_w;

	std::uniform_int_distribution<int> dis2(1, 10);
	if (dis2(gen) == 1 || dis2(gen) == 2 || dis2(gen) == 3) {
		for (int i = start_h; i < end_h; i++) {
			for (int j = start_w; j < end_w; j++) {
				_map[i][j] = 4;
			}
		}
		//_map[start_h][start_w] = this->info.num;
		return 0;
	}
	else {
		for (int i = start_h; i < end_h; i++) {
			for (int j = start_w; j < end_w; j++) {
				if (dis2(gen) == 1)
					_map[i][j] = 4;
				else
					_map[i][j] = 2;
			}
		}
		//_map[start_h][start_w] = this->info.num;
		return 1;
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
		// 부모들도 이어야 함 -> connectRoom4
	}
}

void TreeNode::connectRoom4(int** _map, TreeNode* room1, TreeNode* room2) {
	// 부모들도 이어야 함

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, 2);
	// 2개의 방의 통로 유형은 총 4가지로 규정

	int x1, x2, y1, y2, w1, w2, h1, h2, choice;

	choice = dis(gen); // 4가지 길 중 랜덤 선택

	if (room1->info.room_points_x <= room2->info.room_points_x && room1->info.room_points_y >= room2->info.room_points_y) { // 1, 3 분면에 위치한 경우
		x1 = room1->info.room_points_x;
		x2 = room2->info.room_points_x;
		y1 = room1->info.room_points_y;
		y2 = room2->info.room_points_y;
		w1 = room1->info.room_width;
		w2 = room2->info.room_width;
		h1 = room1->info.room_height;
		h2 = room2->info.room_height;

		if (choice == 1) { // 위쪽, 왼쪽
			if (y1 <= (y2 + h2)) {
				std::uniform_int_distribution<int> dis2(0, std::abs(w1 - 1));
				std::uniform_int_distribution<int> dis3(0, std::abs(y2 - y1));

				int start_x = x1 + dis2(gen);
				int start_y = y1;
				int end_x = x2;
				int end_y = y2 + dis3(gen);

				for (int y = start_y; y >= end_y; y--) {
					if (_map[y][start_x] != 2)
						_map[y][start_x] = 3;
				}

				for (int x = start_x; x <= end_x; x++) {
					if (_map[end_y][x] != 2)
						_map[end_y][x] = 3;
				}
			}
			else if (x2 <= (x1 + w1)) {
				std::uniform_int_distribution<int> dis2(0, std::abs(x2 - x1));
				std::uniform_int_distribution<int> dis3(0, std::abs(h2 - 1));

				int start_x = x1 + dis2(gen);
				int start_y = y1;
				int end_x = x2;
				int end_y = y2 + dis3(gen);

				for (int y = start_y; y >= end_y; y--) {
					if (_map[y][start_x] != 2)
						_map[y][start_x] = 3;
				}

				for (int x = start_x; x <= end_x; x++) {
					if (_map[end_y][x] != 2)
						_map[end_y][x] = 3;
				}
			}
			else {
				std::uniform_int_distribution<int> dis2(0, std::abs(w1 - 1));
				std::uniform_int_distribution<int> dis3(0, std::abs(h2 - 1));

				int start_x = x1 + dis2(gen);
				int start_y = y1;
				int end_x = x2;
				int end_y = y2 + dis3(gen);

				for (int y = start_y; y >= end_y; y--) {
					if (_map[y][start_x] != 2)
						_map[y][start_x] = 3;
				}

				for (int x = start_x; x <= end_x; x++) {
					if (_map[end_y][x] != 2)
						_map[end_y][x] = 3;
				}
			}
		}
		else if (choice == 2) { // 위쪽, 아래쪽
			if (y1 <= (y2 + h2)) {
				std::uniform_int_distribution<int> dis2(0, std::abs(w1 - 1));
				std::uniform_int_distribution<int> dis3(0, std::abs(w2 - 1));
				int start_x = x1 + dis2(gen);
				int start_y = y1;
				int end_x = x2 + dis3(gen);
				int end_y = y2 + h2;
				std::uniform_int_distribution<int> dis4(0, 0); // 꺾이는 위치 랜덤으로 구하기
				std::uniform_int_distribution<int> dis5(0, std::abs(x2 - x1 - w1));
				int middle_y_1 = start_y - dis4(gen);
				if (middle_y_1 < 0) {
					middle_y_1 = start_y - dis4(gen);
				}
				int middle_y_2 = end_y + dis4(gen);
				int middle_x = x1 + w1 + dis5(gen);

				for (int y = start_y; y >= middle_y_1; y--) {
					if (_map[y][start_x] != 2)
						_map[y][start_x] = 3;
				}

				for (int x = start_x; x <= middle_x; x++) {
					if (_map[middle_y_1][x] != 2)
						_map[middle_y_1][x] = 3;
				}

				for (int y = middle_y_1; y <= middle_y_2; y++) {
					if (_map[y][middle_x] != 2)
						_map[y][middle_x] = 3;
				}

				for (int x = middle_x; x <= end_x; x++) {
					if (_map[middle_y_2][x] != 2)
						_map[middle_y_2][x] = 3;
				}

				for (int y = middle_y_2; y >= end_y; y--) {
					if (_map[y][end_x] != 2)
						_map[y][end_x] = 3;
				}
			}
			else {
				std::uniform_int_distribution<int> dis2(0, std::abs(w1 - 1));
				std::uniform_int_distribution<int> dis3(0, std::abs(w2 - 1));
				int start_x = x1 + dis2(gen);
				int start_y = y1;
				int end_x = x2 + dis3(gen);
				int end_y = y2 + h2;
				std::uniform_int_distribution<int> dis4(0, start_y - end_y); // 꺾이는 위치 랜덤으로 구하기
				int middle_y = end_y + dis4(gen);

				for (int y = start_y; y >= middle_y; y--) {
					if (_map[y][start_x] != 2)
						_map[y][start_x] = 3;
				}

				for (int x = start_x; x <= end_x; x++) {
					if (_map[middle_y][x] != 2)
						_map[middle_y][x] = 3;
				}

				for (int y = middle_y; y >= end_y; y--) {
					if (_map[y][end_x] != 2)
						_map[y][end_x] = 3;
				}
			}
		}
		else if (choice == 3) { // 오른쪽, 왼쪽
			if (x2 <= (x1 + w1)) {
				std::uniform_int_distribution<int> dis2(0, std::abs(h1 - 1));
				std::uniform_int_distribution<int> dis3(0, std::abs(h2 - 1));
				int start_x = x1 + w1;
				int start_y = y1 + dis2(gen);
				int end_x = x2;
				int end_y = y2 + dis3(gen);
				std::uniform_int_distribution<int> dis4(0, 0); // 꺾이는 위치 랜덤으로 구하기
				int middle_x_1 = start_x + dis4(gen);
				int middle_x_2 = end_x - dis4(gen);

				std::uniform_int_distribution<int> dis5(0, std::abs(y1 - y2 - h2));
				int middle_y = y2 + h2 + 0;

				for (int x = start_x; x <= middle_x_1; x++) {
					if (_map[start_y][x] != 2)
						_map[start_y][x] = 3;
				}

				for (int y = start_y; y >= middle_y; y--) {
					if (_map[y][middle_x_1] != 2)
						_map[y][middle_x_1] = 3;
				}

				for (int x = middle_x_1; x >= middle_x_2; x--) {
					if (_map[middle_y][x] != 2)
						_map[middle_y][x] = 3;
				}

				for (int y = middle_y; y >= end_y; y--) {
					if (_map[y][middle_x_2] != 2)
						_map[y][middle_x_2] = 3;
				}

				for (int x = middle_x_2; x <= end_x; x++) {
					if (_map[end_y][x] != 2)
						_map[end_y][x] = 3;
				}
			}
			else {
				std::uniform_int_distribution<int> dis2(0, h1 - 1);
				std::uniform_int_distribution<int> dis3(0, h2 - 1);
				int start_x = x1 + w1;
				int start_y = y1 + dis2(gen);
				int end_x = x2;
				int end_y = y2 + dis3(gen);
				std::uniform_int_distribution<int> dis4(0, end_x - start_x); // 꺾이는 위치 랜덤으로 구하기
				int middle_x = start_x + dis4(gen);

				for (int x = start_x; x <= middle_x; x++) {
					if (_map[start_y][x] != 2)
						_map[start_y][x] = 3;
				}

				for (int y = start_y; y >= end_y; y--) {
					if (_map[y][middle_x] != 2)
						_map[y][middle_x] = 3;
				}

				for (int x = middle_x; x <= end_x; x++) {
					if (_map[end_y][x] != 2)
						_map[end_y][x] = 3;
				}
			}
		}
		else if (choice == 4) { // 오른쪽, 아래쪽
			std::uniform_int_distribution<int> dis2(0, h1 - 1);
			std::uniform_int_distribution<int> dis3(0, w2 - 1);
			int start_x = x1 + w1;
			int start_y = y1 + dis2(gen);
			int end_x = x2 + dis3(gen);
			int end_y = y2 + h2;

			for (int x = start_x; x <= end_x; x++) {
				if (_map[start_y][x] != 2)
					_map[start_y][x] = 3;
			}

			for (int y = start_y; y >= end_y; y--) {
				if (_map[y][end_x] != 2)
					_map[y][end_x] = 3;
			}
		}
	}
	if (room1->info.room_points_x <= room2->info.room_points_x && room1->info.room_points_y < room2->info.room_points_y) { // 2, 4 분면에 위치한 경우
		x1 = room1->info.room_points_x;
		x2 = room2->info.room_points_x;
		y1 = room1->info.room_points_y;
		y2 = room2->info.room_points_y;
		w1 = room1->info.room_width;
		w2 = room2->info.room_width;
		h1 = room1->info.room_height;
		h2 = room2->info.room_height;

		if (choice == 1) { // 아래쪽, 왼쪽
			if (y1 <= (y2 + h2)) {
				std::uniform_int_distribution<int> dis2(0, std::abs(w1 - 1));
				std::uniform_int_distribution<int> dis3(0, std::abs(y2 - y1));

				int start_x = x1 + dis2(gen);
				int start_y = y1;
				int end_x = x2;
				int end_y = y2 + dis3(gen);

				for (int y = start_y; y >= end_y; y--) {
					if (_map[y][start_x] != 2)
						_map[y][start_x] = 3;
				}

				for (int x = start_x; x <= end_x; x++) {
					if (_map[end_y][x] != 2)
						_map[end_y][x] = 3;
				}
			}
			else if (x2 <= (x1 + w1)) {
				std::uniform_int_distribution<int> dis2(0, std::abs(x2 - x1));
				std::uniform_int_distribution<int> dis3(0, std::abs(h2 - 1));

				int start_x = x1 + dis2(gen);
				int start_y = y1;
				int end_x = x2;
				int end_y = y2 + dis3(gen);

				for (int y = start_y; y >= end_y; y--) {
					if (_map[y][start_x] != 2)
						_map[y][start_x] = 3;
				}

				for (int x = start_x; x <= end_x; x++) {
					if (_map[end_y][x] != 2)
						_map[end_y][x] = 3;
				}
			}
			else {
				std::uniform_int_distribution<int> dis2(0, std::abs(w1 - 1));
				std::uniform_int_distribution<int> dis3(0, std::abs(h2 - 1));

				int start_x = x1 + dis2(gen);
				int start_y = y1;
				int end_x = x2;
				int end_y = y2 + dis3(gen);

				for (int y = start_y; y >= end_y; y--) {
					if (_map[y][start_x] != 2)
						_map[y][start_x] = 3;
				}

				for (int x = start_x; x <= end_x; x++) {
					if (_map[end_y][x] != 2)
						_map[end_y][x] = 3;
				}
			}
		}
		else if (choice == 2) { // 아래쪽, 위쪽
			if (y1 <= (y2 + h2)) {
				std::uniform_int_distribution<int> dis2(0, std::abs(w1 - 1));
				std::uniform_int_distribution<int> dis3(0, std::abs(w2 - 1));
				int start_x = x1 + dis2(gen);
				int start_y = y1;
				int end_x = x2 + dis3(gen);
				int end_y = y2 + h2;
				std::uniform_int_distribution<int> dis4(0, 0); // 꺾이는 위치 랜덤으로 구하기
				std::uniform_int_distribution<int> dis5(0, std::abs(x2 - x1 - w1));
				int middle_y_1 = start_y - dis4(gen);
				if (middle_y_1 < 0) {
					middle_y_1 = start_y - dis4(gen);
				}
				int middle_y_2 = end_y + dis4(gen);
				int middle_x = x1 + w1 + dis5(gen);

				for (int y = start_y; y >= middle_y_1; y--) {
					if (_map[y][start_x] != 2)
						_map[y][start_x] = 3;
				}

				for (int x = start_x; x <= middle_x; x++) {
					if (_map[middle_y_1][x] != 2)
						_map[middle_y_1][x] = 3;
				}

				for (int y = middle_y_1; y <= middle_y_2; y++) {
					if (_map[y][middle_x] != 2)
						_map[y][middle_x] = 3;
				}

				for (int x = middle_x; x <= end_x; x++) {
					if (_map[middle_y_2][x] != 2)
						_map[middle_y_2][x] = 3;
				}

				for (int y = middle_y_2; y >= end_y; y--) {
					if (_map[y][end_x] != 2)
						_map[y][end_x] = 3;
				}
			}
			else {
				std::uniform_int_distribution<int> dis2(0, std::abs(w1 - 1));
				std::uniform_int_distribution<int> dis3(0, std::abs(w2 - 1));
				int start_x = x1 + dis2(gen);
				int start_y = y1;
				int end_x = x2 + dis3(gen);
				int end_y = y2 + h2;
				std::uniform_int_distribution<int> dis4(0, start_y - end_y); // 꺾이는 위치 랜덤으로 구하기
				int middle_y = end_y + dis4(gen);

				for (int y = start_y; y >= middle_y; y--) {
					if (_map[y][start_x] != 2)
						_map[y][start_x] = 3;
				}

				for (int x = start_x; x <= end_x; x++) {
					if (_map[middle_y][x] != 2)
						_map[middle_y][x] = 3;
				}

				for (int y = middle_y; y >= end_y; y--) {
					if (_map[y][end_x] != 2)
						_map[y][end_x] = 3;
				}
			}
		}
		else if (choice == 3) { // 오른쪽, 왼쪽
			if (x2 <= (x1 + w1)) {
				std::uniform_int_distribution<int> dis2(0, std::abs(h1 - 1));
				std::uniform_int_distribution<int> dis3(0, std::abs(h2 - 1));
				int start_x = x1 + w1;
				int start_y = y1 + dis2(gen);
				int end_x = x2;
				int end_y = y2 + dis3(gen);
				std::uniform_int_distribution<int> dis4(0, 0); // 꺾이는 위치 랜덤으로 구하기
				int middle_x_1 = start_x + dis4(gen);
				int middle_x_2 = end_x - dis4(gen);

				std::uniform_int_distribution<int> dis5(0, std::abs(y2 - y1 - h1));
				int middle_y = y1 + h1 + dis5(gen);

				for (int x = start_x; x <= middle_x_1; x++) {
					if (_map[start_y][x] != 2)
						_map[start_y][x] = 3;
				}

				for (int y = start_y; y <= middle_y; y++) {
					if (_map[y][middle_x_1] != 2)
						_map[y][middle_x_1] = 3;
				}

				for (int x = middle_x_1; x >= middle_x_2; x--) {
					if (_map[middle_y][x] != 2)
						_map[middle_y][x] = 3;
				}

				for (int y = middle_y; y <= end_y; y++) {
					if (_map[y][middle_x_2] != 2)
						_map[y][middle_x_2] = 3;
				}

				for (int x = middle_x_2; x <= end_x; x++) {
					if (_map[end_y][x] != 2)
						_map[end_y][x] = 3;
				}
			}
			else {
				std::uniform_int_distribution<int> dis2(0, h1 - 1);
				std::uniform_int_distribution<int> dis3(0, h2 - 1);
				int start_x = x1 + w1;
				int start_y = y1 + dis2(gen);
				int end_x = x2;
				int end_y = y2 + dis3(gen);
				std::uniform_int_distribution<int> dis4(0, end_x - start_x); // 꺾이는 위치 랜덤으로 구하기
				int middle_x = start_x + dis4(gen);

				for (int x = start_x; x <= middle_x; x++) {
					if (_map[start_y][x] != 2)
						_map[start_y][x] = 3;
				}

				for (int y = start_y; y <= end_y; y++) {
					if (_map[y][middle_x] != 2)
						_map[y][middle_x] = 3;
				}

				for (int x = middle_x; x <= end_x; x++) {
					if (_map[end_y][x] != 2)
						_map[end_y][x] = 3;
				}
			}
		}
		else if (choice == 4) { // 오른쪽, 위쪽
			std::uniform_int_distribution<int> dis2(0, h1 - 1);
			std::uniform_int_distribution<int> dis3(0, w2 - 1);
			int start_x = x1 + w1;
			int start_y = y1 + dis2(gen);
			int end_x = x2 + dis3(gen);
			int end_y = y2;

			for (int x = start_x; x <= end_x; x++) {
				if (_map[start_y][x] != 2)
					_map[start_y][x] = 3;
			}

			for (int y = start_y; y <= end_y; y++) {
				if (_map[y][end_x] != 2)
					_map[y][end_x] = 3;
			}
		}
	}

	if (room1->info.room_points_x >= room2->info.room_points_x && room1->info.room_points_y <= room2->info.room_points_y) { // 3, 1 분면에 위치한 경우
		x1 = room2->info.room_points_x;
		x2 = room1->info.room_points_x;
		y1 = room2->info.room_points_y;
		y2 = room1->info.room_points_y;
		w1 = room2->info.room_width;
		w2 = room1->info.room_width;
		h1 = room2->info.room_height;
		h2 = room1->info.room_height;

		if (choice == 1) { // 위쪽, 왼쪽
			std::uniform_int_distribution<int> dis2(0, w1 - 1);
			std::uniform_int_distribution<int> dis3(0, h2 - 1);
			int start_x = x1 + dis2(gen);
			int start_y = y1;
			int end_x = x2;
			int end_y = y2 + dis3(gen);

			for (int y = start_y; y >= end_y; y--) {
				if (_map[y][start_x] != 2)
					_map[y][start_x] = 3;
			}

			for (int x = start_x; x <= end_x; x++) {
				if (_map[end_y][x] != 2)
					_map[end_y][x] = 3;
			}

		}
		else if (choice == 2) { // 위쪽, 아래쪽
			std::uniform_int_distribution<int> dis2(0, w1 - 1);
			std::uniform_int_distribution<int> dis3(0, w2 - 1);
			int start_x = x1 + dis2(gen);
			int start_y = y1;
			int end_x = x2 + dis3(gen);
			int end_y = y2 + h2;
			std::uniform_int_distribution<int> dis4(0, start_y - end_y); // 꺾이는 위치 랜덤으로 구하기
			int middle_y = end_y + dis4(gen);

			for (int y = start_y; y >= middle_y; y--) {
				if (_map[y][start_x] != 2)
					_map[y][start_x] = 3;
			}

			for (int x = start_x; x <= end_x; x++) {
				if (_map[middle_y][x] != 2)
					_map[middle_y][x] = 3;
			}

			for (int y = middle_y; y >= end_y; y--) {
				if (_map[y][end_x] != 2)
					_map[y][end_x] = 3;
			}
		}
		else if (choice == 3) { // 오른쪽, 왼쪽
			std::uniform_int_distribution<int> dis2(0, h1 - 1);
			std::uniform_int_distribution<int> dis3(0, h2 - 1);
			int start_x = x1 + w1;
			int start_y = y1 + dis2(gen);
			int end_x = x2;
			int end_y = y2 + dis3(gen);
			std::uniform_int_distribution<int> dis4(0, end_x - start_x); // 꺾이는 위치 랜덤으로 구하기
			int middle_x = start_x + dis4(gen);

			for (int x = start_x; x <= middle_x; x++) {
				if (_map[start_y][x] != 2)
					_map[start_y][x] = 3;
			}

			for (int y = start_y; y >= end_y; y--) {
				if (_map[y][middle_x] != 2)
					_map[y][middle_x] = 3;
			}

			for (int x = middle_x; x <= end_x; x++) {
				if (_map[end_y][x] != 2)
					_map[end_y][x] = 3;
			}
		}
		else if (choice == 4) { // 오른쪽, 아래쪽
			std::uniform_int_distribution<int> dis2(0, h1 - 1);
			std::uniform_int_distribution<int> dis3(0, w2 - 1);
			int start_x = x1 + w1;
			int start_y = y1 + dis2(gen);
			int end_x = x2 + dis3(gen);
			int end_y = y2 + h2;

			for (int x = start_x; x <= end_x; x++) {
				if (_map[start_y][x] != 2)
					_map[start_y][x] = 3;
			}

			for (int y = start_y; y >= end_y; y--) {
				if (_map[y][end_x] != 2)
					_map[y][end_x] = 3;
			}
		}
	}
	if (room1->info.room_points_x >= room2->info.room_points_x && room1->info.room_points_y > room2->info.room_points_y) { // 4, 2 분면에 위치한 경우
		x1 = room2->info.room_points_x;
		x2 = room1->info.room_points_x;
		y1 = room2->info.room_points_y;
		y2 = room1->info.room_points_y;
		w1 = room2->info.room_width;
		w2 = room1->info.room_width;
		h1 = room2->info.room_height;
		h2 = room1->info.room_height;

		if (choice == 1) { // 아래쪽, 왼쪽
			std::uniform_int_distribution<int> dis2(0, w1 - 1);
			std::uniform_int_distribution<int> dis3(0, h2 - 1);
			int start_x = x1 + dis2(gen);
			int start_y = y1 + h1;
			int end_x = x2;
			int end_y = y2 + dis3(gen);

			for (int y = start_y; y <= end_y; y++) {
				if (_map[y][start_x] != 2)
					_map[y][start_x] = 3;
			}

			for (int x = start_x; x <= end_x; x++) {
				if (_map[end_y][x] != 2)
					_map[end_y][x] = 3;
			}

		}
		else if (choice == 2) { // 아래쪽, 위쪽
			std::uniform_int_distribution<int> dis2(0, w1 - 1);
			std::uniform_int_distribution<int> dis3(0, w2 - 1);
			int start_x = x1 + dis2(gen);
			int start_y = y1 + h1;
			int end_x = x2 + dis3(gen);
			int end_y = y2;
			std::uniform_int_distribution<int> dis4(0, end_y - start_y); // 꺾이는 위치 랜덤으로 구하기
			int middle_y = start_y + dis4(gen);

			for (int y = start_y; y <= middle_y; y++) {
				if (_map[y][start_x] != 2)
					_map[y][start_x] = 3;
			}

			for (int x = start_x; x <= end_x; x++) {
				if (_map[middle_y][x] != 2)
					_map[middle_y][x] = 3;
			}

			for (int y = middle_y; y <= end_y; y++) {
				if (_map[y][end_x] != 2)
					_map[y][end_x] = 3;
			}
		}
		else if (choice == 3) { // 오른쪽, 왼쪽
			std::uniform_int_distribution<int> dis2(0, h1 - 1);
			std::uniform_int_distribution<int> dis3(0, h2 - 1);
			int start_x = x1 + w1;
			int start_y = y1 + dis2(gen);
			int end_x = x2;
			int end_y = y2 + dis3(gen);
			std::uniform_int_distribution<int> dis4(0, end_x - start_x); // 꺾이는 위치 랜덤으로 구하기
			int middle_x = start_x + dis4(gen);

			for (int x = start_x; x <= middle_x; x++) {
				if (_map[start_y][x] != 2)
					_map[start_y][x] = 3;
			}

			for (int y = start_y; y <= end_y; y++) {
				if (_map[y][middle_x] != 2)
					_map[y][middle_x] = 3;
			}

			for (int x = middle_x; x <= end_x; x++) {
				if (_map[end_y][x] != 2)
					_map[end_y][x] = 3;
			}
		}
		else if (choice == 4) { // 오른쪽, 위쪽
			std::uniform_int_distribution<int> dis2(0, h1 - 1);
			std::uniform_int_distribution<int> dis3(0, w2 - 1);
			int start_x = x1 + w1;
			int start_y = y1 + dis2(gen);
			int end_x = x2 + dis3(gen);
			int end_y = y2;

			for (int x = start_x; x <= end_x; x++) {
				if (_map[start_y][x] != 2)
					_map[start_y][x] = 3;
			}

			for (int y = start_y; y <= end_y; y++) {
				if (_map[y][end_x] != 2)
					_map[y][end_x] = 3;
			}
		}
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

	room_queue = new int[_numOfRoom];

	for (int i = numOfRoom; i < 2 * numOfRoom; i++) {
		TreeNode* location = this->goRoom(i);
		if (location->leftNode == NULL || location->rightNode == NULL) {
			if (location->allocateRoom(_map) == 1) {
				room_queue[index] = location->info.num;
				index++;
			}
		}
	}

	for (int i = numOfRoom; i < 2 * numOfRoom - 1; i++) {
		TreeNode* location1 = this->goRoom(i);
		TreeNode* location2 = this->goRoom(i + 1);

	}

	/*
	for (int i = 0; i < index; i++) {
		std::cout << room_queue[i] << std::endl;
	}
	*/


	for (int i = 0; i < index - 1; i++) {
		//std::cout << room_queue[i] << std::endl;
		this->connectRoom4(_map, this->goRoom(room_queue[i]), this->goRoom(room_queue[i + 1]));
	}


	//std::cout << index << std::endl;

	//this->connectRoom4(_map, this->goRoom(4), this->goRoom(5));
	//this->connectRoom4(_map, this->goRoom(5), this->goRoom(6));
	//this->connectRoom4(_map, this->goRoom(6), this->goRoom(7));

	//this->connectRoom4(_map, this->goRoom(4), this->goRoom(7));

	//this->connectRoom(_map, this->goRoom(65), this->goRoom(66));

	/*
	for (int i = numOfRoom; i < 2 * numOfRoom - 1; i++) {
		TreeNode* location1 = this->goRoom(i);
		TreeNode* location2 = this->goRoom(i + 1);
		this->connectRoom(_map, location1, location2);
	}
	*/
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
