#pragma once

class TextureClass;

class BitmapClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

public:
	BitmapClass();
	BitmapClass(const BitmapClass&);
	~BitmapClass();

	bool Initialize(ID3D11Device*, int, int, WCHAR*, int, int);
	void Shutdown();
	bool Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();
	void SetPos(float x, float y);
	void Move(float x, float y);
	float GetPosX() const { return m_posX; }
	float GetPosY() const { return m_posY; }
	void SetTexture(TextureClass* texture) { m_Texture = texture;}
	bool HasTexture() { return (m_Texture != nullptr); }
	void SetTextureIndex(int i) { m_textureIndex = i; }
	int GetTextureIndex() { return m_textureIndex; }
	int GetWidth() { return m_bitmapWidth; }
	int GetHeight() { return m_bitmapHeight; }
	void GetBitmapSize(int& width, int& height) { width = m_bitmapWidth; height = m_bitmapHeight; }
	void SetBitmapSize(int width, int height) { m_bitmapWidth = width; m_bitmapHeight = height; isNeedUpdate = true; }

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(ID3D11DeviceContext*, float, float);
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

private:
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
	int m_vertexCount = 0;
	int m_indexCount = 0;
	TextureClass* m_Texture = nullptr;
	int m_screenWidth = 0;
	int m_screenHeight = 0;
	int m_bitmapWidth = 0;
	int m_bitmapHeight = 0;

	float m_posX = 0;
	float m_posY = 0;

	float m_previousPosX = 0;
	float m_previousPosY = 0;

	int m_textureIndex = 0;

	bool isNeedUpdate = false;
};