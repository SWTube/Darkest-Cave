/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "GraphicsApiPch.h"

#include "CoreMinimal.h"
#include "Sprite/GenericSprite.h"

#ifdef __UNIX__
namespace cave
{
	class UnixSprite final : public GenericSprite
	{
	public:
		UnixSprite() = delete;
		UnixSprite(Texture* texture, MemoryPool& pool = gCoreMemoryPool);
		UnixSprite(const Texture& texture, MemoryPool& pool = gCoreMemoryPool);
		UnixSprite(Texture&& texture, MemoryPool& pool = gCoreMemoryPool);
		UnixSprite(const UnixSprite& object) = default;
		UnixSprite(UnixSprite&& object);
		UnixSprite& operator=(const UnixSprite& object) = default;
		UnixSprite& operator=(UnixSprite&& object);
		virtual ~UnixSprite();

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

	typedef UnixSprite Sprite;
} // namespace cave
#endif