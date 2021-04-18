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

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

	void MoveObject(int index, float posX, float posY);
	bool AddBitmap(WCHAR* filename, int bitmapWidth = 200 , int bitmapHeight = 200);
	void ZoomInScreen();
	void ZoomOutScreen();

private:
	bool Render(float);

private:
	int m_screenWidth = 0;
	int m_screenHeight = 0;

	D3DClass* m_Direct3D = nullptr;
	CameraClass* m_Camera = nullptr;
	ModelClass* m_Model = nullptr;
	ModelClass* m_Model2 = nullptr;
	Squere* m_Squere = nullptr;
	BitmapClass* m_Bitmap = nullptr;

	std::vector<BitmapClass*> m_Bitmaps;

	ColorShaderClass* m_ColorShader = nullptr;
	TextureShaderClass* m_TextureShader = nullptr;
};