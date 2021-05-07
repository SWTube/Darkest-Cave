/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Sprite/Vertex.h"

namespace cave
{
	constexpr Float3::Float3(const Float3&& other)
	{
		if (this != &other)
		{
			X = other.X;
			Y = other.Y;
			Z = other.Z;
		}
	}

	constexpr Float3& Float3::operator=(const Float3&& other)
	{
		if (this != &other)
		{
			X = other.X;
			Y = other.Y;
			Z = other.Z;
		}

		return *this;
	}

	constexpr Float3::Float3(float* array)
		: X(array[0])
		, Y(array[1])
		, Z(array[2])
	{
	}

	/* */

	constexpr Float2::Float2(const Float2&& other)
		: X(other.X)
		, Y(other.Y)
	{
	}

	constexpr Float2& Float2::operator=(const Float2&& other)
	{
		X = other.X;
		Y = other.Y;

		return *this;
	}

	constexpr Float2::Float2(float* array)
		: X(array[0])
		, Y(array[1])
	{
	}

	constexpr Vertex::Vertex(const Vertex&& other)
	{
		if (this != &other)
		{
			Position = other.Position;
		}
	}

	constexpr Vertex& Vertex::operator=(const Vertex&& other)
	{
		if (this != &other)
		{
			Position = other.Position;
		}

		return *this;
	}

	constexpr Vertex::Vertex(float* array)
		: Position(Float3(array))
	{
	}

	constexpr Vertex::Vertex(const Float3& array)
		: Position(array)
	{
	}

	constexpr Vertex::Vertex(const Float3&& array)
		: Position(array)
	{
	}

	constexpr VertexT::VertexT(const VertexT&& other)
	{
		if (this != &other)
		{
			Position = other.Position;
			TexCoord = other.TexCoord;
			VertexFlag |= VERTEX_TEXCOORD;
		}
	}

	constexpr VertexT& VertexT::operator=(const VertexT&& other)
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

	constexpr VertexT::VertexT(const Float3&& position, const Float2&& texCoord)
		: Vertex(std::move(position))
		, TexCoord(std::move(texCoord))
	{
		VertexFlag |= VERTEX_TEXCOORD;
	}
} // namespace cave
