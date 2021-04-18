#pragma once
class TextureClass;

class Squere : public AlignedAllocationPolicy<16>
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 texture;
	};

public:
	Squere();
	Squere(const Squere&);
	~Squere();

	bool Initialize(ID3D11Device*,int screenWidth, int screenHeight, WCHAR* , int squereWidth ,int squereHeight);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, float, float);
	ID3D11ShaderResourceView* GetTexture();
	
	int GetIndexCount();

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
	TextureClass* m_Texture = nullptr;

	XMFLOAT4 m_color = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);
	int m_vertexCount = 0;
	int m_indexCount = 0;

	int m_screenWidth = 0;
	int m_screenHeight = 0;

	int m_bitmapWidth = 0;
	int m_bitmapHeight = 0;

	float m_previousPosX = 0.0f;
	float m_previousPosY = 0.0f;
};