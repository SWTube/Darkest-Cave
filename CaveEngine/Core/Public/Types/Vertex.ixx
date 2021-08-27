/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "CoreTypes.h"

export module cave.Core.Types.Vertex;

import cave.Core.Types.Float;

namespace cave
{
	export extern constexpr uint32_t VERTEX_POSITION = 0b001;
	export extern constexpr uint32_t VERTEX_TEXCOORD = 0b010;
	export extern constexpr uint32_t VERTEX_COLOR = 0b100;

	export class Vertex
	{
	protected:
		uint32_t VertexFlag = VERTEX_POSITION;
	public:
		Float3 Position = Float3(0.0f, 0.0f, 0.0f);

		Vertex() = default;
		Vertex(const Vertex& other) = default;
		Vertex& operator=(const Vertex& other) = default;
		constexpr Vertex(Vertex&& other) noexcept;
		constexpr Vertex& operator=(Vertex&& other) noexcept;
		constexpr Vertex(float x, float y, float z);
		constexpr Vertex(float* array);
		constexpr Vertex(const Float3& array);
		constexpr Vertex(Float3&& array);
		constexpr uint32_t GetSize() const;

		constexpr bool operator==(const Vertex& rhs) const;
	};

	export class VertexT : public Vertex
	{
	public:
		Float2 TexCoord = Float2(0.0f, 0.0f);

		VertexT();
		VertexT(const VertexT& other);
		VertexT& operator=(const VertexT& other);
		constexpr VertexT(VertexT&& other) noexcept;
		constexpr VertexT& operator=(VertexT&& other) noexcept;
		constexpr VertexT(float posX, float posY, float posZ, float texX, float texY);
		constexpr VertexT(float* array);
		constexpr VertexT(const Float3& position, const Float2& texCoord);
		constexpr VertexT(Float3&& position, Float2&& texCoord);
	};

	export class VertexTC : public VertexT
	{
	public:
		Float4 Color = Float4(0.0f, 0.0f, 0.0f, 0.0f);

		VertexTC();
		VertexTC(const VertexTC& other);
		VertexTC& operator=(const VertexTC& other);
		constexpr VertexTC(VertexTC&& other) noexcept;
		constexpr VertexTC& operator=(VertexTC&& other) noexcept;
		constexpr VertexTC(float posX, float posY, float posZ, float texX, float texY, float red, float green, float blue, float alpha);
		constexpr VertexTC(float* array);
		constexpr VertexTC(const Float3& position, const Float2& texCoord, const Float4& color);
		constexpr VertexTC(Float3&& position, Float2&& texCoord, Float4&& color);
	};

	constexpr Vertex& Vertex::operator=(Vertex&& other) noexcept
	{
		if (this != &other)
		{
			Position = other.Position;
		}

		return *this;
	}

	constexpr Vertex::Vertex(Vertex&& other) noexcept
	{
		if (this != &other)
		{
			Position = other.Position;
		}
	}

	constexpr Vertex::Vertex(float* array)
		: Position(Float3(array))
	{
	}

	constexpr Vertex::Vertex(const Float3& array)
		: Position(array)
	{
	}

	constexpr Vertex::Vertex(Float3&& array)
		: Position(std::move(array))
	{
	}

	constexpr Vertex::Vertex(float x, float y, float z)
		: Position(Float3(x, y, z))
	{
	}

	constexpr uint32_t Vertex::GetSize() const
	{
		uint32_t size = 0u;
		if (VertexFlag & VERTEX_POSITION)
		{
			size += 3u;
		}

		if (VertexFlag & VERTEX_TEXCOORD)
		{
			size += 2u;
		}

		size = size * sizeof(float) + sizeof(VertexFlag);

		if (size | 0b10 || size | 0b01)
		{
			size &= ~(0b11);
			size += 0b100;
		}

		return size;
	}

	constexpr bool Vertex::operator==(const Vertex& rhs) const
	{
		return (Position == rhs.Position) && (VertexFlag == rhs.VertexFlag);
	}

