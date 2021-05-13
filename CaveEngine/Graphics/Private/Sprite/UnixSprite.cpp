/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Sprite/UnixSprite.h"

#include "lodepng.h"

#ifdef __UNIX__
namespace cave
{
	UnixSprite::UnixSprite(Texture* texture, MemoryPool& pool)
		: GenericSprite(texture, pool)
	{
	}
	
	UnixSprite::UnixSprite(const Texture& texture, MemoryPool& pool)
		: GenericSprite(texture, pool)
	{
	}
	
	UnixSprite::UnixSprite(Texture&& texture, MemoryPool& pool)
		: GenericSprite(std::move(texture), pool)
	{
	}

	UnixSprite::UnixSprite(UnixSprite&& other)
		: GenericSprite(std::move(other))
	{
	}

	UnixSprite& UnixSprite::operator=(UnixSprite&& other)
	{
		if (this != &other)
		{
			GenericSprite::operator=(other);
			mVertexArrayObject = other.mVertexArrayObject;
			memcpy(mBuffers, other.mBuffers, BUFFER_COUNT);
			mProgram = other.mProgram;
		}

		return *this;
	}

	UnixSprite::~UnixSprite()
	{
		Destroy();
	}

	eResult UnixSprite::initializeBuffers(uint32_t program)
	{
		eResult result = eResult::CAVE_OK;
		uint32_t glError = GL_NO_ERROR;
		mProgram = program;

		// 14. Create Buffer ---------------------------------------------------------------------------------------------
		glCreateBuffers(Sprite::BUFFER_COUNT, mBuffers);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glCreateBuffers error code: 0x%x", glError);
			return eResult::CAVE_FAIL;
		}
		for (uint32_t i = 0; i < Sprite::BUFFER_COUNT; ++i)
		{
			LOGDF(eLogChannel::GRAPHICS, std::cerr, "buffer: %u", mBuffers[i]);
		}

