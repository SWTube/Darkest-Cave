/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "GraphicsApiPch.h"

#include "CoreMinimal.h"
#include "Sprite/GenericSprite.h"

#ifdef __WIN32__
namespace cave
{
	class WindowsSprite final : public GenericSprite
	{
	public:
		WindowsSprite() = delete;
		WindowsSprite(uint32_t verticesCount, Vertex*&& vertices, uint32_t indicesCount, uint8_t*&& indices);
		WindowsSprite(uint32_t verticesCount, Vertex*&& vertices, uint32_t indicesCount, uint8_t*&& indices, const char* textureFilePath);
		WindowsSprite(const WindowsSprite& object);
		WindowsSprite(WindowsSprite&& object);
		constexpr WindowsSprite& operator=(const WindowsSprite& object);
		constexpr WindowsSprite& operator=(WindowsSprite&& object);
		virtual ~WindowsSprite();

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

	typedef WindowsSprite Sprite;
} // namespace cave
#endif