	VertexT::VertexT()
		: Vertex()
	{
		VertexFlag |= VERTEX_TEXCOORD;
	}

	VertexT::VertexT(const VertexT& other)
		: Vertex(other)
		, TexCoord(other.TexCoord)
	{
		VertexFlag |= VERTEX_TEXCOORD;
	}

	VertexT& VertexT::operator=(const VertexT& other)
	{
		if (this != &other)
		{
			Vertex::operator=(other);
			TexCoord = other.TexCoord;
			VertexFlag |= VERTEX_TEXCOORD;
		}

		return *this;
	}

	constexpr VertexT::VertexT(VertexT&& other) noexcept
	{
		if (this != &other)
		{
			Position = other.Position;
			TexCoord = other.TexCoord;
			VertexFlag |= VERTEX_TEXCOORD;
		}
	}

	constexpr VertexT& VertexT::operator=(VertexT&& other) noexcept
	{
		if (this != &other)
		{
			Position = other.Position;
			TexCoord = other.TexCoord;
			VertexFlag |= VERTEX_TEXCOORD;
		}

		return *this;
	}

	constexpr VertexT::VertexT(float* array)
		: Vertex(array)
		, TexCoord(Float2(array[3], array[4]))
	{
		VertexFlag |= VERTEX_TEXCOORD;
	}

	constexpr VertexT::VertexT(const Float3& position, const Float2& texCoord)
		: Vertex(position)
		, TexCoord(texCoord)
	{
		VertexFlag |= VERTEX_TEXCOORD;
	}

	constexpr VertexT::VertexT(Float3&& position, Float2&& texCoord)
		: Vertex(std::move(position))
		, TexCoord(std::move(texCoord))
	{
		VertexFlag |= VERTEX_TEXCOORD;
	}

	constexpr VertexT::VertexT(float posX, float posY, float posZ, float texX, float texY)
		: Vertex(posX, posY, posZ)
		, TexCoord(Float2(texX, texY))
	{
		VertexFlag |= VERTEX_TEXCOORD;
	}

	VertexTC::VertexTC()
		: VertexT()
	{
		VertexFlag |= VERTEX_COLOR;
	}

	VertexTC::VertexTC(const VertexTC& other)
		: VertexT(other)
		, Color(other.Color)
	{
		VertexFlag |= VERTEX_COLOR;
	}

	VertexTC& VertexTC::operator=(const VertexTC& other)
	{
		if (this != &other)
		{
			VertexT::operator=(other);
			Color = other.Color;
			VertexFlag |= VERTEX_COLOR;
		}

		return *this;
	}

	constexpr VertexTC::VertexTC(VertexTC&& other) noexcept
		: VertexT(std::move(other))
		, Color(std::move(other.Color))
	{
		VertexFlag |= VERTEX_COLOR;
	}

	constexpr VertexTC& VertexTC::operator=(VertexTC&& other) noexcept
	{
		if (this != &other)
		{
			VertexT::operator=(std::move(other));

			Color = std::move(other.Color);
			VertexFlag |= VERTEX_COLOR;
		}

		return *this;
	}

	constexpr VertexTC::VertexTC(float posX, float posY, float posZ, float texX, float texY, float red, float green, float blue, float alpha)
		: VertexT(posX, posY, posZ, texX, texY)
		, Color(red, green, blue, alpha)
	{
		VertexFlag |= VERTEX_COLOR;
	}

	constexpr VertexTC::VertexTC(float* array)
		: VertexT(array)
		, Color(array[5], array[6], array[7], array[8])
	{
		VertexFlag |= VERTEX_COLOR;
	}

	constexpr VertexTC::VertexTC(const Float3& position, const Float2& texCoord, const Float4& color)
		: VertexT(position, texCoord)
		, Color(color)
	{
		VertexFlag |= VERTEX_COLOR;
	}

	constexpr VertexTC::VertexTC(Float3&& position, Float2&& texCoord, Float4&& color)
		: VertexT(std::move(position), std::move(texCoord))
		, Color(std::move(color))
	{
		VertexFlag |= VERTEX_COLOR;
	}
} // namespace cave
