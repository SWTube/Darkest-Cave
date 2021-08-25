#pragma once
//#include "Texture/Texture.h"
import Texture;

namespace cave
{

	class MultiTexture : public Texture {
	public:
		MultiTexture() = delete;
		MultiTexture(ID3D11Device* device, const std::filesystem::path& filePath, uint32_t frameCount, eTextureFormat textureFormat = eTextureFormat::RGBA, MemoryPool& pool = gCoreMemoryPool);
		MultiTexture(ID3D11Device* device, const std::filesystem::path& filePath,  uint32_t row, uint32_t column, uint32_t frameCount, eTextureFormat textureFormat = eTextureFormat::RGBA, MemoryPool& pool = gCoreMemoryPool);
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
}
