#include "Texture/MultiTexture.h"

namespace cave {

	//가로로 쭉 이어진 스프라이트 시트라고 가정.
	MultiTexture::MultiTexture(ID3D11Device* device, const std::filesystem::path& filePath, uint32_t frameCount,eTextureFormat textureFormat, MemoryPool& pool)
		:Texture(device,filePath, textureFormat, pool)
	{
		mFrame = 0;
		mFrameCount = frameCount;
		mColumn = frameCount;
		mRow = 1;
		mUVPerFrame = Float2(1.0f / float(frameCount), 1.0f);
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

	//void MultiTexture::Init(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
	//{
	//	Texture::Init(device, deviceContext);
	//	mWidth *= mUVPerFrame.X;
	//	mHeight *= mUVPerFrame.Y;
	//}

	void MultiTexture::SetFrame(int frame)
	{
		if (frame > mFrameCount) frame = mFrameCount;
		mFrame = frame;

		float u = int(mFrame % (mColumn)) * mUVPerFrame.X;
		float v = int(mFrame / (mColumn)) % mRow * mUVPerFrame.Y;
		mStartUV = Float2(u, v);
		mEndUV = mStartUV + mUVPerFrame;
	}



}
