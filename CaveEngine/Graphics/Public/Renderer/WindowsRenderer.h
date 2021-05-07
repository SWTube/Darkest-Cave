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
	class WindowsRenderer final : public GenericRenderer
	{
	public:
		WindowsRenderer() = delete;
		WindowsRenderer(DeviceResources* deviceResources);
		WindowsRenderer(const WindowsRenderer&) = delete;
		WindowsRenderer(const WindowsRenderer&&) = delete;
		WindowsRenderer& operator=(const WindowsRenderer&) = delete;
		WindowsRenderer& operator=(const WindowsRenderer&&) = delete;
		~WindowsRenderer();

		bool WindowShouldClose() override;

		void CreateDeviceDependentResources() override;
		void CreateWindowSizeDependentResources() override;
		void Update() override;
		void Render() override;
		void Destroy() override;

	private:
		eResult createShader(Shader& shader) override;
		eResult createShaders() override;
		eResult createObject(Sprite& object) override;
		eResult createObjects() override;
		void createView() override;
		void createPerspective() override;

		void cleanupDevice();

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

		//--------------------------------------------------------------------------------------
		// Global Variables
		//--------------------------------------------------------------------------------------
		
		ID3D11Buffer*				mConstantBufferNeverChanges = nullptr;
		ID3D11Buffer*				mConstantBufferChangeOnResize = nullptr;
		
		DirectX::XMMATRIX			mView;
		DirectX::XMMATRIX			mProjection;
		// �ؽ�ó ������� �����Ƿ� shader resource view�� ������� ����

		//-----------------------------------------------------------------------------
		// Direct3D device resources
		//-----------------------------------------------------------------------------
		//ID3DXEffect* mEffect;
		ID3D11InputLayout* mInputLayoutExtended = nullptr;
	};

	typedef WindowsRenderer Renderer;
}
#endif