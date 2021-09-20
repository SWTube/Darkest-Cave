/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;

#include "Utils/Crt.h"

export module cave.Core.Containers.CompareItemType;

export namespace cave
{
	enum class eCompareItem : uint8_t
	{
		LESS,
		EQUAL,
		GREATER
	};

	namespace CompareItem
	{
		typedef eCompareItem(*Type)(void*, void*);

		constexpr eCompareItem DefaultFunction(void* leftItem, void* rightItem)
		{
			if (leftItem < rightItem)
			{
				return eCompareItem::LESS;
			}

			if (leftItem > rightItem)
			{
				return eCompareItem::GREATER;
			}

			return eCompareItem::EQUAL;
		}
	}
}