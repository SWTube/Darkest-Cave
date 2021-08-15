module;

#include "GraphicsApiPch.h"
#include "CoreGlobals.h"
#include "CoreTypes.h"
#include "Containers/Vertex.h"
//#include "Texture/Texture.h"

export module Renderable;
import Texture;
import MultiTexture;
import RenderQueue;
import Sprite;

namespace cave {
	export class Renderable
	{
	public:
		Renderable();
		Renderable(const Renderable& other) = delete;
		Renderable(Renderable&& other) = delete;
		Renderable& operator=(const Renderable& other) = delete;
		Renderable& operator=(Renderable&& other) = delete;

		virtual ~Renderable();
		
		void Destroy();
		void Render(/*gameObject owner*/);
		void SetTexture(Texture* texture);
		void SetTextureWithFilePath(const std::filesystem::path& filePath);
		constexpr void SetFlipX(bool flip);
		constexpr void SetFlipY(bool flip);

	private:
		void createSprite();
		Sprite* mSprite = nullptr;
		

	};

	Renderable::Renderable()
	{
		createSprite();
	}

	Renderable::~Renderable() 
	{
		Destroy();
	}

	void Renderable::Destroy()
	{
		mSprite->~Sprite();
		gCoreMemoryPool.Deallocate(mSprite,sizeof(Sprite));
	}

	void Renderable::Render(/*gameObject owner*/)
	{
		/*
		* gameObject 이용해서 위치정보 얻어오기.
		*/


		if (mSprite != nullptr) 
		{
			RenderQueue::GetInstance().AddSprite(mSprite);
		}

	}

	void Renderable::SetTexture(Texture* texture) 
	{
		mSprite->SetTexture(texture);
	}

	void Renderable::SetTextureWithFilePath(const std::filesystem::path& filePath) 
	{
		mSprite->SetTextureWithFilePath(filePath);
	}

	constexpr void Renderable::SetFlipX(bool flip)
	{
		if (mSprite != nullptr) 
		{
			mSprite->SetFlipX(flip);
		}
	}

	constexpr void Renderable::SetFlipY(bool flip)
	{
		if (mSprite != nullptr)
		{
			mSprite->SetFlipY(flip);
		}
	}

	void Renderable::createSprite()
	{
		mSprite = reinterpret_cast<Sprite*>(gCoreMemoryPool.Allocate(sizeof(Sprite)));
		new(mSprite) cave::Sprite();
		mSprite->SetPosition(400,400);
	}
}
