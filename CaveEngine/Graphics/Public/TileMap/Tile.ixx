module;
#include "GraphicsApiPch.h"
#include "CoreGlobals.h"

export module cave.Graphics.TileMap.Tile;
import cave.Core.Types.Float;
import cave.Core.Types.Vertex;
import TextureManager;

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
	};
}
