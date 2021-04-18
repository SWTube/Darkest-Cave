#pragma once

class ModelClass : public AlignedAllocationPolicy<16>
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	void SetColor(XMFLOAT4);
	void SetMoveX(int x);

	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
	XMFLOAT4 m_color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	int moveX = 0;
	int m_vertexCount = 0;
	int m_indexCount = 0;
};