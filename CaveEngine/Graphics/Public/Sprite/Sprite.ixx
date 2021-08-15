/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;
#include "GraphicsApiPch.h"

#include "CoreTypes.h"
#include "Containers/Vertex.h"
//#include "Texture/Texture.h"
export module Sprite;

import TextureManager;

namespace cave
{
	export class Sprite
	{
	public:
		Sprite() = default;
		Sprite(Texture* texture);
		Sprite(const Sprite& other);
		Sprite(Sprite&& other);
		virtual ~Sprite();
		Sprite& operator=(const Sprite& other);
		Sprite& operator=(Sprite&& other);

		virtual void Destroy();
		virtual void Update();
		virtual void Render(ID3D11DeviceContext* context);

		constexpr uint32_t GetIndicesCount() const;
		constexpr Texture* GetTexture() const;
		constexpr void SetPosition(float x, float y);
		constexpr void SetPosition(const Float2& position);
		constexpr void SetPosition(const Float2&& position);
		constexpr void SetZIndex(const uint32_t z);
		constexpr void SetFlipX(bool Flip);
		constexpr void SetFlipY(bool Flip);

		constexpr void Move(float x, float y);
		constexpr float GetPositionX() const;
		constexpr float GetPositionY() const;
		constexpr Float2 GetPosition() const;
		constexpr uint32_t GetWidth() const;
		constexpr uint32_t GetHeight() const;
		constexpr void GetSize(uint32_t& outWidth, uint32_t& outHeight) const;
		constexpr void SetSize(uint32_t width, uint32_t height);
		static constexpr void SetScreenSize(uint32_t width, uint32_t height);


		VertexT* GetVertices();
		void SetTexture(Texture* texture);
		void SetTextureWithFilePath(const std::filesystem::path& filePath);

	protected:

		static uint32_t mScreenWidth;
		static uint32_t mScreenHeight;


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

		bool mFlipX = false;
		bool mFlipY = false;
		bool mbNeedsUpdate = false;
	};
	
	uint32_t Sprite::mScreenWidth = 0u;
	uint32_t Sprite::mScreenHeight = 0u;



	constexpr void Sprite::SetScreenSize(uint32_t width, uint32_t height)
	{
		mScreenWidth = width;
		mScreenHeight = height;
	}

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

	void Sprite::SetTexture(Texture* texture)
	{
		mTexture = texture;
		mWidth = mTexture->GetWidth();
		mHeight = mTexture->GetHeight();
	}

	void Sprite::SetTextureWithFilePath(const std::filesystem::path& filePath)
	{
		mTexture = TextureManager::GetInstance().GetTexture(filePath.generic_string());
		mWidth = mTexture->GetWidth();
		mHeight = mTexture->GetHeight();
	}


	Sprite::Sprite(Texture* texture)
		: mTexture(texture)
	{
		mWidth = mTexture->GetWidth();
		mHeight = mTexture->GetHeight();
	}


	Sprite::Sprite(const Sprite& other)
		: mWidth(other.mWidth)
		, mHeight(other.mHeight)
		, mPosition(other.mPosition)
	{
		mTexture = other.mTexture;
	}

	Sprite::Sprite(Sprite&& other)
		: mTexture(other.mTexture)
		, mPosition(other.mPosition)
		, mWidth(other.mWidth)
		, mHeight(other.mHeight)
	{
		other.mTexture = nullptr;
	}

	Sprite& Sprite::operator=(const Sprite& other)
	{
		if (this != &other)
		{
			mTexture = other.mTexture;

			mPosition = other.mPosition;
			mWidth = other.mWidth;
			mHeight = other.mHeight;
		}

		return *this;
	}

	Sprite& Sprite::operator=(Sprite&& other)
	{
		if (this != &other)
		{
			mTexture = other.mTexture;

			mPosition = other.mPosition;

			mWidth = other.mWidth;
			mHeight = other.mHeight;
			other.mTexture = nullptr;
		}

		return *this;
	}

	Sprite::~Sprite()
	{
		Destroy();
	}


	void Sprite::Destroy()
	{
		if (mTexture != nullptr)
		{
			mTexture->~Texture(); //
			mTexture = nullptr;
		}
	}
	void Sprite::Update()
	{
	}


	VertexT* Sprite::GetVertices() {
		return mVertices;
	}

	void Sprite::Render(ID3D11DeviceContext* context)
	{
		float left = 0.0f;
		float right = 0.0f;
		float top = 0.0f;
		float bottom = 0.0f;
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		VertexT* verticesPtr = nullptr;
		eResult result = eResult::CAVE_OK;

		if (!mbNeedsUpdate && (mPosition == mPreviousPosition))
		{
			return;
		}

		mPreviousPosition = mPosition;

		left = static_cast<float>(mScreenWidth / 2) * -1 + mPosition.X - static_cast<float>(mWidth) / 2.0f;
		right = left + static_cast<float>(mWidth);
		top = static_cast<float>(mScreenHeight / 2) - mPosition.Y + static_cast<float>(mHeight) / 2.0f;
		bottom = top - static_cast<float>(mHeight);

		Float2 startCoord = { 0.0f,0.0f };
		Float2 endCoord = { 1.0f,1.0f };
		if (mTexture != nullptr) 
		{
			startCoord = mTexture->GetStartUV();
			endCoord = mTexture->GetEndUV();
		}
		if (mFlipX) 
		{
			float temp = startCoord.X;
			startCoord.X = endCoord.X;
			endCoord.X = temp;
		}
		if (mFlipY) {
			float temp = startCoord.Y;
			startCoord.Y = endCoord.Y;
			endCoord.Y = temp;
		}
		mVertices[0] = std::move(VertexT(Float3(left, top, mPosition.Z), startCoord));		// top left
		mVertices[1] = std::move(VertexT(Float3(right, top, mPosition.Z), Float2(endCoord.X, startCoord.Y)));	// top right
		mVertices[2] = std::move(VertexT(Float3(right, bottom, mPosition.Z), endCoord));		// bottom right
		mVertices[3] = std::move(VertexT(Float3(left, bottom, mPosition.Z), Float2(startCoord.X, endCoord.Y)));		// bottom left


		//flipX 
		//mVertices[0] = std::move(VertexT(Float3(left, top, mPosition.Z), Float2(mTexture->GetEndUV().X, mTexture->GetStartUV().Y)));		// top left
		//mVertices[1] = std::move(VertexT(Float3(right, top, mPosition.Z), Float2(mTexture->GetStartUV().X, mTexture->GetStartUV().Y)));	// top right
		//mVertices[2] = std::move(VertexT(Float3(right, bottom, mPosition.Z), Float2(mTexture->GetStartUV().X, mTexture->GetEndUV().Y)));		// bottom right
		//mVertices[3] = std::move(VertexT(Float3(left, bottom, mPosition.Z), Float2(mTexture->GetEndUV().X, mTexture->GetEndUV().Y)));		// bottom left
	}



	constexpr void Sprite::SetFlipX(bool Flip)
	{
		mFlipX = Flip;
	}

	constexpr void Sprite::SetFlipY(bool Flip)
	{
		mFlipY = Flip;
	}

} // namespace cave
