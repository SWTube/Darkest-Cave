#include "Texture/AnimationTexture.h"

namespace cave {

	//가로로 쭉 이어진 스프라이트 시트라고 가정.
	AnimationTexture::AnimationTexture(const std::filesystem::path& filePath, uint32_t frameCount, uint32_t framesPerSecond, bool isLoof,
		eTextureFormat textureFormat, MemoryPool& pool)
		:Texture(filePath, textureFormat, pool)
	{
		mFrame = 0;
		mFrameCount = frameCount;
		mColumn = frameCount;
		mRow = 1;
		mTimePerFrame = 1.0f / float(framesPerSecond);
		mTotalElapsed = 0;
		mUVPerFrame = Float2(1.0f / float(frameCount), 1.0f);
		mEndUV = mUVPerFrame;
	}

	AnimationTexture::AnimationTexture(const AnimationTexture& other)
		:Texture(other)
		,mFrame(other.mFrame)
		,mFrameCount(other.mFrameCount)
		,mColumn(other.mColumn)
		,mRow(other.mRow)
		,mTimePerFrame(other.mTimePerFrame)
		,mUVPerFrame(other.mUVPerFrame)
		,mbIsLoof(other.mbIsLoof)
		,mbIsPlay(other.mbIsPlay)
	{
	}

	AnimationTexture::AnimationTexture(AnimationTexture&& other)
		: Texture(std::move(other))
		, mFrame(other.mFrame)
		, mFrameCount(other.mFrameCount)
		, mColumn(other.mColumn)
		, mRow(other.mRow)
		, mTimePerFrame(other.mTimePerFrame)
		, mUVPerFrame(other.mUVPerFrame)
		, mbIsLoof(other.mbIsLoof)
		, mbIsPlay(other.mbIsPlay)
	{
		other.Destroy();
	}

	AnimationTexture& AnimationTexture::operator=(const AnimationTexture& other)
	{
		if (this != &other) 
		{
			Texture::operator=(other);
			mFrame = other.mFrame;
			mFrameCount = other.mFrameCount;
			mColumn = other.mColumn;
			mRow = other.mRow;
			mTimePerFrame = other.mTimePerFrame;
			mUVPerFrame = other.mUVPerFrame;
			mbIsLoof = other.mbIsLoof;
			mbIsPlay = other.mbIsPlay;
		}
		return *this;
	}

	AnimationTexture& AnimationTexture::operator=(AnimationTexture&& other)
	{
		if (this != &other)
		{
			Texture::operator=(std::move(other));
			mFrame = other.mFrame;
			mFrameCount = other.mFrameCount;
			mColumn = other.mColumn;
			mRow = other.mRow;
			mTimePerFrame = other.mTimePerFrame;
			mUVPerFrame = other.mUVPerFrame;
			mbIsLoof = other.mbIsLoof;
			mbIsPlay = other.mbIsPlay;

			other.Destroy();
			
		}
		return *this;
	}

	AnimationTexture::~AnimationTexture()
	{
		Destroy();
	}

	void AnimationTexture::Init(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
	{
		Texture::Init(device, deviceContext);
		mWidth *= mUVPerFrame.X;
		mHeight *= mUVPerFrame.Y;
	}

	bool AnimationTexture::IsAnimation() const
	{
		return true;
	}

	void AnimationTexture::Update() 
	{
		if (!mbIsPlay) return;

		mTotalElapsed += tempElapsed;
		if (mTotalElapsed > mTimePerFrame) {
			Next();
		}

	}

	void AnimationTexture::Next()
	{
		++mFrame;
		if (mFrame > mFrameCount) {
			if (mbIsLoof) mFrame = 0;
			else {
				mbIsPlay = false;
				return;
			}
		}

		mTotalElapsed -= mTimePerFrame;

		float u = int(mFrame % (mColumn)) * mUVPerFrame.X;
		float v = int(mFrame / (mColumn)) % mRow * mUVPerFrame.Y;
		mStartUV = Float2(u, v);
		mEndUV = mStartUV + mUVPerFrame;
	}

}
