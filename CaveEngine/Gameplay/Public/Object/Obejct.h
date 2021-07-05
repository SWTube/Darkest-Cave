/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

namespace cave
{
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

		__forceinline unsigned int GetInstanceID() const
		{
			return mInstanceID;
		}

		__forceinline unsigned int GetInternalIndex() const
		{
			return mInternalIndex;
		}

		__forceinline bool IsValid() const
		{
			return mbVaild;
		}

	protected:
		Object();
		Object(const Object& other);
		Object(Object&& other) noexcept;

		__forceinline void SetOwner(Object& owner)
		{
			mOwner = &owner;
		}

		__forceinline void SetInstanceID(unsigned int id)
		{
			mInstanceID = id;
		}

		__forceinline void SetInternalIndex(unsigned int index)
		{
			mInternalIndex = index;
		}

	private:
		Object* mOwner;

		unsigned char mFlags;
		unsigned int mInternalIndex;
		unsigned int mInstanceID;

		bool mbVaild;
	};
}