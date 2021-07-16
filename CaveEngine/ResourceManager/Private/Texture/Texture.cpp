/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "lodepng.h"

#include "Debug/Log.h"
#include "Texture/Texture.h"

#ifdef __WIN32__
	import DdsTextureLoader;
	import WicTextureLoader;
#endif

namespace cave
{
	int32_t Texture::msTextureCount = -1;

	Texture::Texture(ID3D11Device* device, const std::filesystem::path& filePath, eTextureFormat textureFormat, MemoryPool& pool)
		: mPool(&pool)
		, mFormat(textureFormat)
		, mTarget(++msTextureCount)
	{
		mTexture = reinterpret_cast<TexturePointer*>(mPool->Allocate(sizeof(TexturePointer)));
		mTexture->ReferenceCount = 1u;
		mTexture->Texture = nullptr;

		mFilePath /= L"CaveEngine\\Graphics\\Resource";
		std::filesystem::create_directories(mFilePath / L"Textures");
		mFilePath /= L"Textures";
		mFilePath /= filePath;
		mFormat = textureFormat;

		ID3D11Resource* resource;
		if (mFilePath.extension() == ".dds")
		{
			if (FAILED(DdsTextureLoader::CreateDDSTextureFromFile(device, mFilePath.c_str(), &resource, &mTexture->Texture))) {
				LOGEF(eLogChannel::GRAPHICS, "The dss file %s cannot be loaded", mFilePath.string().c_str());
				return;
			}
		}
		else
		{
			if (FAILED(WicTextureLoader::CreateWICTextureFromFile(device, mFilePath.c_str(), &resource, &mTexture->Texture))) {
				LOGEF(eLogChannel::GRAPHICS, "The png file %s cannot be loaded", mFilePath.string().c_str());
				return;
			}

		}
		LOGIF(eLogChannel::GRAPHICS, "Texture file %s be successfully loaded.", mFilePath.string().c_str());

		//get width, height
		ID3D11Texture2D* texture2D;
		texture2D = (ID3D11Texture2D*)resource;
		if (texture2D) {
			//D3D11_Texture2d_DESC 정보 얻기
			D3D11_TEXTURE2D_DESC desc;
			texture2D->GetDesc(&desc);

			mWidth = (uint32_t)desc.Width;
			mHeight = (uint32_t)desc.Height;
		}
	}

	Texture::Texture(const Texture& other)
		: mPool(other.mPool)
		, mFilePath(other.mFilePath)
		, mWidth(other.mWidth)
		, mHeight(other.mHeight)
		, mFormat(other.mFormat)
		, mTexture(other.mTexture)
		, mIndex(other.mIndex)
		, mTarget(other.mTarget)
		, mStartUV(other.mStartUV)
		, mEndUV(other.mEndUV)
	{
		if (mTexture != nullptr)
		{
			++mTexture->ReferenceCount;
		}
	}

	Texture::Texture(Texture&& other)
		: mPool(other.mPool)
		, mFilePath(other.mFilePath)
		, mWidth(other.mWidth)
		, mHeight(other.mHeight)
		, mFormat(other.mFormat)
		, mTexture(other.mTexture)
		, mIndex(other.mIndex)
		, mTarget(other.mTarget)
		, mStartUV(other.mStartUV)
		, mEndUV(other.mEndUV)
	{
		other.mPool = nullptr;
		other.mFilePath.clear();
		other.mTexture = nullptr;
		other.mIndex = -1;
		other.mTarget = 0u;
		other.mStartUV = Float2(0.0f, 0.0f);
		other.mEndUV = Float2(1.0f, 1.0f);
	}

	Texture& Texture::operator=(const Texture& other)
	{
		if (this != &other)
		{
			mPool = other.mPool;
			mFilePath = other.mFilePath;
			mWidth = other.mWidth;
			mHeight = other.mHeight;
			mFormat = other.mFormat;
			mStartUV = other.mStartUV;
			mEndUV = other.mEndUV;
			if (mTexture != nullptr)
			{
				--mTexture->ReferenceCount;
			}
			mTexture = other.mTexture;
			if (mTexture != nullptr)
			{
				++mTexture->ReferenceCount;
			}
			mIndex = other.mIndex;
		}

		return *this;
	}

