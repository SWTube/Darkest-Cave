/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>

#include "CoreTypes.h"
#include "Assertion/Assert.h"

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

		FORCEINLINE int GetGUID() const;
		FORCEINLINE bool IsValid() const;

		void SetName(std::string& name);
		void SetName(const char* name);
		FORCEINLINE std::string& GetName();

	protected:
		Object();
		Object(std::string& name);
		Object(const char* name);
		Object(const Object& other);
		Object(Object&& other) noexcept;

	private:
		static int mNextGUID;
		/*Object's unique ID.*/
		int mGUID = -1;

		std::string mName;
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

	FORCEINLINE int Object::GetGUID() const
	{
		assert(IsValid());
		return mGUID;
	}

	FORCEINLINE bool Object::IsValid() const
	{
		return mGUID < 0 ? false : true;
	}

	FORCEINLINE std::string& Object::GetName()
	{
		assert(IsValid());
		return mName;
	}
}