/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>

namespace cave
{
	class Tag final
	{
	public:
		Tag(const char& typeName);
		Tag(std::string& typeName);

		~Tag();

		__forceinline friend bool operator==(const Tag& lhs, const Tag& rhs)
		{
			return lhs.mType == rhs.mType;
		}

		__forceinline friend bool operator!=(const Tag& lhs, const Tag& rhs)
		{
			return lhs.mType == rhs.mType;
		}

	private:
		Tag();
		Tag(const Tag& other) = delete;
		Tag(Tag&& other) = delete;

		Tag& operator=(const Tag& other) = delete;
		Tag& operator=(const Tag&& other) = delete;

	private:
		std::string mTypeName;
		size_t mType;
	};
}