	Texture& Texture::operator=(Texture&& other)
	{
		if (this != &other)
		{
			mPool = other.mPool;
			mFilePath = other.mFilePath;
			mWidth = other.mWidth;
			mHeight = other.mHeight;
			mFormat = other.mFormat;
			if (mTexture != nullptr)
			{
				--mTexture->ReferenceCount;
			}
			mTexture = other.mTexture;
			mIndex = other.mIndex;
			mTarget = other.mTarget;
			mStartUV = other.mStartUV;
			mEndUV = other.mEndUV;

			other.mPool = nullptr;
			other.mFilePath.clear();
			other.mTexture = nullptr;
			other.mIndex = 0u;
			other.mTarget = -1;
			other.mStartUV = Float2(0.0f, 0.0f);
			other.mEndUV = Float2(1.0f, 1.0f);
		}

		return *this;
	}

	Texture::~Texture()
	{
		Destroy();
	}


	void Texture::Destroy()
	{
		if (mTexture != nullptr)
		{
			if (--mTexture->ReferenceCount == 0)
			{
				--msTextureCount;
			}
			mTexture->~TexturePointer();
			
			mPool->Deallocate(mTexture, sizeof(TexturePointer));
			mTexture = nullptr;
		}
	}

	MemoryPool* Texture::GetMemoryPool()
	{
		return mPool;
	}

	const char* Texture::GetCStringFilePath() const
	{
		return mFilePath.string().c_str();
	}

	/*
	void Texture::Init(ID3D11Device* device, ID3D11DeviceContext* deviceContext) {
		//const wchar_t* extension = mFilePath.extension().c_str();

		ID3D11Resource* resource;
		if (mFilePath.extension() == ".dds")
		{
			if (FAILED(DdsTextureLoader::CreateDDSTextureFromFile(device, mFilePath.c_str(), &resource, &mTexture->Texture))) {
				LOGEF(eLogChannel::GRAPHICS, "The dss file %s cannot be loaded", mFilePath.string().c_str());
				return;
			}
		}
		else
		{
			if (FAILED(WicTextureLoader::CreateWICTextureFromFile(device, mFilePath.c_str(), &resource, &mTexture->Texture))) {
				LOGEF(eLogChannel::GRAPHICS, "The png file %s cannot be loaded", mFilePath.string().c_str());
				return;
			}

		}
		LOGIF(eLogChannel::GRAPHICS, "Texture file %s be successfully loaded.",mFilePath.string().c_str());
		//get width, height
		ID3D11Texture2D* texture2D;
		texture2D = (ID3D11Texture2D*)resource;
		if (texture2D) {
			//D3D11_Texture2d_DESC 정보 얻기
			D3D11_TEXTURE2D_DESC desc;
			texture2D->GetDesc(&desc);

			mWidth = (uint32_t)desc.Width;
			mHeight = (uint32_t)desc.Height;
		}

	}
	void Texture::LoadFromPngData(ID3D11Device* device, ID3D11DeviceContext* deviceContext, unsigned char* pngData)
	{
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Width = mWidth;
		desc.Height = mHeight;
		desc.MipLevels = 0;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

		//D3D11_SUBRESOURCE_DATA subResource;
		//subResource.pSysMem = pngData;
		//subResource.SysMemPitch = desc.Width * 4;
		//subResource.SysMemSlicePitch = 0;

		ID3D11Texture2D* pTexture2D = nullptr;
		auto result = device->CreateTexture2D(&desc, NULL, &pTexture2D);

		UINT rowPitch = (mWidth * 4) * sizeof(unsigned char);
		deviceContext->UpdateSubresource(pTexture2D, 0, NULL, pngData, rowPitch, 0);

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));
		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = -1;
		srvDesc.Texture2D.MostDetailedMip = 0;
		result = device->CreateShaderResourceView(pTexture2D, &srvDesc, &mTexture->Texture);
	}
	*/

} // namespace cave
