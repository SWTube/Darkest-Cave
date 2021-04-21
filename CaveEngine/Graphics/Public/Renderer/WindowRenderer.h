/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "CoreTypes.h"
#include "Texture/DdsTextureLoader.h"

#ifdef __WIN32__
namespace cave
{
	class WindowRenderer final
	{
	public:
		WindowRenderer() = delete;
		WindowRenderer(const WindowRenderer&) = delete;
		WindowRenderer(const WindowRenderer&&) = delete;
		WindowRenderer& operator=(const WindowRenderer&) = delete;
		WindowRenderer& operator=(const WindowRenderer&&) = delete;
		~WindowRenderer() = default;

		static void Destroy();
		static int32_t Init(HINSTANCE hInstance, int32_t nCmdShow, const wchar_t* className, const wchar_t* windowName);
		static void Render();
		
	private:
		static void cleanupDevice();
		static int32_t compileShaderFromFile(const wchar_t* fileName, const wchar_t* entryPoint, const wchar_t* shaderModel, ID3DBlob** blobOut);
		static int32_t initWindow(HINSTANCE hInstance, int32_t nCmdShow, const wchar_t* className, const wchar_t* windowName);
		static int32_t initDevice();
		static LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);

		/**
		 * @brief Simple Vertex Structure, acts as the input to the Vertex Shader
		 * @details Contains position and texture coordinate
		 * @author Alegruz
		 * @version 0.0.1
		 * 
		 */
		struct SimpleVertex
		{
			DirectX::XMFLOAT3 mPosition;	/*!< Vertex position data */
			DirectX::XMFLOAT2 mTexCoord;	/*!< Vertex texture coordinate data */
		};

		struct ConstantBufferNeverChanges
		{
			DirectX::XMMATRIX mView;
		};

		struct ConstantBufferChangeOnResize
		{
			DirectX::XMMATRIX mProjection;
		};

		struct ConstantBufferChangesEveryFrame
		{
			DirectX::XMMATRIX mWorld;
			DirectX::XMFLOAT4 mvMeshColor;
		};

		//--------------------------------------------------------------------------------------
		// Global Variables
		//--------------------------------------------------------------------------------------
		static HINSTANCE					msHInstance;
		static HWND							msHWindow;
		static D3D_DRIVER_TYPE				msDriverType;
		static D3D_FEATURE_LEVEL			msFeatureLevel;
		static ID3D11Device*				msD3dDevice;
		static ID3D11Device1*				msD3dDevice1;
		static ID3D11DeviceContext*			msImmediateContext;
		static ID3D11DeviceContext1*		msImmediateContext1;
		static IDXGISwapChain*				msSwapChain;
		static IDXGISwapChain1*				msSwapChain1;
		static ID3D11RenderTarmsetView*		msRenderTargetView;
		static ID3D11Texture2D*				msDepthStencil;
		static ID3D11DepthStencilView*		msDepthStencilView;
		static ID3D11VertexShader*			msVertexShader;
		static ID3D11PixelShader*			msPixelShader;
		static ID3D11InputLayout*			msVertexLayout;
		static ID3D11Buffer*				msVertexBuffer;
		static ID3D11Buffer*				msIndexBuffer;
		static ID3D11Buffer*				msConstantBufferNeverChanges;
		static ID3D11Buffer*				msConstantBufferChangeOnResize;
		static ID3D11Buffer*				msConstantBufferChangesEveryFrame;
		static ID3D11ShaderResourceView*	msTextureRv;
		static ID3D11SamplerState*			msSamplerLinear;
		static DirectX::XMMATRIX			msWorld;
		static DirectX::XMMATRIX			msView;
		static DirectX::XMMATRIX			msProjection;
		static DirectX::XMFLOAT4			msMeshColor;
		// �ؽ�ó ������� �����Ƿ� shader resource view�� ������� ����
	}

	typedef WindowRenderer Renderer;
}
#endif