		// 15. Bind Buffer ---------------------------------------------------------------------------------------------
		// glBindBuffer(GL_ARRAY_BUFFER, mBuffers[Sprite::ARRAY_BUFFER]);
		// if (glError = glGetError(); glError != GL_NO_ERROR)
		// {
		// 	LOGEF(eLogChannel::GRAPHICS, std::cerr, "glBindBuffer error code: 0x%x", glError);
		// 	return eResult::CAVE_FAIL;
		// }
		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffers[Sprite::ELEMENT_ARRAY_BUFFER]);
		// if (glError = glGetError(); glError != GL_NO_ERROR)
		// {
		// 	LOGEF(eLogChannel::GRAPHICS, std::cerr, "glBindBuffer error code: 0x%x", glError);
		// 	return eResult::CAVE_FAIL;
		// }

		// Preparing to Send Data to OpenGL
		// All data must be stored in buffer objects (chunks of memory managed by OpenGL)
		// Common way is to specify the data at the same time as you specify the buffer's size
		glNamedBufferStorage(mBuffers[Sprite::ARRAY_BUFFER], sizeof(VertexT) * VERTICES_COUNT, mVertices, GL_DYNAMIC_STORAGE_BIT);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glNamedBufferStorage error code: 0x%x", glError);
			return eResult::CAVE_FAIL;
		}

		glNamedBufferStorage(mBuffers[Sprite::ELEMENT_ARRAY_BUFFER], sizeof(uint8_t) * INDICES_COUNT, INDICES, GL_DYNAMIC_STORAGE_BIT);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glNamedBufferStorage error code: 0x%x", glError);
			return eResult::CAVE_FAIL;
		}

		glCreateVertexArrays(1u, &mVertexArrayObject);
		if (uint32_t glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glCreateVertexArrays error code: 0x%x", glError);
			return eResult::CAVE_FAIL;
		}

		return result;
	}

	eResult UnixSprite::InitTexture()
	{
		mTextureIndex = mTexture->GetIndex();

		char tex[8] = "tex";
		snprintf(tex, 8, "tex[%u]", mTextureIndex - 1u);
		LOGDF(eLogChannel::GRAPHICS, std::cerr, "glBindTextureUnit %s %u", tex, mTextureIndex);
		if (glGetUniformLocation(mProgram, tex) < 0)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "Failed to get uniform location: %s, error code: 0x%x", tex, glGetError());
			return eResult::CAVE_FAIL;
		}

		int32_t texLocation = glGetUniformLocation(mProgram, tex);
		if (texLocation >= 0)
		{
			glUniform1i(texLocation, mTextureIndex - 1u);
			if (uint32_t glError = glGetError(); glError != GL_NO_ERROR)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "glUniform1i location: %u error code: 0x%x", texLocation, glError);
			}
		}

		return eResult::CAVE_OK;
	}

	void UnixSprite::Destroy()
	{
		GenericSprite::Destroy();
		
		glDeleteBuffers(BUFFER_COUNT, mBuffers);
	}

	const uint32_t* const UnixSprite::GetBuffers() const
	{
		return mBuffers;
	}

	void UnixSprite::Update()
	{
	}

	void UnixSprite::Render()
	{
		int32_t glError = GL_NO_ERROR;

		float left = 0.0f;
		float right = 0.0f;
		float top = 0.0f;
		float bottom = 0.0f;
		eResult result = eResult::CAVE_OK;

		if (!mbNeedsUpdate && (mPosition == mPreviousPosition))
		{
			return;
		}

		mPreviousPosition = mPosition;

		left = -static_cast<float>(mScreenWidth / 2u) + mPosition.X - static_cast<float>(mWidth) / 2.0f;
		right = left + static_cast<float>(mWidth);
		top = -static_cast<float>((mScreenHeight / 2u)) - mPosition.Y + static_cast<float>(mHeight) / 2.0f;
		bottom = top - static_cast<float>(mHeight);

		// mVertices[0] = std::move(VertexT(Float3( left,    top, 0.0f), Float2(0.0f, 0.0f)));		// top left
		// mVertices[1] = std::move(VertexT(Float3( right,   top, 0.0f), Float2(1.0f, 0.0f)));		// top right
		// mVertices[2] = std::move(VertexT(Float3(right, bottom, 0.0f), Float2(1.0f, 1.0f)));		// bottom right
		// mVertices[3] = std::move(VertexT(Float3( left, bottom, 0.0f), Float2(0.0f, 1.0f)));		// bottom left

		// mVertices[0] = std::move(VertexT(Float3(-1.0f,  1.0f, 0.0f), Float2(0.0f, 0.0f)));		// top left
		// mVertices[1] = std::move(VertexT(Float3( 1.0f,  1.0f, 0.0f), Float2(1.0f, 0.0f)));		// top right
		// mVertices[2] = std::move(VertexT(Float3(-1.0f, -1.0f, 0.0f), Float2(1.0f, 1.0f)));		// bottom right
		// mVertices[3] = std::move(VertexT(Float3( 1.0f, -1.0f, 0.0f), Float2(0.0f, 1.0f)));		// bottom left

		LOGIF(eLogChannel::GRAPHICS, std::cout, "%6f %6f %6f", mVertices[0].Position.X, mVertices[0].Position.Y, mVertices[0].Position.Z);
		LOGIF(eLogChannel::GRAPHICS, std::cout, "%6f %6f %6f", mVertices[1].Position.X, mVertices[1].Position.Y, mVertices[1].Position.Z);
		LOGIF(eLogChannel::GRAPHICS, std::cout, "%6f %6f %6f", mVertices[2].Position.X, mVertices[2].Position.Y, mVertices[2].Position.Z);
		LOGIF(eLogChannel::GRAPHICS, std::cout, "%6f %6f %6f", mVertices[3].Position.X, mVertices[3].Position.Y, mVertices[3].Position.Z);

		mbNeedsUpdate = false;

		// mVertices[0]

		mTextureIndex = mTexture->GetIndex();

		glBindVertexArray(mVertexArrayObject);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glBindVertexArray error code: 0x%x", glError);
		}
	}
} // namespace cave
#endif