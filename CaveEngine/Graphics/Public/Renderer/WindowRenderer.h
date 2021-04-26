/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "CoreTypes.h"
#include "Device/DeviceResources.h"
#include "Renderer/GenericRenderer.h"

#ifdef __WIN32__
import DdsTextureLoader;

namespace cave
{
	class WindowRenderer final : public GenericRenderer
	{
	public:
		WindowRenderer() = delete;
		WindowRenderer(DeviceResources* deviceResources);
		WindowRenderer(const WindowRenderer&) = delete;
		WindowRenderer(const WindowRenderer&&) = delete;
		WindowRenderer& operator=(const WindowRenderer&) = delete;
		WindowRenderer& operator=(const WindowRenderer&&) = delete;
		~WindowRenderer();

		bool WindowShouldClose() override;

		void CreateDeviceDependentResources() override;
		void CreateWindowSizeDependentResources() override;
		void Update() override;
		void Render() override;
		void Destroy() override;

	private:
		int32_t createShaders() override;
		int32_t createCube() override;
		void createView() override;
		void createPerspective() override;

		void cleanupDevice();
		int32_t compileShaderFromFile(const wchar_t* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** blobOut);

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

		// Assert that the constant buffer remains 16-byte aligned.
		static_assert((sizeof(ConstantBufferNeverChanges) % 16) == 0, "Constant Buffer size must be 16-byte aligned");

		struct ConstantBufferChangeOnResize
		{
			DirectX::XMMATRIX mProjection;
		};

		// Assert that the constant buffer remains 16-byte aligned.
		static_assert((sizeof(ConstantBufferChangeOnResize) % 16) == 0, "Constant Buffer size must be 16-byte aligned");

		struct ConstantBufferChangesEveryFrame
		{
			DirectX::XMMATRIX mWorld;
			DirectX::XMFLOAT4 mMeshColor;
		};

		// Assert that the constant buffer remains 16-byte aligned.
		static_assert((sizeof(ConstantBufferChangesEveryFrame) % 16) == 0, "Constant Buffer size must be 16-byte aligned");

		//--------------------------------------------------------------------------------------
		// Global Variables
		//--------------------------------------------------------------------------------------
		ID3D11VertexShader*			mVertexShader = nullptr;
		ID3D11PixelShader*			mPixelShader = nullptr;
		ID3D11InputLayout*			mVertexLayout = nullptr;
		ID3D11Buffer*				mVertexBuffer = nullptr;
		ID3D11Buffer*				mIndexBuffer = nullptr;
		ID3D11Buffer*				mConstantBufferNeverChanges = nullptr;
		ID3D11Buffer*				mConstantBufferChangeOnResize = nullptr;
		ID3D11Buffer*				mConstantBufferChangesEveryFrame = nullptr;
		ID3D11ShaderResourceView*	mTextureRv = nullptr;
		ID3D11SamplerState*			mSamplerLinear = nullptr;
		DirectX::XMMATRIX			mWorld;
		DirectX::XMMATRIX			mView;
		DirectX::XMMATRIX			mProjection;
		DirectX::XMFLOAT4			mMeshColor = DirectX::XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
		// �ؽ�ó ������� �����Ƿ� shader resource view�� ������� ����

		//-----------------------------------------------------------------------------
		// Direct3D device resources
		//-----------------------------------------------------------------------------
		//ID3DXEffect* mEffect;
		ID3D11InputLayout* mInputLayoutExtended = nullptr;
	};

	typedef WindowRenderer Renderer;
}
#endif