/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Shader/GenericShader.h"

namespace cave
{
	GenericShader::GenericShader(const std::filesystem::path& vertexShaderFilePath, const std::filesystem::path& fragmentShaderFilePath, MemoryPool& pool)
		: mPool(&pool)
	{
		mVertexShaderFilePath /= "CaveEngine\\Graphics\\Shader";
		mFragmentShaderFilePath /= "CaveEngine\\Graphics\\Shader";
		mVertexShaderFilePath /= vertexShaderFilePath;
		mFragmentShaderFilePath /= fragmentShaderFilePath;
	}

	GenericShader::GenericShader(const std::filesystem::path& shaderFilePath, MemoryPool& pool)
		: mPool(&pool)
	{
		mShaderFilePath /= "CaveEngine\\Graphics\\Shader";
		mShaderFilePath /= shaderFilePath;
	}

	GenericShader::GenericShader(GenericShader&& other)
		: mPool(other.mPool)
		, mShaderFilePath(std::move(other.mShaderFilePath))
		, mVertexShaderFilePath(std::move(other.mVertexShaderFilePath))
		, mFragmentShaderFilePath(std::move(other.mFragmentShaderFilePath))
	{
		other.mPool = nullptr;
	}

	GenericShader::~GenericShader()
	{
		mPool = nullptr;
		mShaderFilePath.clear();
		mVertexShaderFilePath.clear();
		mFragmentShaderFilePath.clear();
	}

	constexpr MemoryPool* const GenericShader::GetMemoryPool() const
	{
		return mPool;
	}

	GenericShader& GenericShader::operator=(GenericShader&& other)
	{
		if (this != &other)
		{
			mPool = other.mPool;
			mShaderFilePath = std::move(other.mShaderFilePath);
			mVertexShaderFilePath = std::move(other.mVertexShaderFilePath);
			mFragmentShaderFilePath = std::move(other.mFragmentShaderFilePath);

			other.mPool = nullptr;
		}

		return *this;
	}
} // namespace cave
