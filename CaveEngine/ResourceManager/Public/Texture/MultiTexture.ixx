module;
#include <filesystem>

#include "ResourceManagerApiPch.h"

#include "CoreGlobals.h"
#include "CoreTypes.h"
#include "Containers/Vertex.h"

//#include "Texture/Texture.h"
export module MultiTexture;

import Texture;
import DdsTextureLoader;
import WicTextureLoader;

namespace cave
{
	export class MultiTexture : public Texture {
	public:
		MultiTexture() = delete;
		MultiTexture(ID3D11Device* device, const std::filesystem::path& filePath, uint32_t frameCount, eTextureFormat textureFormat = eTextureFormat::RGBA, MemoryPool& pool = gCoreMemoryPool);
		MultiTexture(ID3D11Device* device, const std::filesystem::path& filePath, uint32_t row, uint32_t column, uint32_t frameCount, eTextureFormat textureFormat = eTextureFormat::RGBA, MemoryPool& pool = gCoreMemoryPool);
		MultiTexture(const MultiTexture& other);
		MultiTexture(MultiTexture&& other);
		MultiTexture& operator=(const MultiTexture& other);
		MultiTexture& operator=(MultiTexture&& other);
		virtual ~MultiTexture();

		constexpr uint32_t GetTotalWidth() const;
		constexpr uint32_t GetTotalHeight() const;
		void GetUVCoordsByFrame(uint32_t frame, Float2& startCoord, Float2& endCoord);
		void SetFrame(uint32_t frame = 0u);

	private:
		uint32_t mFrame = 0u;
		uint32_t mFrameCount = 0u;
		uint32_t mColumn = 0u;
		uint32_t mRow = 0u;
		Float2 mUVPerFrame = Float2(0.0f, 0.0f);
		uint32_t mTotalWidth = 0u;
		uint32_t mTotalHeight = 0u;
	};

	constexpr uint32_t MultiTexture::GetTotalWidth() const
	{
		return mTotalWidth;
	}
	constexpr uint32_t MultiTexture::GetTotalHeight() const
	{
		return mTotalHeight;
	}

	//가로로 쭉 이어진 스프라이트 시트라고 가정.
	MultiTexture::MultiTexture(ID3D11Device* device, const std::filesystem::path& filePath, uint32_t frameCount, eTextureFormat textureFormat, MemoryPool& pool)
		:Texture(device, filePath, textureFormat, pool)
	{
		mFrame = 0;
		mFrameCount = frameCount;
		mColumn = frameCount;
		mRow = 1;
		mUVPerFrame = Float2(1.0f / static_cast<float>(frameCount), 1.0f);
		mEndUV = mUVPerFrame;
		mTotalWidth = mWidth;
		mTotalHeight = mHeight;
		mWidth *= mUVPerFrame.X;
		mHeight *= mUVPerFrame.Y;
	}

	MultiTexture::MultiTexture(ID3D11Device* device, const std::filesystem::path& filePath, uint32_t row, uint32_t column, uint32_t frameCount, eTextureFormat textureFormat, MemoryPool& pool)
		:Texture(device, filePath, textureFormat, pool)
		, mFrame(0)
		, mFrameCount(frameCount)
		, mRow(row)
		, mColumn(column)
	{
		mUVPerFrame = Float2(1.0f / static_cast<float>(column), 1.0f / static_cast<float>(row));
		mEndUV = mUVPerFrame;
		mWidth *= mUVPerFrame.X;
		mHeight *= mUVPerFrame.Y;
	}

	MultiTexture::MultiTexture(const MultiTexture& other)
		:Texture(other)
		, mFrame(other.mFrame)
		, mFrameCount(other.mFrameCount)
		, mColumn(other.mColumn)
		, mRow(other.mRow)
		, mUVPerFrame(other.mUVPerFrame)
	{
	}

	MultiTexture::MultiTexture(MultiTexture&& other)
		: Texture(std::move(other))
		, mFrame(other.mFrame)
		, mFrameCount(other.mFrameCount)
		, mColumn(other.mColumn)
		, mRow(other.mRow)
		, mUVPerFrame(other.mUVPerFrame)
	{
		other.Destroy();
	}

	MultiTexture& MultiTexture::operator=(const MultiTexture& other)
	{
		if (this != &other)
		{
			Texture::operator=(other);
			mFrame = other.mFrame;
			mFrameCount = other.mFrameCount;
			mColumn = other.mColumn;
			mRow = other.mRow;
			mUVPerFrame = other.mUVPerFrame;
		}
		return *this;
	}

	MultiTexture& MultiTexture::operator=(MultiTexture&& other)
	{
		if (this != &other)
		{
			Texture::operator=(std::move(other));
			mFrame = other.mFrame;
			mFrameCount = other.mFrameCount;
			mColumn = other.mColumn;
			mRow = other.mRow;
			mUVPerFrame = other.mUVPerFrame;
			other.Destroy();

		}
		return *this;
	}

	MultiTexture::~MultiTexture()
	{
		Destroy();
	}

	void MultiTexture::GetUVCoordsByFrame(uint32_t frame, Float2& startCoord, Float2& endCoord)
	{
		if (frame > mFrameCount) frame = mFrameCount;

		float u = int(frame % (mColumn)) * mUVPerFrame.X;
		float v = int(frame / (mColumn)) % mRow * mUVPerFrame.Y;

		startCoord = Float2(u, v);
		endCoord = startCoord + mUVPerFrame;
	}

	void MultiTexture::SetFrame(uint32_t frame)
	{
		if (frame > mFrameCount) frame = mFrameCount;
		mFrame = frame;

		float u = int(mFrame % (mColumn)) * mUVPerFrame.X;
		float v = int(mFrame / (mColumn)) % mRow * mUVPerFrame.Y;
		mStartUV = Float2(u, v);
		mEndUV = mStartUV + mUVPerFrame;
	}
}
