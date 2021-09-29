module;
#include <vector>
#include <filesystem>
#include "GraphicsApiPch.h"
#include "CoreGlobals.h"
#include "CoreTypes.h"

export module cave.Graphics.TileMap.TileSet;
import cave.Graphics.TileMap.TileManager;
import cave.Graphics.TileMap.Tile;
import TextureManager;
import Texture;
import MultiTexture;
import cave.Core.Types.Float;

namespace cave
{
	export class TileSet
	{
	public:
		TileSet(const std::filesystem::path& texturePath, uint16_t tileWidth, uint16_t tileHeight);
		~TileSet();

	private:
		Texture* mTileTexture;
		std::vector<Tile*> mTiles;
	};


	TileSet::TileSet(const std::filesystem::path& texturePath, uint16_t tileWidth, uint16_t tileHeight)
	{
		mTileTexture = TextureManager::GetInstance().GetOrAddTexture(texturePath);

		float x = static_cast<float>(mTileTexture->GetWidth()) / static_cast<float>(tileWidth);
		float y = static_cast<float>(mTileTexture->GetHeight()) / static_cast<float>(tileHeight);
		
		float normalizedWidth = 1.0 / x;
		float normalizedHeight = 1.0 / y;

		for (size_t i = 0; i < y; i++)
		{
			for (size_t j = 0; j < x; j++)
			{
				Tile* temp = reinterpret_cast<Tile*>(gCoreMemoryPool.Allocate(sizeof(Tile)));
				new(temp) Tile();
				temp->id = 0u;
				temp->texture = mTileTexture;
				temp->startTexCoords = { normalizedWidth * j, normalizedHeight * i };
				temp->endTexCoords = temp->startTexCoords + Float2{normalizedWidth, normalizedHeight};
				TileManager::GetInstance().AddTile(temp);
				mTiles.push_back(temp);
			}
		}
	}
	TileSet::~TileSet()
	{
		for (Tile* i : mTiles)
		{
			TileManager::GetInstance().DeleteTile(i->id);
			i->~Tile();
			gCoreMemoryPool.Deallocate(i, sizeof(Tile));
		}
		mTiles.clear();

	}

}
