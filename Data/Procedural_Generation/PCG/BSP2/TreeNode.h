#pragma once

struct Info
{
	// 이진트리를 위한 방 번호
	int num;

	// 영역 정보
	int height;
	int width;
	int points_x; // x좌표
	int points_y; // y좌표

	// 방 정보
	int room_height;
	int room_width;
	int room_points_x; // x좌표
	int room_points_y; // y좌표

	int parent_devide_type; // 부모가 행과 열 중 어떤 기준으로 나뉘었는지 나타냄. 0이면 열, 1이면 행으로 나뉨.
};

class TreeNode {
private:
	TreeNode* leftNode;
	TreeNode* rightNode;
	TreeNode* parentNode;
	Info info;
public:
	void setRoot(int** _map, int _height, int _width);
	void devide_col(int** _map);
	void devide_row(int** _map);

	TreeNode* goRoot();
	TreeNode* goLeftNode();
	TreeNode* goRightNode();
	TreeNode* goRoom(int _num);

	int getHeight();
	int getWidth();
	int getX();
	int getY();

	int allocateRoom(int** _map);
	void connectRoom(int** _map, TreeNode* room1, TreeNode* room2);
	void connectRoom4(int** _map, TreeNode* room1, TreeNode* room2);
	void connectRoom_X(int** _map, TreeNode* room1, TreeNode* room2);
	void connectRoom_Y(int** _map, TreeNode* room1, TreeNode* room2);

	void devide(int** _map, int _numOfRoom);

	void printInfo();
	void printRoomInfo();
};
