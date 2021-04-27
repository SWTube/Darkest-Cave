/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "GraphicsApiPch.h"

#include "CoreMinimal.h"
#include "Object/GenericDrawableObject.h"

#ifdef __UNIX__
namespace cave
{
	class UnixDrawableObject final : public GenericDrawableObject
	{
	public:
		UnixDrawableObject() = delete;
		constexpr UnixDrawableObject(uint32_t verticesCount, uint32_t verticesFrameSize, float*&& vertices, uint32_t indicesCount, uint8_t*&& indices);
		constexpr UnixDrawableObject(const UnixDrawableObject& object);
		constexpr UnixDrawableObject(const UnixDrawableObject&& object);
		constexpr UnixDrawableObject& operator=(const UnixDrawableObject& object);
		constexpr UnixDrawableObject& operator=(const UnixDrawableObject&& object);
		virtual ~UnixDrawableObject();

		virtual void Destroy();

		uint32_t* const GetBuffers();
		uint32_t VertexArrayObject = 0u;
		static constexpr uint32_t ARRAY_BUFFER = 2u;
		static constexpr uint32_t ELEMENT_ARRAY_BUFFER = 2u;
		static constexpr uint32_t BUFFER_COUNT = 2u;
		uint32_t Buffers[BUFFER_COUNT] = { 0u, };
	};

	constexpr UnixDrawableObject::UnixDrawableObject(uint32_t verticesCount, uint32_t verticesFrameSize, float*&& vertices, uint32_t indicesCount, uint8_t*&& indices)
		: GenericDrawableObject(verticesCount, verticesFrameSize, std::move(vertices), indicesCount, std::move(indices))
	{
	}

	typedef UnixDrawableObject DrawableObject;
} // namespace cave
#endif