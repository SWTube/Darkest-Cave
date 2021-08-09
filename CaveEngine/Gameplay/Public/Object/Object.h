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
	class Object
	{
	public:
		Object() = delete;
		Object(Object&& other)= delete;

		virtual ~Object();

		FORCEINLINE friend bool operator==(const Object& lhs, const Object& rhs);
		FORCEINLINE friend bool operator!=(const Object& lhs, const Object& rhs);
		FORCEINLINE friend bool operator<(const Object& lhs, const Object& rhs);

		FORCEINLINE uint32_t GetGUID() const;
		FORCEINLINE bool IsValid() const;
		FORCEINLINE bool IsDuplicated() const;

		FORCEINLINE const std::string& GetName() const;

	protected:
		Object(std::string& name);
		Object(const char* name);
		Object(const Object& other);

		Object& operator=(const Object& other);
		Object& operator=(Object&& other) noexcept;

	protected:
		uint32_t getDuplicatedNum() const;

	private:
		static uint32_t mNextGUID;

		Object* mDuplicatedTarget;
		uint32_t mDuplicatedNum;

		/*Object's unique ID.*/
		uint32_t mGUID = 0;

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

	FORCEINLINE uint32_t Object::GetGUID() const
	{
		assert(IsValid());
		return mGUID;
	}

	FORCEINLINE bool Object::IsValid() const
	{
		return mGUID == 0 ? false : true;
	}

	FORCEINLINE bool Object::IsDuplicated() const
	{
		assert(IsValid());
		return mDuplicatedTarget != nullptr;
	}

	FORCEINLINE const std::string& Object::GetName() const
	{
		assert(IsValid());
		return mName;
	}
}
