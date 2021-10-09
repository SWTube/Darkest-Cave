module;
#include "GraphicsApiPch.h"

export module cave.Graphics.TileMap.Grid;

import cave.Core.Types.Float;
import cave.Core.Types.Vertex;
import cave.Graphics.Shape.Line;

namespace cave
{
	export class Grid
	{
	public:
		Grid(Float3 position, float width, float height, uint16_t cellSize);

	private:
		//Line mHorizontalLine;
		//Line mVerticalLine;

	};

	Grid::Grid(Float3 position, float width, float height, uint16_t cellSize)
	{
	}

}