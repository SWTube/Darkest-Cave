/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "CoreTypes.h"
#include "Renderer/GenericRenderer.h"

#ifdef __WIN32__
import DeviceResources;

namespace cave
{
	class WindowsRenderer final : public GenericRenderer
	{
	public:
		WindowsRenderer() = default;
		WindowsRenderer(const WindowsRenderer&) = delete;
		WindowsRenderer(const WindowsRenderer&&) = delete;
		WindowsRenderer& operator=(const WindowsRenderer&) = delete;
		WindowsRenderer& operator=(const WindowsRenderer&&) = delete;
		virtual ~WindowsRenderer();

		bool WindowShouldClose() override;

		virtual eResult Init(Window* window) override;
		eResult CreateDeviceDependentResources() override;
		eResult CreateWindowSizeDependentResources(Window* window = nullptr) override;
		void Update() override;
		void Render() override;
		void Destroy() override;

	private:
	

		DirectX::XMMATRIX	mView = DirectX::XMMatrixIdentity();
		DirectX::XMMATRIX	mProjection = DirectX::XMMatrixIdentity();
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