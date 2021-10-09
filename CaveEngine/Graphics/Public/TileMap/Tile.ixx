module;
#include "GraphicsApiPch.h"
#include "CoreGlobals.h"

export module cave.Graphics.TileMap.Tile;
import cave.Core.Types.Float;
import cave.Core.Types.Vertex;
import TextureManager;
import cave.Core.Containers.Array;

namespace cave
{
	export struct Coords
	{
		int x;
		int y;
	};

	export struct Tile
	{
		Texture* texture = nullptr;
		uint16_t id = 0u;
		Float2 startTexCoords = {0.0f, 0.0f };
		Float2 endTexCoords = {0.0f, 0.0f};
		//std::vector<Coords> mTileCoords; // 해당 타일이 놓이는 좌표들.
		constexpr bool operator==(const Tile& other);
		constexpr bool operator<(const Tile& other);
		constexpr bool operator>(const Tile& other);
	};

	constexpr bool Tile::operator==(const Tile& other)
	{
		return (this->id == other.id);
	}

	constexpr bool Tile::operator<(const Tile& other)
	{
		return (this->id < other.id);
	}

	constexpr bool Tile::operator>(const Tile& other)
	{
		return (this->id > other.id);
	}

	export class TileGroup
	{
	public:
		TileGroup() = default;
		TileGroup(uint16_t _width, uint16_t _height, uint16_t* _tiles);
		~TileGroup();

		constexpr uint16_t* GetTiles() const;
		constexpr uint16_t GetWidth() const;
		constexpr uint16_t GetHeight() const;
	private:
		uint16_t mWidth = 0u;
		uint16_t mHeight = 0u;
		uint16_t* mTiles = nullptr;
	};

	TileGroup::TileGroup(uint16_t _width, uint16_t _height, uint16_t* _tiles)
		:mWidth(_width),
		mHeight(_height)
	{
		mTiles = reinterpret_cast<uint16_t*>(gCoreMemoryPool.Allocate(sizeof(uint16_t) * mWidth * mHeight));
		new(mTiles) uint16_t[mWidth * mHeight];

		for (size_t i = 0; i < mWidth*mHeight; i++)
		{
			mTiles[i] = _tiles[i];
		}
	}

	TileGroup::~TileGroup()
	{
		gCoreMemoryPool.Deallocate(mTiles, sizeof(uint16_t) * mWidth * mHeight);
	}

	constexpr uint16_t* TileGroup::GetTiles() const
	{
		return mTiles;
	}

	constexpr uint16_t TileGroup::GetWidth() const
	{
		return mWidth;
	}

	constexpr uint16_t TileGroup::GetHeight() const
	{
		return mHeight;
	}

}
