#pragma once

#include "Math/Vector2.h"

namespace cave
{
	class Transform
	{
	public:
		Transform() :
			mPosition(),
			mRotation(),
			mScale()
		{
			mPosition.x = 0.f;
			mPosition.y = 0.f;

			mRotation.x = 0.f;
			mRotation.y = 0.f;

			mScale.x = 1.f;
			mScale.y = 1.f;
		}

		Transform(const Transform& other) :
			mPosition(other.mPosition),
			mRotation(other.mRotation),
			mScale(other.mScale)
		{

		}

		Transform(Transform&& other) noexcept :
			mPosition(other.mPosition),
			mRotation(other.mRotation),
			mScale(other.mScale)
		{

		}

		~Transform()
		{

		}

		Transform& operator=(const Transform& other)
		{
			return *this;
		}

		Transform& operator=(Transform&& other) noexcept
		{
			return *this;
		}

	private:
		Vector2 mPosition;
		Vector2 mRotation;
		Vector2 mScale;
	};
}