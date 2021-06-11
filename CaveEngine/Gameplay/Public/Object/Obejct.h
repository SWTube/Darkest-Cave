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
	class Quaternion;

	class Object
	{
	public:
		virtual ~Object();
		Object& operator=(const Object& other);
		Object& operator=(Object&& other) noexcept;

		__forceinline bool operator==(const Object& other) const
		{
			return mInstanceID == other.mInstanceID;
		}

		__forceinline bool operator!=(const Object& other) const
		{
			return mInstanceID != other.mInstanceID;
		}

		unsigned int GetInstanceID();
		const char* ToString();

		unsigned int GetInternalIndex() const;

		bool CompareTag(unsigned int Tag);

		void Print();

	protected:
		Object();
		Object(const Object& other);
		Object(Object&& other) noexcept;

		void Initialize();

		void SetOwner(Object& owner);
		void SetInstanceID(unsigned int id);

	private:
		Object* mOwner;

		std::string mName;
		unsigned int mTag;

		unsigned char mHideFlags;
		unsigned int mInternalIndex;
		unsigned int mInstanceID;
	};
}