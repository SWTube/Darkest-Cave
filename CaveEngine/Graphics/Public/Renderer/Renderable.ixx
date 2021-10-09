/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "GraphicsApiPch.h"
#include "CoreGlobals.h"
#include "CoreTypes.h"

export module Renderable;

export import RenderQueue;

import cave.Core.Types.Float;
import cave.Core.Types.Vertex;
import DeviceResources;

namespace cave 
{
	enum RenderType 
	{
		UNKNOWN,
		SPRITE,
		TEXT,
		TILEMAP
	};

	export class Renderable
	{

	public:
		Renderable(/*gameObject owner*/);
		Renderable(const Renderable& other);
		Renderable(Renderable&& other);
		Renderable& operator=(const Renderable& other);
		Renderable& operator=(Renderable&& other);

		virtual ~Renderable();
		
		virtual void Destroy();
		void Render(/*gameObject owner*/);

		constexpr void SetPosition(float x, float y);
		constexpr void SetPosition(const Float2& position);
		constexpr void SetPosition(const Float2&& position);
		constexpr void SetZIndex(const uint32_t z);
		constexpr void SetAngle(const float angle);

		constexpr void Move(float x, float y);		
		constexpr void Move(Float2 movement);
		constexpr float GetPositionX() const;
		constexpr float GetPositionY() const;
		constexpr Float2 GetPosition() const;

	protected:
		friend class Renderer;

		virtual void init(DeviceResources* deviceResource) {};
		virtual void update() = 0;
		virtual void creatRenderCommand() = 0;
		//virtual void destroyRenderCommand() = 0;
		virtual void makeRenderCommand() = 0;

	protected:
		RenderType mType = RenderType::UNKNOWN;
		uint32_t mZIndex = 0u;
		Float3 mPosition = Float3(0, 0, 0);
		float mAngle = 0.0f;

	protected:
		RenderCommand* mCommand = nullptr;

	};

	Renderable::Renderable()
		:mZIndex(0u),
		mPosition(Float3(0, 0, 0)),
		mCommand(nullptr)
	{

	}

	Renderable::Renderable(const Renderable& other)
		:mZIndex(other.mZIndex),
		mPosition(other.mPosition),
		mCommand(nullptr)

	{
	}

	Renderable::Renderable(Renderable&& other)
		:mZIndex(other.mZIndex),
		mPosition(other.mPosition),
		mCommand(nullptr)
	{
	}

	Renderable& Renderable::operator=(const Renderable& other)
	{
		if (this != &other)
		{
			mPosition = other.mPosition;
			mZIndex = other.mZIndex;

			mCommand = nullptr; // render�� nullptr�̸� �ڵ����� �������.
		}
		return *this;
	}

	Renderable& Renderable::operator=(Renderable&& other)
	{
		if (this != &other)
		{
			mPosition = other.mPosition;
			mZIndex = other.mZIndex;

			mCommand = other.mCommand; // render�� nullptr�̸� �ڵ����� �������.
			other.mCommand = nullptr;
		}

		return *this;
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
		if (mCommand == nullptr)
		{
			creatRenderCommand();
		}
		/*
		* gameObject �̿��ؼ� ��ġ���� ������.
		*/
		update();

		makeRenderCommand(/*gameObject owner*/);
	
		RenderQueue::GetInstance().AddRenderCommand(mCommand);
		
	}

	constexpr void Renderable::SetPosition(float x, float y)
	{
		mPosition.X = x;
		mPosition.Y = y;
	}

	constexpr void Renderable::SetPosition(const Float2& position)
	{
		mPosition.X = position.X;
		mPosition.Y = position.Y;
	}

	constexpr void Renderable::SetPosition(const Float2&& position)
	{
		mPosition.X = position.X;
		mPosition.Y = position.Y;
	}

	inline constexpr void Renderable::SetZIndex(const uint32_t z)
	{
		mZIndex = z;
		mPosition.Z = 1.0f - static_cast<float>(z) * 0.01f;
	}
	
	constexpr void Renderable::SetAngle(const float angle)
	{
		mAngle = angle;
	}

	constexpr void Renderable::Move(float x, float y)
	{
		if (mPosition.X <= FLT_MAX - x)
		{
			mPosition.X += x;
		}
		else
		{
			mPosition.X = FLT_MAX;
		}

		if (mPosition.Y <= FLT_MAX - y)
		{
			mPosition.Y += y;
		}
		else
		{
			mPosition.Y = FLT_MAX;
		}
	}
	constexpr void Renderable::Move(Float2 movement)
	{
		if (mPosition.X <= FLT_MAX - movement.X)
		{
			mPosition.X += movement.X;
		}
		else
		{
			mPosition.X = FLT_MAX;
		}

		if (mPosition.Y <= FLT_MAX - movement.Y)
		{
			mPosition.Y += movement.Y;
		}
		else
		{
			mPosition.Y = FLT_MAX;
		}
	}

	constexpr float Renderable::GetPositionX() const
	{
		return mPosition.X;
	}

	constexpr float Renderable::GetPositionY() const
	{
		return mPosition.Y;
	}

	constexpr Float2 Renderable::GetPosition() const
	{
		return Float2(mPosition.X, mPosition.Y);
	}

}
