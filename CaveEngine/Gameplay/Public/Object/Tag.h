/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>
#include <xhash>

namespace cave
{
	class Tag final
	{
	public:
		Tag();
		Tag(const char* typeName);
		Tag(const Tag& other);
		Tag(Tag&& other);

		~Tag();
		Tag& operator=(const Tag& other);
		Tag& operator=(const Tag && other);

	private:
		const char* mTypeName;
		size_t mType;
	};
}