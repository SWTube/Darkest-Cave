/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#ifdef CAVE_BUILD_DEBUG
#include <random>
#include <iostream>
#include <limits>
#include <vector>
#endif // CAVE_BUILD_DEBUG


#include "Object/Transform.h"
#include "CoreGlobals.h"

namespace cave
{
	Transform::Transform()
		: Object()
		, mPosition()
		, mRotation()
		, mScale()
	{

	}

	Transform::Transform(const Transform& other)
		: Object(other)
		, mPosition(other.mPosition)
		, mRotation(other.mRotation)
		, mScale(other.mScale)
	{

	}

	Transform::Transform(Transform&& other) noexcept
		: Object(std::move(other))
		, mPosition(std::move(other.mPosition))
		, mRotation(std::move(other.mRotation))
		, mScale(std::move(other.mScale))
	{

	}

	Transform::~Transform()
	{

	}

	Transform& Transform::operator=(const Transform& other)
	{
		Object::operator=(other);
		mPosition = other.mPosition;
		mRotation = other.mRotation;
		mScale = other.mScale;

		return *this;
	}

	Transform& Transform::operator=(Transform&& other) noexcept
	{
		Object::operator=(std::move(other));
		mPosition = std::move(other.mPosition);
		mRotation = std::move(other.mRotation);
		mScale = std::move(other.mScale);

		return *this;
	}

#ifdef CAVE_BUILD_DEBUG
	namespace TransformTest
	{
		void Test()
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float> disFloat(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
			std::uniform_int_distribution<int> disInt(0, 99);

			std::vector<Transform*> vec;
			
			for (size_t i = 0; i < 100; i++)
			{
				Transform* transform = new Transform();

				vec.push_back(transform);
			}

			for (auto& element : vec)
			{
				element->GetPosition()->X = disFloat(gen);
				element->GetPosition()->Y = disFloat(gen);
				element->GetRotation()->X = disFloat(gen);
				element->GetRotation()->Y = disFloat(gen);
				element->GetScale()->X = disFloat(gen);
				element->GetScale()->Y = disFloat(gen);
			}

			for (auto& element : vec)
			{
				std::cout << element->GetPosition()->X << '\n';
				std::cout << element->GetPosition()->Y << '\n';
				std::cout << element->GetRotation()->X << '\n';
				std::cout << element->GetRotation()->Y << '\n';
				std::cout << element->GetScale()->X << '\n';
				std::cout << element->GetScale()->Y << '\n';
				std::cout << '\n' << std::endl;
			}

			for (size_t i = 0; i < 100; i++)
			{
				Transform transform((*vec[disInt(gen)]));
				Transform trans(std::move(*vec[disInt(gen)]));
			}
			
			*vec[20] = *vec[21];
			*vec[40] = std::move(*vec[41]);

			for (auto& element : vec)
			{
				delete element;
			}
		}
	}
#endif //CAVE_BUILD_DEBUG
}