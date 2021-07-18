/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include "CoreTypes.h"

namespace cave
{
	class MemoryPool;

	class Object
	{
	public:
		virtual ~Object();
		Object& operator=(const Object& other);
		Object& operator=(Object&& other) noexcept;

		FORCEINLINE friend bool operator==(const Object& lhs, const Object& rhs);
		FORCEINLINE friend bool operator!=(const Object& lhs, const Object& rhs);
		FORCEINLINE friend bool operator<(const Object& lhs, const Object& rhs);

		int GetGUID() const;

		void SetFlags(unsigned char flag);
		unsigned char GetFlags() const;

		bool IsValid() const;

	protected:
		Object();
		Object(const Object& other);
		Object(Object&& other) noexcept;

	private:
		static int mNextGUID;
		unsigned char mFlags = 0;
		/*Object's unique ID.*/
		int mGUID = -1;
	};

	FORCEINLINE bool operator==(const Object& lhs, const Object& rhs)
	{
		return lhs.GetGUID() == rhs.GetGUID();
	}

	FORCEINLINE bool operator!=(const Object& lhs, const Object& rhs)
	{
		return lhs.GetGUID() != rhs.GetGUID();
	}

	FORCEINLINE bool operator<(const Object& lhs, const Object& rhs)
	{
		return lhs.GetGUID() < rhs.GetGUID();
	}
}