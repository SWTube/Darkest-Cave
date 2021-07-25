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
		, mLocation({.x = 0.f, .y = 0.f})
		, mRotation({.x = 0.f, .y = 0.f})
		, mScale({.x = 1.f, .y = 1.f})
	{

	}

	Transform::Transform(const Transform& other)
		: Object(other)
		, mLocation(other.mLocation)
		, mRotation(other.mRotation)
		, mScale(other.mScale)
	{

	}

	Transform::Transform(Transform&& other) noexcept
		: Object(std::move(other))
		, mLocation(std::move(other.mLocation))
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
		mLocation = other.mLocation;
		mRotation = other.mRotation;
		mScale = other.mScale;

		return *this;
	}

	Transform& Transform::operator=(Transform&& other) noexcept
	{
		Object::operator=(std::move(other));
		mLocation = other.mLocation;
		mRotation = other.mRotation;
		mScale = other.mScale;

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
				element->GetLocation()->x = disFloat(gen);
				element->GetLocation()->y = disFloat(gen);
				element->GetRotation()->x = disFloat(gen);
				element->GetRotation()->y = disFloat(gen);
				element->GetScale()->x = disFloat(gen);
				element->GetScale()->y = disFloat(gen);
			}

			for (auto& element : vec)
			{
				std::cout << element->GetLocation()->x << '\n';
				std::cout << element->GetLocation()->y << '\n';
				std::cout << element->GetRotation()->x << '\n';
				std::cout << element->GetRotation()->y << '\n';
				std::cout << element->GetScale()->x << '\n';
				std::cout << element->GetScale()->y << '\n';
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