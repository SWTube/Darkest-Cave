#pragma once
#include "Texture/Texture.h"
namespace cave
{
	class MultiTexture : public Texture {
	public:
		MultiTexture() = delete;
		MultiTexture(ID3D11Device* device, const std::filesystem::path& filePath, uint32_t frameCount, eTextureFormat textureFormat = eTextureFormat::RGBA, MemoryPool& pool = gCoreMemoryPool);
		MultiTexture(const MultiTexture& other);
		MultiTexture(MultiTexture&& other);
		MultiTexture& operator=(const MultiTexture& other);
		MultiTexture& operator=(MultiTexture&& other);
		virtual ~MultiTexture();

		void SetFrame(int frame = 0);
	
	private:
		uint32_t mFrame = 0u;
		uint32_t mFrameCount = 0u;
		uint32_t mColumn = 0u;
		uint32_t mRow = 0u;

		Float2 mUVPerFrame = Float2(0.0f, 0.0f);

	};
}
