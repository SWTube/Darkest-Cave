#include "pch.h"
#include "MultiTexture.h"


	//가로로 쭉 이어진 스프라이트 시트라고 가정.

	MultiTexture::~MultiTexture()
	{
	}


	void MultiTexture::Initialize(ID3D11Device* device, WCHAR* path, uint32_t frameCount, uint32_t framesPerSecond)
	{
		TextureClass::Initialize(device, path);
		mFrame = 0;
		mFrameCount = frameCount;
		mColumn = frameCount;
		mRow = 1;
		mUVPerFrame = XMFLOAT2(1.0f / float(frameCount), 1.0f);
		mEndUV = mUVPerFrame;
	}

	void MultiTexture::SetFrame(int frame)
	{
		if (frame > mFrameCount) frame = mFrameCount;
		mFrame = frame;

		float u = int(mFrame % (mColumn)) * mUVPerFrame.x;
		float v = int(mFrame / (mColumn)) % mRow * mUVPerFrame.y;
		mStartUV = XMFLOAT2(u, v);
		mEndUV = XMFLOAT2(mStartUV.x + mUVPerFrame.x,mStartUV.y + mUVPerFrame.y);
	}

