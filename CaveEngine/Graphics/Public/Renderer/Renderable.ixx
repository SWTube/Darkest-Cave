/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "GraphicsApiPch.h"
#include "CoreGlobals.h"
#include "CoreTypes.h"
#include "Containers/Vertex.h"
//#include "Texture/Texture.h"

export module Renderable;
export import RenderQueue;


namespace cave {
	export class Renderable
	{
	public:
		Renderable(/*gameObject owner*/);
		Renderable(const Renderable& other) = delete;
		Renderable(Renderable&& other) = delete;
		Renderable& operator=(const Renderable& other) = delete;
		Renderable& operator=(Renderable&& other) = delete;

		virtual ~Renderable();
		
		virtual void Destroy();
		void Render(/*gameObject owner*/);

	protected:
		virtual void update() = 0;
		virtual RenderCommand makeRenderCommand() = 0;

	protected:

	};

	Renderable::Renderable()
	{

	}

	Renderable::~Renderable() 
	{
		Destroy();
	}

	void Renderable::Destroy()
	{

	}

	void Renderable::Render(/*gameObject owner*/)
	{
		/*
		* gameObject 이용해서 위치정보 얻어오기.
		*/
		update();

		RenderCommand command = makeRenderCommand(/*gameObject owner*/);
	
		RenderQueue::GetInstance().AddRenderCommand(command);
		
	}

}
