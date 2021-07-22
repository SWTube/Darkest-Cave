/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "CoreTypes.h"
#include "Assertion/Assert.h"

namespace cave
{
	class GameObject;

	class Tag final
	{
	public:
		friend class TagPool;

		Tag() = delete;
		Tag(const Tag& other) = delete;
		Tag(Tag&& other) = delete;

		~Tag();
		Tag& operator=(const Tag& other) = delete;
		Tag& operator=(const Tag&& other) = delete;

		friend bool operator==(const Tag& lhs, const Tag& rhs);
		friend bool operator==(const Tag& lhs, std::string& rhs);
		friend bool operator==(const Tag& lhs, const char* rhs);
		friend bool operator!=(const Tag& lhs, const Tag& rhs);
		friend bool operator!=(const Tag& lhs, std::string& rhs);
		friend bool operator!=(const Tag& lhs, const char* rhs);
		friend bool operator<(const Tag& lhs, const Tag& rhs);

		bool IsValid() const;

#ifdef CAVE_BUILD_DEBUG
		std::string& GetName();
#endif // CAVE_BUILD_DEBUG

	private:
		Tag(std::string& name);
		Tag(const char* name);

	private:
		std::string mName;
		size_t mNameHashCode;

		bool mbValid = false;
	};
}