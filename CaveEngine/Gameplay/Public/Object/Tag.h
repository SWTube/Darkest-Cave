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
		friend class TagPool;

		~Tag();

		__forceinline friend bool operator==(const Tag& lhs, const Tag& rhs)
		{
			return lhs.mCompareSeed == rhs.mCompareSeed;
		}

		__forceinline friend bool operator!=(const Tag& lhs, const Tag& rhs)
		{
			return lhs.mCompareSeed != rhs.mCompareSeed;
		}

		__forceinline friend bool operator<(const Tag& lhs, const Tag& rhs)
		{
			return lhs.mCompareSeed < rhs.mCompareSeed;
		}

		__forceinline bool IsValid() const
		{
			return mbValid;
		}

		std::string& GetName();

	private:
		Tag() = delete;
		Tag(std::string& name);
		Tag(const Tag& other) = delete;
		Tag(Tag&& other) = delete;

		Tag& operator=(const Tag& other) = delete;
		Tag& operator=(const Tag&& other) = delete;

		__forceinline void setValid(bool state)
		{
			mbValid = state;
		}

	private:
		std::string mName;
		/*Used only compare tag.*/
		size_t mCompareSeed;

		bool mbValid;
	};
}