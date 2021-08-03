#include "Texture/MultiTexture.h"

namespace cave {

	//가로로 쭉 이어진 스프라이트 시트라고 가정.
	MultiTexture::MultiTexture(ID3D11Device* device, const std::filesystem::path& filePath, uint32_t frameCount, Padding padding, eTextureFormat textureFormat, MemoryPool& pool)
		:Texture(device,filePath, textureFormat, pool)
	{
		mFrame = 0;
		mFrameCount = frameCount;
		mColumn = frameCount;
		mPadding = padding;
		mRow = 1;
		mUVPerFrame = Float2(1.0f / static_cast<float>(frameCount), 1.0f);
		mEndUV = mUVPerFrame;
		mTotalWidth = mWidth;
		mTotalHeight = mHeight;
		mWidth *= mUVPerFrame.X;
		mHeight *= mUVPerFrame.Y;
	}

	MultiTexture::MultiTexture(ID3D11Device* device, const std::filesystem::path& filePath, uint32_t row, uint32_t column, uint32_t frameCount, Padding padding, eTextureFormat textureFormat, MemoryPool& pool)
		:Texture(device, filePath, textureFormat, pool)
		,mFrame(0)
		,mFrameCount(frameCount)
		,mPadding(padding)
		,mRow(row)
		,mColumn(column)
	{
		mUVPerFrame = Float2(1.0f / static_cast<float>(row), 1.0f/ static_cast<float>(column));
		mEndUV = mUVPerFrame;
		mWidth *= mUVPerFrame.X;
		mHeight *= mUVPerFrame.Y;
	}

	MultiTexture::MultiTexture(const MultiTexture& other)
		:Texture(other)
		,mFrame(other.mFrame)
		,mFrameCount(other.mFrameCount)
		,mColumn(other.mColumn)
		,mRow(other.mRow)
		,mUVPerFrame(other.mUVPerFrame)
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
			mPadding = other.mPadding;
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
			mPadding = other.mPadding;
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
