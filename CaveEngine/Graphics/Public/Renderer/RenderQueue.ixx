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

import TextureManager;

namespace cave 
{
	export struct RenderCommand 
	{
		VertexT* vertexData = nullptr;
		//WORD* indexData = nullptr;
		Texture* texture = nullptr;
		uint32_t zIndex = 0u;
		uint32_t bufferKey = 0u;
	};


	export class RenderQueue final
	{
	public:
		static RenderQueue & GetInstance()
		{
			static RenderQueue instance;
			return instance;
		}

		void AddRenderCommand(RenderCommand RenderCommand);
		std::vector<RenderCommand> GetRenderQueue();
		void ClearRenderQueue();
	private:
		RenderQueue() = default;
		RenderQueue(const RenderQueue& other) = delete;
		RenderQueue& operator=(const RenderQueue& other) = delete;
		~RenderQueue();

		std::vector<RenderCommand> mRenderCommands;
	};

	RenderQueue::~RenderQueue()
	{
		mRenderCommands.clear();
	}
	void RenderQueue::AddRenderCommand(RenderCommand RenderCommand)
	{
		mRenderCommands.push_back(RenderCommand);
	}
	
	std::vector<RenderCommand> RenderQueue::GetRenderQueue()
	{
		return mRenderCommands;
	}
	
	void RenderQueue::ClearRenderQueue()
	{
		mRenderCommands.clear();
	}
}