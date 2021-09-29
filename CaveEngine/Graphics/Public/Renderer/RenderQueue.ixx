/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;

#include <vector>
#include "GraphicsApiPch.h"

#include "CoreTypes.h"

export module RenderQueue;

import cave.Core.Types.Vertex;
import cave.Core.String;
import TextureManager;

namespace cave 
{
	export struct RenderCommand 
	{
		enum eType
		{
			UNKNOWN_COMMAND,
			SPRITE_COMMAND,
			TEXT_COMMAND,
		};

		eType type = RenderCommand::eType::UNKNOWN_COMMAND;
		uint32_t zIndex = 0u;
	};
	export struct SpriteCommand : RenderCommand
	{
		VertexT* vertexData = nullptr;
		//WORD* indexData = nullptr;
		Texture* texture = nullptr;
	};
	export struct TextCommand : RenderCommand
	{
		IDWriteTextLayout* textLayout;
		Float3 position = { 0,0,0 };
		D2D1::ColorF color = { 0,0,0,1 };
	};


	export class RenderQueue final
	{
	public:
		static RenderQueue & GetInstance()
		{
			static RenderQueue instance;
			return instance;
		}

		void AddRenderCommand(RenderCommand* RenderCommand);
		std::vector<RenderCommand*> GetRenderQueue();
		void ClearRenderQueue();
	private:
		RenderQueue() = default;
		RenderQueue(const RenderQueue& other) = delete;
		RenderQueue& operator=(const RenderQueue& other) = delete;
		~RenderQueue();

		std::vector<RenderCommand*> mRenderCommands;
	};

	RenderQueue::~RenderQueue()
	{
		mRenderCommands.clear();
	}
	void RenderQueue::AddRenderCommand(RenderCommand* RenderCommand)
	{
		mRenderCommands.push_back(RenderCommand);
	}
	
	std::vector<RenderCommand*> RenderQueue::GetRenderQueue()
	{
		return mRenderCommands;
	}
	
	void RenderQueue::ClearRenderQueue()
	{
		mRenderCommands.clear();
	}
}