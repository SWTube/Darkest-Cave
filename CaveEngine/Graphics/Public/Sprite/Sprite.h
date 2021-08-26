/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once
#include "GraphicsApiPch.h"

#include "CoreTypes.h"
#include "Containers/Vertex.h"
//#include "Texture/Texture.h"
//#include "Texture/MultiTexture.h"

//import Texture;
import TextureManager;
import MultiTexture;

namespace cave
{
	class Sprite
	{
	public:
		Sprite() = default;
		Sprite(Texture* texture);
		Sprite(const Sprite& other);
		Sprite(Sprite&& other);
		virtual ~Sprite();
		Sprite& operator=(const Sprite& other);
		Sprite& operator=(Sprite&& other);
		//eResult Init(ID3D11Device* device, ID3D11DeviceContext* context, uint32_t screenWidth, uint32_t screenHeight);

		virtual void Destroy();
		virtual void Update();
		virtual void Render(ID3D11DeviceContext* context);

		constexpr uint32_t GetIndicesCount() const;
		constexpr Texture* GetTexture() const;
		constexpr void SetPosition(float x, float y);
		constexpr void SetPosition(const Float2& position);
		constexpr void SetPosition(const Float2&& position);
		constexpr void SetZIndex(const uint32_t z);
		constexpr void Move(float x, float y);
		constexpr float GetPositionX() const;
		constexpr float GetPositionY() const;
		constexpr Float2 GetPosition() const;

		VertexT* GetVertices();

		constexpr uint32_t GetWidth() const;
		constexpr uint32_t GetHeight() const;
		constexpr void GetSize(uint32_t& outWidth, uint32_t& outHeight) const;
		constexpr void SetSize(uint32_t width, uint32_t height);
		constexpr void SetTexture(Texture* texture);
	
	public:
		static uint32_t mScreenWidth;
		static uint32_t mScreenHeight;

	protected:
		//eResult initializeBuffers(ID3D11Device* device, ID3D11DeviceContext* context);
		static constexpr uint32_t VERTICES_COUNT = 4u;
		static constexpr uint32_t INDICES_COUNT = 6u;

		VertexT mVertices[VERTICES_COUNT] = {
			VertexT(-1.0f,  1.0f, 0.0f,	1.0f, 0.0f),	// top left
			VertexT(1.0f,  1.0f, 0.0f,	0.0f, 0.0f),	// top right
			VertexT(1.0f, -1.0f, 0.0f,	1.0f, 1.0f),	// bottom right
			VertexT(-1.0f, -1.0f, 0.0f,	0.0f, 1.0f),	// bottom left
		};


		static constexpr WORD INDICES[INDICES_COUNT] = {
			0, 1, 2,
			2, 3, 0,
		};

		Texture* mTexture = nullptr;

		uint32_t mWidth = 0u;
		uint32_t mHeight = 0u;


		Float3 mPosition = Float3(0, 0, 0);
		Float3 mPreviousPosition = Float3(-1, -1, -1);

		bool mbNeedsUpdate = false;

		//ID3D11Buffer* mVertexBuffer = nullptr;
		//ID3D11Buffer* mIndexBuffer = nullptr;

	};


	constexpr uint32_t Sprite::GetIndicesCount() const
	{
		return INDICES_COUNT;
	}

	constexpr Texture* Sprite::GetTexture() const
	{
		return mTexture;
	}

	constexpr void Sprite::SetPosition(float x, float y)
	{
		mPosition.X = x;
		mPosition.Y = y;
	}

	constexpr void Sprite::SetPosition(const Float2& position)
	{
		mPosition.X = position.X;
		mPosition.Y = position.Y;
	}

	constexpr void Sprite::SetPosition(const Float2&& position)
	{
		mPosition.X = position.X;
		mPosition.Y = position.Y;
	}

	inline constexpr void Sprite::SetZIndex(const uint32_t z)
	{
		mPosition.Z = 1.0f - static_cast<float>(z) * 0.01f;
	}

	constexpr void Sprite::Move(float x, float y)
	{
		if (mPosition.X <= FLT_MAX - x)
		{
			mPosition.X += x;
		}
		else
		{
			mPosition.X = FLT_MAX;
		}

		if (mPosition.Y <= FLT_MAX - y)
		{
			mPosition.Y += y;
		}
		else
		{
			mPosition.Y = FLT_MAX;
		}
	}

	constexpr float Sprite::GetPositionX() const
	{
		return mPosition.X;
	}

	constexpr float Sprite::GetPositionY() const
	{
		return mPosition.Y;
	}

	constexpr Float2 Sprite::GetPosition() const
	{
		return Float2(mPosition.X, mPosition.Y);
	}

	constexpr uint32_t Sprite::GetWidth() const
	{
		return mWidth;
	}

	constexpr uint32_t Sprite::GetHeight() const
	{
		return mHeight;
	}

	constexpr void Sprite::GetSize(uint32_t& outWidth, uint32_t& outHeight) const
	{
		outWidth = mWidth;
		outHeight = mHeight;
	}

	constexpr void Sprite::SetSize(uint32_t width, uint32_t height)
	{
		mWidth = width;
		mHeight = height;
		mbNeedsUpdate = true;
	}

	constexpr void Sprite::SetTexture(Texture* texture)
	{
		mTexture = texture;
	}

} // namespace cave
