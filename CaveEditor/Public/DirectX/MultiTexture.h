#pragma once
#include "framework.h"
#include "TextureClass.h"

	class MultiTexture : public TextureClass {
	public:
		MultiTexture() = delete;
		virtual ~MultiTexture();

		virtual void Initialize(ID3D11Device*, WCHAR*, uint32_t frameCount, uint32_t framesPerSecond);
		void SetFrame(int frame = 0);
	
	private:
		uint32_t mFrame = 0u;
		uint32_t mFrameCount = 0u;
		uint32_t mColumn = 0u;
		uint32_t mRow = 0u;
		XMFLOAT2 mUVPerFrame = XMFLOAT2(0.0f, 0.0f);

	};

