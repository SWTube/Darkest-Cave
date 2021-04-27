/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Object/UnixDrawableObject.h"

#ifdef __UNIX__
namespace cave
{
	constexpr UnixDrawableObject::UnixDrawableObject(const UnixDrawableObject& other)
		: GenericDrawableObject(other)
	{
		if (this != &other)
		{

		}
	}

	constexpr UnixDrawableObject::UnixDrawableObject(const UnixDrawableObject&& other)
		: GenericDrawableObject(other)
	{
		if (this != &other)
		{

		}
	}

	constexpr UnixDrawableObject& UnixDrawableObject::operator=(const UnixDrawableObject& other)
	{
		return *this;
	}

	constexpr UnixDrawableObject& UnixDrawableObject::operator=(const UnixDrawableObject&& other)
	{
		return *this;
	}

	UnixDrawableObject::~UnixDrawableObject()
	{
	}

	void UnixDrawableObject::Destroy()
	{
		glDeleteTextures(1u, &Texture);

		
		glDeleteBuffers(BUFFER_COUNT, Buffers);

		if (TextureData != nullptr)
		{
			free(TextureData);
		}
	}

	uint32_t* const UnixDrawableObject::GetBuffers()
	{
		return Buffers;
	}
} // namespace cave
#endif