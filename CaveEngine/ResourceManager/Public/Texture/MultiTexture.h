#pragma once
#include "Texture/Texture.h"
namespace cave
{
	typedef struct Padding {
		uint16_t top = 0u;
		uint16_t right = 0u;
		uint16_t bottom = 0u;
		uint16_t left = 0u;
		
		Padding() = default;
		Padding(const Padding& other) = default;
		Padding& operator=(const Padding& other) = default;
		constexpr Padding(uint16_t top, uint16_t right, uint16_t bottom, uint16_t left);
		constexpr Padding(const Padding&& other);
		constexpr Padding& operator=(const Padding&& other);
		constexpr bool operator==(const Padding& other);
	}Padding;
	constexpr Padding::Padding(uint16_t _top, uint16_t _right, uint16_t _bottom, uint16_t _left)
		:top(_top),
		right(_right),
		bottom(_bottom),
		left(_left)
	{

	}
	constexpr Padding::Padding(const Padding&& other) {
		if (this != &other) {
			top = other.top;
			right = other.right;
			bottom = other.bottom;
			left = other.left;
		}
	}
	constexpr Padding& Padding::operator=(const Padding&& other) {
		if (this != &other) {
			top = other.top;
			right = other.right;
			bottom = other.bottom;
			left = other.left;
		}
		return *this;
	}
	constexpr bool Padding::operator==(const Padding& other) {
		return (top == other.top) && (right == other.right) && (bottom == other.bottom) && (left == other.left);
	}

	class MultiTexture : public Texture {
	public:
		MultiTexture() = delete;
		MultiTexture(ID3D11Device* device, const std::filesystem::path& filePath, uint32_t frameCount, Padding padding = Padding(), eTextureFormat textureFormat = eTextureFormat::RGBA, MemoryPool& pool = gCoreMemoryPool);
		MultiTexture(ID3D11Device* device, const std::filesystem::path& filePath,  uint32_t row, uint32_t column, uint32_t frameCount, Padding padding = Padding(), eTextureFormat textureFormat = eTextureFormat::RGBA, MemoryPool& pool = gCoreMemoryPool);
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
		Padding mPadding = Padding(0u, 0u, 0u, 0u);
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
