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
		UnixDrawableObject(uint32_t verticesCount, Vertex*&& vertices, uint32_t indicesCount, uint8_t*&& indices);
		UnixDrawableObject(uint32_t verticesCount, Vertex*&& vertices, uint32_t indicesCount, uint8_t*&& indices, const char* textureFilePath);
		UnixDrawableObject(const UnixDrawableObject& object) = default;
		UnixDrawableObject(const UnixDrawableObject&& object);
		constexpr UnixDrawableObject& operator=(const UnixDrawableObject& object) = default;
		constexpr UnixDrawableObject& operator=(const UnixDrawableObject&& object);
		~UnixDrawableObject() = default;

		eResult Init(uint32_t program) override;
		void Destroy() override;
		void Update() override;
		void Render() override;

		uint32_t* const GetBuffers();
	private:
		uint32_t mVertexArrayObject = 0u;
		static constexpr uint32_t ARRAY_BUFFER = 0u;
		static constexpr uint32_t ELEMENT_ARRAY_BUFFER = 1u;
		static constexpr uint32_t BUFFER_COUNT = 2u;
		static constexpr uint32_t V_POSITION = 0u;
		static constexpr uint32_t V_TEX_COORD = 1u;
		uint32_t mBuffers[BUFFER_COUNT] = { 0u, };
		uint32_t mProgram = 0u;
	};

	typedef UnixDrawableObject DrawableObject;
} // namespace cave
#endif