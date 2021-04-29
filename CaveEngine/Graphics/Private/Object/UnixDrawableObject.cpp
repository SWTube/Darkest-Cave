/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Object/UnixDrawableObject.h"

#include "lodepng.h"

#ifdef __UNIX__
namespace cave
{
	UnixDrawableObject::UnixDrawableObject(uint32_t verticesCount, Vertex*&& vertices, uint32_t indicesCount, uint8_t*&& indices)
		: GenericDrawableObject(verticesCount, std::move(vertices), indicesCount, std::move(indices))
	{
	}

	UnixDrawableObject::UnixDrawableObject(uint32_t verticesCount, Vertex*&& vertices, uint32_t indicesCount, uint8_t*&& indices, const char* textureFilePath)
		: GenericDrawableObject(verticesCount, std::move(vertices), indicesCount, std::move(indices), textureFilePath)
	{
	}

	UnixDrawableObject::UnixDrawableObject(const UnixDrawableObject&& other)
		: GenericDrawableObject(std::move(other))
	{
	}


	UnixDrawableObject& UnixDrawableObject::operator=(const UnixDrawableObject&& other)
	{
		if (this != &other)
		{
			GenericDrawableObject::operator=(other);
			mVertexArrayObject = other.mVertexArrayObject;
			memcpy(mBuffers, other.mBuffers, BUFFER_COUNT);
			mProgram = other.mProgram;
		}

		return *this;
	}

	eResult UnixDrawableObject::Init(uint32_t program)
	{
		eResult result = eResult::CAVE_OK;
		uint32_t glError = GL_NO_ERROR;
		mProgram = program;

		// 14. Create Buffer ---------------------------------------------------------------------------------------------
		glCreateBuffers(DrawableObject::BUFFER_COUNT, mBuffers);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glCreateBuffers error code: 0x%x", glError);
			return eResult::CAVE_FAIL;
		}
		for (uint32_t i = 0; i < DrawableObject::BUFFER_COUNT; ++i)
		{
			LOGDF(eLogChannel::GRAPHICS, std::cerr, "buffer: %u", mBuffers[i]);
		}

