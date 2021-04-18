#pragma once

class D3DClass : public AlignedAllocationPolicy<16>
{
public:
	D3DClass();
	D3DClass(const D3DClass&);
	~D3DClass();

	bool Initialize(int, int, bool, HWND, bool, float, float);
	void Shutdown();

	void BeginScene(float, float, float, float);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(XMMATRIX&);
	void GetWorldMatrix(XMMATRIX&);
	void GetOrthoMatrix(XMMATRIX&);

	void GetVideoCardInfo(char*, int&);

	void TurnZBufferOn();
	void TurnZBufferOff();

private:
	bool m_vsync_enabled = false;
	int m_videoCardMemory = 0;
	char m_videoCardDescription[128] = { 0, };
	IDXGISwapChain* m_swapChain = nullptr;
	ID3D11Device* m_device = nullptr;
	ID3D11DeviceContext* m_deviceContext = nullptr;
	ID3D11RenderTargetView* m_renderTargetView = nullptr;
	ID3D11Texture2D* m_depthStencilBuffer = nullptr;
	ID3D11DepthStencilState* m_depthStencilState = nullptr;
	ID3D11DepthStencilView* m_depthStencilView = nullptr;
	ID3D11RasterizerState* m_rasterState = nullptr;
	XMMATRIX m_projectionMatrix;
	XMMATRIX m_worldMatrix;
	XMMATRIX m_orthoMatrix;
	ID3D11DepthStencilState* m_depthDisabledStencilState = nullptr;
};