/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;
#include <cmath>
#include "GraphicsApiPch.h"
#include "CoreGlobals.h"

export module Sprite;

import cave.Core.Types.Float;
import cave.Core.Types.Vertex;
import Renderable;
import TextureManager;

namespace cave
{
	export class Sprite : public Renderable
	{
	public:
		Sprite() = default;
		Sprite(Texture* texture);
		Sprite(const Sprite& other);
		Sprite(Sprite&& other);
		virtual ~Sprite();
		Sprite& operator=(const Sprite& other);
		Sprite& operator=(Sprite&& other);

		virtual void Destroy() override;

		constexpr uint32_t GetIndicesCount() const;
		constexpr Texture* GetTexture() const;

		constexpr uint32_t GetWidth() const;
		constexpr uint32_t GetHeight() const;
		constexpr void GetSize(uint32_t& outWidth, uint32_t& outHeight) const;
		constexpr void SetSize(uint32_t width, uint32_t height);

		static constexpr void SetScreenSize(uint32_t width, uint32_t height);
		VertexTC* GetVertices();

		void SetTexture(Texture* texture);
		void SetTextureWithFilePath(const std::filesystem::path& filePath);
		constexpr void SetColor(const Float4 color);
		constexpr void SetFlipX(bool Flip);
		constexpr void SetFlipY(bool Flip);

	protected:
		virtual void update() override;
		virtual void creatRenderCommand() override;
		virtual void makeRenderCommand() override;

	protected:
		static uint32_t mScreenWidth;
		static uint32_t mScreenHeight;


		static constexpr uint32_t VERTICES_COUNT = 4u;
		static constexpr uint32_t INDICES_COUNT = 6u;

		VertexTC mVertices[VERTICES_COUNT] = {
			VertexTC(-1.0f,  1.0f, 0.0f,	1.0f, 0.0f,1.0f,1.0f,1.0f,1.0f),	// top left
			VertexTC(1.0f,  1.0f, 0.0f,	0.0f, 0.0f,1.0f,1.0f,1.0f,1.0f),	// top right
			VertexTC(1.0f, -1.0f, 0.0f,	1.0f, 1.0f,1.0f,1.0f,1.0f,1.0f),	// bottom right
			VertexTC(-1.0f, -1.0f, 0.0f,	0.0f, 1.0f,1.0f,1.0f,1.0f,1.0f),	// bottom left
		};


		Texture* mTexture = nullptr;

		uint32_t mWidth = 0u;
		uint32_t mHeight = 0u;

		Float4 mColor = Float4(1.0f, 1.0f, 1.0f, 1.0f);
		Float3 mPreviousPosition = Float3(-1, -1, -1);

		Float2 mStartTextureCoord = Float2(0.0f, 0.0f);
		Float2 mEndTextureCoord = Float2(1.0f, 1.0f);

		bool mFlipX = false;
		bool mFlipY = false;
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
	}

	void Sprite::creatRenderCommand()
	{
		SpriteCommand* command = reinterpret_cast<SpriteCommand*>(gCoreMemoryPool.Allocate(sizeof(SpriteCommand)));
		new(command) SpriteCommand();
		command->type =  RenderCommand::eType::SPRITE_COMMAND;
		mCommand = command;
	}
	constexpr void Sprite::SetColor(const Float4 color)
	{
		mColor = color;
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
		if (mTexture == nullptr)
		{
			mTexture = TextureManager::GetInstance().AddTexture(filePath);
		}
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
		: Renderable(other)
		, mWidth(other.mWidth)
		, mHeight(other.mHeight)
	{
		mTexture = other.mTexture;
	}

	Sprite::Sprite(Sprite&& other)
		: Renderable(other)
		, mTexture(other.mTexture)
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
			//mTexture->~Texture(); //
			mTexture = nullptr;
		}

		if (mCommand != nullptr)
		{
			gCoreMemoryPool.Deallocate(mCommand, sizeof(SpriteCommand));
			mCommand = nullptr;
		}
	}
	void Sprite::update()
	{
	}


	VertexTC* Sprite::GetVertices() 
	{
		return mVertices;
	}

	void Sprite::makeRenderCommand()
	{
		float left = 0.0f;
		float right = 0.0f;
		float top = 0.0f;
		float bottom = 0.0f;

		mPreviousPosition = mPosition;

		float radian = mAngle * 0.0174533f;

		float posX = static_cast<float>(mScreenWidth / 2) * -1 + mPosition.X;
		float posY = static_cast<float>(mScreenHeight / 2) - mPosition.Y;

		left = posX - static_cast<float>(mWidth) / 2.0f;
		//left = mPosition.X - static_cast<float>(mWidth) / 2.0f;
		right = left + static_cast<float>(mWidth);
		top = posY + static_cast<float>(mHeight) / 2.0f;
		//top = mPosition.Y + static_cast<float>(mHeight) / 2.0f;
		bottom = top - static_cast<float>(mHeight);
	
		mVertices[0] = std::move(VertexTC(Float3(left, top, mPosition.Z), 
			mStartTextureCoord, 
			mColor));		// top left
		
		mVertices[1] = std::move(VertexTC(Float3(right, top, mPosition.Z), 
			Float2(mEndTextureCoord.X, mStartTextureCoord.Y), 
			mColor));	// top right
		
		mVertices[2] = std::move(VertexTC(Float3(right, bottom, mPosition.Z),
			mEndTextureCoord , 
			mColor));		// bottom right
	
		mVertices[3] = std::move(VertexTC(Float3(left, bottom, mPosition.Z), 
			Float2(mStartTextureCoord.X, mEndTextureCoord.Y),
			mColor));		// bottom left
		
		//회전
		DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixTranslation(-posX, -posY, -mPosition.Z) *DirectX::XMMatrixRotationZ(mAngle * 0.0174533f) * DirectX::XMMatrixTranslation(posX, posY, mPosition.Z);
		
		SpriteCommand* command = reinterpret_cast<SpriteCommand*>(mCommand);
		command->vertexData = mVertices;
		command->texture = mTexture;
		command->zIndex = mZIndex;
		command->worldMatrix = worldMatrix;
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
