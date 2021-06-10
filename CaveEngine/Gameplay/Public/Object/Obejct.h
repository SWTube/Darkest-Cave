/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>
#include <vector>

#include "Math/Vector2.h"

namespace cave
{
	class Type;
	class Transform;
	class Vector3;
	class Quaternion;

	class Object
	{
	public:
		Object();
		Object(const Object& other);
		Object(Object&& other) noexcept;
		
		virtual ~Object();
		Object& operator=(const Object& other);
		Object& operator=(Object&& other) noexcept;

		static void Destroy(Object& target, float timeDelay = 0.f);
		static void DestroyImmediate(Object& target);
		static void DontDestroyOnLoad(Object& target);

		static Object& FindObjectOfType(Type& type);
		static Object& FindObjectsOfType(Type& type, bool includeInactive = false);

		static Object& Instantiate(Object& original);
		static Object& Instantiate(Object& original, Transform& parent);
		static Object& Instantiate(Object& original, Vector3& position, Quaternion& rotation);
		static Object& Instantiate(Object& original, Vector3& position, Quaternion& rotation, Transform& parent);

		unsigned int GetInstanceID();
		const char* ToString();

		unsigned int GetInternalIndex() const;

		bool CompareTag(unsigned int Tag);

		void Print();

	private:
		void Initialize();

		void SetOwner(Object& owner);
		void SetInstanceID(unsigned int id);

	private:
		Object* mOwner = nullptr;

		const char* mName;
		const char* mTag;

		Vector2 mTransform;

		unsigned char mHideFlags;
		unsigned int mInternalIndex;
		unsigned int mInstanceID;
	};

	void Swap(Object& left, Object& right);
}