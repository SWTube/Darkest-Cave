/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;

#include <vector>
#include "GraphicsApiPch.h"

#include "CoreTypes.h"
#include "Containers/Vertex.h"
export module RenderQueue;

import Sprite;

namespace cave 
{
	export class RenderQueue final
	{
	public:
		static RenderQueue & GetInstance()
		{
			static RenderQueue instance;
			return instance;
		}

		void AddSprite(Sprite* sprite);
		std::vector<Sprite*> GetRenderQueue();

	private:
		RenderQueue() = default;
		RenderQueue(const RenderQueue& other) = delete;
		RenderQueue& operator=(const RenderQueue& other) = delete;
		~RenderQueue();

		std::vector<Sprite*> mSprites;
	};

	RenderQueue::~RenderQueue()
	{
		mSprites.clear();
	}
	void RenderQueue::AddSprite(Sprite* sprite)
	{
		mSprites.push_back(sprite);
	}
	
	std::vector<Sprite*> RenderQueue::GetRenderQueue()
	{
		return mSprites;
	}
}