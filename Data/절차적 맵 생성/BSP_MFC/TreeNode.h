#pragma once

struct Info
{
	// ¿µ¿ª Á¤º¸
	int height;
	int width;
	int points_x; // xÁÂÇ¥
	int points_y; // yÁÂÇ¥

	// ¹æ Á¤º¸
	int room_height;
	int room_width;
	int room_points_x; // xÁÂÇ¥
	int room_points_y; // yÁÂÇ¥

	int parent_devide_type; // ºÎ¸ð°¡ Çà°ú ¿­ Áß ¾î¶² ±âÁØÀ¸·Î ³ª´µ¾ú´ÂÁö ³ªÅ¸³¿. 0ÀÌ¸é ¿­, 1ÀÌ¸é ÇàÀ¸·Î ³ª´¸.
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

	int getHeight();
	int getWidth();
	int getX();
	int getY();

	void allocateRoom(int** _map);
	void connectRoom(int** _map, TreeNode* room1, TreeNode* room2);
	void connectRoom_X(int** _map, TreeNode* room1, TreeNode* room2);
	void connectRoom_Y(int** _map, TreeNode* room1, TreeNode* room2);

	void devide(int** _map, int _numOfRoom);

	void printInfo();
	void printRoomInfo();
};