/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>
#include <unordered_set>

#include "CoreTypes.h"
#include "Assertion/Assert.h"

namespace cave
{
	class Object
	{
	public:
		Object() = delete;
		Object(const Object&) = delete;
		Object(Object&&) = delete;

		virtual ~Object();

		friend bool operator==(const Object& lhs, const Object& rhs);
		friend bool operator!=(const Object& lhs, const Object& rhs);
		friend bool operator<(const Object& lhs, const Object& rhs);

		uint32_t GetGUID() const;
		virtual bool IsValid() const;
		bool IsDuplicated() const;

		const std::string& GetName() const;

	protected:
		Object(const char* name, std::unordered_set<std::string>& nameList);
		Object(std::string& name, std::unordered_set<std::string>& nameList);
		Object(const std::string& name, std::unordered_set<std::string>& nameList);
		Object(const Object& other, std::unordered_set<std::string>& nameList);
		Object(Object&& other, std::unordered_set<std::string>& nameList) noexcept;

		Object& operator=(const Object& other);
		Object& operator=(Object&& other) noexcept;

	protected:
		uint32_t getDuplicatedNum() const;

	protected:
		Object* mDuplicatedTarget;
		uint32_t mDuplicatedNum;

		/*Object's unique ID.*/
		uint32_t mGUID = 0;

		std::string mName;

	private:
		static uint32_t mNextGUID;
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