		// 15. Bind Buffer ---------------------------------------------------------------------------------------------
		glBindBuffer(GL_ARRAY_BUFFER, mBuffers[DrawableObject::ARRAY_BUFFER]);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glBindBuffer error code: 0x%x", glError);
			return eResult::CAVE_FAIL;
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffers[DrawableObject::ELEMENT_ARRAY_BUFFER]);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glBindBuffer error code: 0x%x", glError);
			return eResult::CAVE_FAIL;
		}

		// 12. Define, create, set the input layout ---------------------------------------------------------------------------------------------
		glCreateVertexArrays(1u, &mVertexArrayObject);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glCreateVertexArrays error code: 0x%x", glError);
			return eResult::CAVE_FAIL;
		}
		glBindVertexArray(mVertexArrayObject);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glBindVertexArray error code: 0x%x", glError);
			return eResult::CAVE_FAIL;
		}
		
		glVertexAttribPointer(V_POSITION, 3, GL_FLOAT, GL_FALSE, mVertices[0].GetSize(), BUFFER_OFFSET(0u));
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glVertexAttribPointer error code: 0x%x", glError);
			return eResult::CAVE_FAIL;
		}
		glEnableVertexAttribArray(V_POSITION);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glEnableVertexAttribArray error code: 0x%x", glError);
			return eResult::CAVE_FAIL;
		}

		glVertexAttribPointer(V_TEX_COORD, 2, GL_FLOAT, GL_FALSE, mVertices[0].GetSize(), BUFFER_OFFSET(sizeof(Vertex)));
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glVertexAttribPointer error code: 0x%x", glError);
			return eResult::CAVE_FAIL;
		}
		glEnableVertexAttribArray(V_TEX_COORD);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glEnableVertexAttribArray error code: 0x%x", glError);
			return eResult::CAVE_FAIL;
		}

		// Preparing to Send Data to OpenGL
		// All data must be stored in buffer objects (chunks of memory managed by OpenGL)
		// Common way is to specify the data at the same time as you specify the buffer's size
		glNamedBufferStorage(mBuffers[DrawableObject::ARRAY_BUFFER], mVerticesCount * mVertices[0].GetSize(), mVertices, 0);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glNamedBufferStorage error code: 0x%x", glError);
			return eResult::CAVE_FAIL;
		}

		glNamedBufferStorage(mBuffers[DrawableObject::ELEMENT_ARRAY_BUFFER], mIndicesCount * sizeof(*mIndices), mIndices, 0);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glNamedBufferStorage error code: 0x%x", glError);
			return eResult::CAVE_FAIL;
		}

		// 16. Load Textures ---------------------------------------------------------------------------------------------
		uint32_t error = lodepng_decode24_file(&mTextureData, &mTextureWidth, &mTextureHeight, mTextureFilePath);
		if (error != 0)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cout, "The png file %s cannot be loaded. Error Code: %u", mTextureFilePath, error);
			return eResult::CAVE_FAIL;
		}

		// LOGDF(eLogChannel::GRAPHICS, std::cout, "vector size: %lu", TextureData.size());
		glCreateTextures(GL_TEXTURE_2D, 1u, &mTexture);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glCreateTextures error code: 0x%x", glError);
			return eResult::CAVE_FAIL;
		}

		glBindTextureUnit(mTexture - 1u, mTexture);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glBindTextureUnit error code: 0x%x", glError);
			return eResult::CAVE_FAIL;
		}

		char tex[8] = "tex";
		snprintf(tex, 8, "tex[%u]", mTexture - 1u);
		LOGDF(eLogChannel::GRAPHICS, std::cerr, "glBindTextureUnit %s %u", tex, mTexture);
		if (glGetUniformLocation(mProgram, tex) < 0)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "Failed to get uniform location: %s, error code: 0x%x", tex, glGetError());
			return eResult::CAVE_FAIL;
		}

		glTextureParameteri(mTexture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(mTexture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(mTexture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(mTexture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureStorage2D(mTexture, 1, GL_RGB8, mTextureWidth, mTextureHeight);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glTextureStorage2D error code: 0x%x", glError);
			return eResult::CAVE_FAIL;
		}
		glTextureSubImage2D(mTexture, 0, 0, 0, mTextureWidth, mTextureHeight, GL_RGB, GL_UNSIGNED_BYTE, mTextureData);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glTextureSubImage2D error code: 0x%x", glError);
			return eResult::CAVE_FAIL;
		}
		// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, TextureWidth, TextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureData);
		glGenerateTextureMipmap(mTexture);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glGenerateTextureMipmap error code: 0x%x", glError);
			return eResult::CAVE_FAIL;
		}

		int32_t texLocation = glGetUniformLocation(mProgram, tex);
		
		if (texLocation >= 0)
		{
			glUniform1i(texLocation, mTexture - 1u);
		}

		int32_t worldLocation = glGetUniformLocation(mProgram, "World");
		if (worldLocation < 0)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "Failed to get uniform location: %s, error code: 0x%x", "World", glGetError());
			return eResult::CAVE_FAIL;
		}
		glUniformMatrix4fv(worldLocation, 1, false, glm::value_ptr(mWorld));

		// glCreateSamplers(1, &msBackgroundSampler);
		// LOGDF(eLogChannel::GRAPHICS, std::cout, "sampler: %u", msBackgroundSampler);
		// glBindSampler(msBackgroundIndex, msBackgroundSampler);
		free(mTextureData);
		mTextureData = nullptr;

		LOGDF(eLogChannel::GRAPHICS, std::cout, "\n\tArray Buffer: %u\n\tElement Array Buffer: %u\n\tVertexArrayObject: %u\n\tTexture: %u, %s", mBuffers[ARRAY_BUFFER], mBuffers[ELEMENT_ARRAY_BUFFER], mVertexArrayObject, mTexture, mTextureFilePath);

		return result;
	}

	void UnixDrawableObject::Destroy()
	{
		glDeleteTextures(mTexture - 1u, &mTexture);

		
		glDeleteBuffers(BUFFER_COUNT, mBuffers);

		if (mTextureData != nullptr)
		{
			free(mTextureData);
		}
	}

	uint32_t* const UnixDrawableObject::GetBuffers()
	{
		return mBuffers;
	}

	void UnixDrawableObject::Update()
	{
	}

	void UnixDrawableObject::Render()
	{
		int32_t glError = GL_NO_ERROR;

		int32_t worldLocation = glGetUniformLocation(mProgram, "World");
		if (worldLocation < 0)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "Failed to get uniform location: %s, error code: 0x%x", "World", glGetError());
		}
		glUniformMatrix4fv(worldLocation, 1, false, glm::value_ptr(mWorld));

		glBindTextureUnit(mTexture - 1u, mTexture);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glBindTextureUnit error code: 0x%x, %u", glError, mTexture);
		}

		glBindVertexArray(mVertexArrayObject);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glBindVertexArray error code: 0x%x", glError);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffers[DrawableObject::ELEMENT_ARRAY_BUFFER]);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glBindBuffer error code: 0x%x", glError);
		}

		int32_t textureIndexLocation = glGetUniformLocation(mProgram, "textureIndex");
		glUniform1i(textureIndexLocation, mTexture - 1u);

		// 5. Render ---------------------------------------------------------------------------------------------
		// Sending Data to OpenGL
			// Drawing == transferring vertex data to the OpenGL server
			// vertex == bundle of data values that are processed together
				// almost always includes positional data
				// values needed to determine the pixel's final color
		glDrawElements(GL_TRIANGLES, mIndicesCount, GL_UNSIGNED_BYTE, nullptr);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glDrawElements error code: 0x%x", glError);
		}
	}
} // namespace cave
#endif