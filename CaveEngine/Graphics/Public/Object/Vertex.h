/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "CoreTypes.h"

namespace cave
{
	//--------------------------------------------------------------------------------------
	// Structures
	//--------------------------------------------------------------------------------------
	typedef struct Float3
	{
		float X = 0.0f;
		float Y = 0.0f;
		float Z = 0.0f;

		Float3() = default;
		Float3(const Float3& other) = default;
		Float3& operator=(const Float3& other) = default;
		constexpr Float3(const Float3&& other);
		constexpr Float3& operator=(const Float3&& other);
		constexpr Float3(float x, float y, float z);
		constexpr Float3(float* array);
	} Float3;

	constexpr Float3::Float3(float x, float y, float z)
		: X(x)
		, Y(y)
		, Z(z)
	{
	}

	struct Float2
	{
		float X = 0.0f;
		float Y = 0.0f;
		Float2() = default;
		Float2(const Float2& other) = default;
		Float2& operator=(const Float2& other) = default;
		constexpr Float2(const Float2&& other);
		constexpr Float2& operator=(const Float2&& other);
		constexpr Float2(float x, float y);
		constexpr Float2(float* array);
	};

	constexpr Float2::Float2(float x, float y)
		: X(x)
		, Y(y)
	{
	}

	constexpr uint8_t VERTEX_POSITION = 0x0001;
	constexpr uint8_t VERTEX_TEXCOORD = 0x0010;


	typedef struct Vertex
	{
	public:
		Float3 Position = Float3(0.0f, 0.0f, 0.0f);
		uint8_t VertexFlag = VERTEX_POSITION;

		Vertex() = default;
		Vertex(const Vertex& other) = default;
		Vertex& operator=(const Vertex& other) = default;
		constexpr Vertex(const Vertex&& other);
		constexpr Vertex& operator=(const Vertex&& other);
		constexpr Vertex(float x, float y, float z);
		constexpr Vertex(float* array);
		constexpr Vertex(const Float3& array);
		constexpr Vertex(const Float3&& array);
	} Vertex;

	typedef struct VertexT : public Vertex
	{
	public:
		Float2 TexCoord = Float2(0.0f, 0.0f);

		VertexT() = default;
		VertexT(const VertexT& other) = default;
		VertexT& operator=(const VertexT& other) = default;
		constexpr VertexT(const VertexT&& other);
		constexpr VertexT& operator=(const VertexT&& other);
		constexpr VertexT(float posX, float posY, float posZ, float texX, float texY);
		constexpr VertexT(float* array);
		constexpr VertexT(const Float3& position, const Float2& texCoord);
		constexpr VertexT(const Float3&& position, const Float2&& texCoord);
	} VertexT;
} // namespace cave
