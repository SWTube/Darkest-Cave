/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include "CoreTypes.h"

namespace cave
{
	class Object
	{
	public:
		virtual ~Object();
		Object& operator=(const Object& other);
		Object& operator=(Object&& other) noexcept;

		FORCEINLINE bool operator==(const Object& other) const
		{
			return mInstanceID == other.mInstanceID;
		}

		FORCEINLINE bool operator!=(const Object& other) const
		{
			return mInstanceID != other.mInstanceID;
		}

		FORCEINLINE unsigned int GetInstanceID() const
		{
			return mInstanceID;
		}

		FORCEINLINE unsigned int GetInternalIndex() const
		{
			return mInternalIndex;
		}

		FORCEINLINE void SetFlags(unsigned char flag)
		{
			mFlags = flag;
		}

		FORCEINLINE unsigned char GetFlags() const
		{
			return mFlags;
		}

		FORCEINLINE bool IsValid() const
		{
			return mbVaild;
		}

	protected:
		Object();
		Object(const Object& other);
		Object(Object&& other) noexcept;

		FORCEINLINE void SetInstanceID(unsigned int id)
		{
			mInstanceID = id;
		}

		FORCEINLINE void SetInternalIndex(unsigned int index)
		{
			mInternalIndex = index;
		}

	private:
		unsigned char mFlags;
		unsigned int mInternalIndex;
		unsigned int mInstanceID;

		bool mbVaild;
	};
}