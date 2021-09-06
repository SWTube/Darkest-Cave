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
	//export extern constexpr uint32_t VERTEX_POSITION = 0b001;
	//export extern constexpr uint32_t VERTEX_TEXCOORD = 0b010;
	//export extern constexpr uint32_t VERTEX_COLOR = 0b100;

	//constexpr uint32_t GetVertexSize(uint32_t vertexFlag);

	export class Vertex
	{
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
		//virtual constexpr uint32_t GetSize() const;

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
		//virtual constexpr uint32_t GetSize() const override;
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
		//virtual constexpr uint32_t GetSize() const override;
	};

	export class VertexC : public Vertex
	{
	public:
		Float4 Color = Float4(0.0f, 0.0f, 0.0f, 0.0f);

		VertexC();
		VertexC(const VertexC& other);
		VertexC& operator=(const VertexC& other);
		constexpr VertexC(VertexC&& other) noexcept;
		constexpr VertexC& operator=(VertexC&& other) noexcept;
		constexpr VertexC(float posX, float posY, float posZ, float red, float green, float blue, float alpha);
		constexpr VertexC(float* array);
		constexpr VertexC(const Float3& position, const Float4& color);
		constexpr VertexC(Float3&& position, Float4&& color);
		//virtual constexpr uint32_t GetSize() const override;
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

	//constexpr uint32_t Vertex::GetSize() const
	//{
	//	uint32_t size = 0u;
	//	if (VertexFlag & VERTEX_POSITION)
	//	{
	//		size += 3u;
	//	}

	//	if (VertexFlag & VERTEX_TEXCOORD)
	//	{
	//		size += 2u;
	//	}

	//	size = size * sizeof(float) + sizeof(VertexFlag);

	//	if (size | 0b10 || size | 0b01)
	//	{
	//		size &= ~(0b11);
	//		size += 0b100;
	//	}

	//	return size;
	//}

	constexpr bool Vertex::operator==(const Vertex& rhs) const
	{
		return (Position == rhs.Position);
	}

	VertexT::VertexT()
		: Vertex()
	{
	}

	VertexT::VertexT(const VertexT& other)
		: Vertex(other)
		, TexCoord(other.TexCoord)
	{
	}

	VertexT& VertexT::operator=(const VertexT& other)
	{
		if (this != &other)
		{
			Vertex::operator=(other);
			TexCoord = other.TexCoord;
		}

		return *this;
	}

	constexpr VertexT::VertexT(VertexT&& other) noexcept
	{
		if (this != &other)
		{
			Position = other.Position;
			TexCoord = other.TexCoord;
		}
	}

	constexpr VertexT& VertexT::operator=(VertexT&& other) noexcept
	{
		if (this != &other)
		{
			Position = other.Position;
			TexCoord = other.TexCoord;
		}

		return *this;
	}

	constexpr VertexT::VertexT(float* array)
		: Vertex(array)
		, TexCoord(Float2(array[3], array[4]))
	{
	}

	constexpr VertexT::VertexT(const Float3& position, const Float2& texCoord)
		: Vertex(position)
		, TexCoord(texCoord)
	{
	}

	constexpr VertexT::VertexT(Float3&& position, Float2&& texCoord)
		: Vertex(std::move(position))
		, TexCoord(std::move(texCoord))
	{
	}

	constexpr VertexT::VertexT(float posX, float posY, float posZ, float texX, float texY)
		: Vertex(posX, posY, posZ)
		, TexCoord(Float2(texX, texY))
	{
	}

	VertexTC::VertexTC()
		: VertexT()
	{
	}

	VertexTC::VertexTC(const VertexTC& other)
		: VertexT(other)
		, Color(other.Color)
	{
	}

	VertexTC& VertexTC::operator=(const VertexTC& other)
	{
		if (this != &other)
		{
			VertexT::operator=(other);
			Color = other.Color;
		}

		return *this;
	}

	constexpr VertexTC::VertexTC(VertexTC&& other) noexcept
		: VertexT(std::move(other))
		, Color(std::move(other.Color))
	{
	}

	constexpr VertexTC& VertexTC::operator=(VertexTC&& other) noexcept
	{
		if (this != &other)
		{
			VertexT::operator=(std::move(other));

			Color = std::move(other.Color);
		}

		return *this;
	}

	constexpr VertexTC::VertexTC(float posX, float posY, float posZ, float texX, float texY, float red, float green, float blue, float alpha)
		: VertexT(posX, posY, posZ, texX, texY)
		, Color(red, green, blue, alpha)
	{
	}

	constexpr VertexTC::VertexTC(float* array)
		: VertexT(array)
		, Color(array[5], array[6], array[7], array[8])
	{
	}

	constexpr VertexTC::VertexTC(const Float3& position, const Float2& texCoord, const Float4& color)
		: VertexT(position, texCoord)
		, Color(color)
	{
	}

	constexpr VertexTC::VertexTC(Float3&& position, Float2&& texCoord, Float4&& color)
		: VertexT(std::move(position), std::move(texCoord))
		, Color(std::move(color))
	{
	}

	VertexC::VertexC()
		: Vertex()
	{
	}

	VertexC::VertexC(const VertexC& other)
		: Vertex(other)
		, Color(other.Color)
	{
	}

	VertexC& VertexC::operator=(const VertexC& other)
	{
		if (this != &other)
		{
			Vertex::operator=(other);
			Color = other.Color;
		}

		return *this;
	}

	constexpr VertexC::VertexC(VertexC&& other) noexcept
	{
		if (this != &other)
		{
			Position = other.Position;
			Color = other.Color;
		}
	}

	constexpr VertexC& VertexC::operator=(VertexC&& other) noexcept
	{
		if (this != &other)
		{
			Position = other.Position;
			Color = other.Color;
		}

		return *this;
	}

	constexpr VertexC::VertexC(float* array)
		: Vertex(array)
		, Color(array[3], array[4], array[5], array[6])
	{
	}

	constexpr VertexC::VertexC(const Float3& position, const Float4& color)
		: Vertex(position)
		, Color(color)
	{
	}

	constexpr VertexC::VertexC(Float3&& position, Float4&& color)
		: Vertex(std::move(position))
		, Color(std::move(Color))
	{
	}

	constexpr VertexC::VertexC(float posX, float posY, float posZ, float red, float green, float blue, float alpha)
		: Vertex(posX, posY, posZ)
		, Color(red, green, blue, alpha)
	{
	}
} // namespace cave
