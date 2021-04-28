/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "GraphicsApiPch.h"

#include "CoreMinimal.h"
#include "Object/GenericDrawableObject.h"

#ifdef __WIN32__
namespace cave
{
	class WindowsDrawableObject final : public GenericDrawableObject
	{
	public:
		WindowsDrawableObject() = delete;
		WindowsDrawableObject(uint32_t verticesCount, Vertex*&& vertices, uint32_t indicesCount, uint8_t*&& indices);
		WindowsDrawableObject(uint32_t verticesCount, Vertex*&& vertices, uint32_t indicesCount, uint8_t*&& indices, const char* textureFilePath);
		WindowsDrawableObject(const WindowsDrawableObject& object);
		WindowsDrawableObject(const WindowsDrawableObject&& object);
		constexpr WindowsDrawableObject& operator=(const WindowsDrawableObject& object);
		constexpr WindowsDrawableObject& operator=(const WindowsDrawableObject&& object);
		virtual ~WindowsDrawableObject();

		eResult Init(ID3D11Device* device, ID3D11DeviceContext* context) override;
		eResult SetInputLayout(ID3DBlob* vsBlob);
		void Destroy() override;
		void Update() override;
		void Render() override;
	private:
		ID3D11Device* mDevice = nullptr;
		ID3D11DeviceContext* mContext = nullptr;
		ID3D11Buffer* mVertexBuffer = nullptr;
		ID3D11Buffer* mIndexBuffer = nullptr;
		ID3D11InputLayout* mVertexLayout = nullptr;
		ID3D11Buffer* mConstantBuffer = nullptr;
		ID3D11ShaderResourceView* mTextureRv = nullptr;
		ID3D11SamplerState* mSamplerLinear = nullptr;
	};

	typedef WindowsDrawableObject DrawableObject;
} // namespace cave
#endif