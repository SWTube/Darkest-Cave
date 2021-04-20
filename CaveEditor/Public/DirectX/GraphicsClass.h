#pragma once
#include <vector>
/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class D3DClass;
class CameraClass;
class ModelClass;
class ColorShaderClass;
class TextureShaderClass;
class Squere;
class BitmapClass;
class TextureClass;

class GraphicsClass
{
public:
	static GraphicsClass* GetInstance() {
		if (instance == nullptr) instance = new GraphicsClass();
		return instance;
	}
	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

	void MoveObject(int index, float posX, float posY);
	bool AddBitmap(WCHAR* filename, int bitmapWidth = 200 , int bitmapHeight = 200);
	void SetBitmapTexture(int objIndex,int texIndex);
	int GetBitmapTextureIndex(int index);
	void SetBitmapSize(int objIndex,int width, int height);
	void GetBitmapSize(int objIndex, int& width, int& hegiht);
	void ZoomInScreen();
	void ZoomOutScreen();
	void GetObjectPosition(int index, float& x, float& y);
private:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();
	bool Render(float);


private:
	static GraphicsClass* instance;
	int m_screenWidth = 0;
	int m_screenHeight = 0;

	D3DClass* m_Direct3D = nullptr;
	CameraClass* m_Camera = nullptr;
	ModelClass* m_Model = nullptr;
	Squere* m_Squere = nullptr;
	BitmapClass* m_Bitmap = nullptr;

	std::vector<BitmapClass*> m_Bitmaps;
	std::vector<TextureClass*> m_Textures;

	ColorShaderClass* m_ColorShader = nullptr;
	TextureShaderClass* m_TextureShader = nullptr;
};

