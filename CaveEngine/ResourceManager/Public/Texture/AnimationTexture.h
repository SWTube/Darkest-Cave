#pragma once
#include "Texture/Texture.h"
namespace cave
{
	class AnimationTexture : public Texture {
	public:
		AnimationTexture() = delete;
		AnimationTexture(const std::filesystem::path& filePath, uint32_t frameCount, uint32_t framesPerSecond, bool isLoof = true, 
			eTextureFormat textureFormat = eTextureFormat::RGBA, MemoryPool& pool = gCoreMemoryPool);
		AnimationTexture(const AnimationTexture& other);
		AnimationTexture(AnimationTexture&& other);
		AnimationTexture& operator=(const AnimationTexture& other);
		AnimationTexture& operator=(AnimationTexture&& other);
		virtual ~AnimationTexture();

		virtual void Init(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
		virtual bool IsAnimation() const override;

		virtual void Update() override;
		void Next();
	
	private:
		uint32_t mFrame = 0u;
		uint32_t mFrameCount = 0u;
		uint32_t mColumn = 0u;
		uint32_t mRow = 0u;
		float mTimePerFrame = 0;
		float mTotalElapsed = 0;

		bool mbIsPlay = true;
		bool mbIsLoof = true;

		Float2 mUVPerFrame = Float2(0.0f, 0.0f);

		float tempElapsed = 0.01f; // (임시)업데이트 간 간격
	};
}
