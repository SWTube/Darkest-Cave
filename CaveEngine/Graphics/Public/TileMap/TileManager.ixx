module;
#include "GraphicsApiPch.h"
#include "CoreGlobals.h"

export module cave.Graphics.TileMap.TileManager;
import cave.Core.Containers.HashTable;
import cave.Graphics.TileMap.Tile;

namespace cave
{

	export class TileManager
	{
	public:
		static TileManager& GetInstance()
		{
			static TileManager msInstance;
			return msInstance;
		}

		void AddTile(Tile* tile);
		void DeleteTile(uint16_t tileId);
		Tile* GetTile(uint16_t tileId);

	private:
		TileManager();
		TileManager(const TileManager& other) = delete;
		TileManager& operator=(const TileManager& other) = delete;
		~TileManager();
	private:
		uint16_t getNewId();
	private:
		HashTable* mTiles = nullptr;
		uint16_t mCount = 0u;
	};
	TileManager::TileManager()
	{
		mTiles = reinterpret_cast<HashTable*>(gCoreMemoryPool.Allocate(sizeof(HashTable)));
		new(mTiles) HashTable(sizeof(Tile*));
	}

	TileManager::~TileManager()
	{
		gCoreMemoryPool.Deallocate(mTiles, sizeof(HashTable));
	}

	uint16_t TileManager::getNewId()
	{
		return ++mCount;
	}

	void TileManager::AddTile(Tile* tile)
	{
		if (tile->id == 0)
		{
			tile->id = getNewId();
		}
		
		mTiles->Insert(&tile->id,tile);
	}

	void TileManager::DeleteTile(uint16_t tileId)
	{
		mTiles->Erase(&tileId);
	}

	Tile* TileManager::GetTile(uint16_t tileId)
	{
		Tile* tile = reinterpret_cast<Tile*>(mTiles->Find(&tileId));
		
		return tile;
	}
}

