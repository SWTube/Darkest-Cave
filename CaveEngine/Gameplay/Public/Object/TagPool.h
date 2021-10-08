/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>
#include <unordered_map>

#include "CoreTypes.h"

namespace cave
{
	class Tag;

	class TagPool final
	{
	public:
		TagPool() = delete;
		TagPool(const TagPool&) = delete;
		TagPool(TagPool&&) = delete;

		~TagPool();
		TagPool& operator=(const TagPool&) = delete;
		TagPool& operator=(TagPool&&) = delete;
		
		static void Init();
		static void ShutDown();

		static void AddTag(const char* name);
		static void AddTag(std::string& name);
		static void AddTag(const std::string& name);

		static void RemoveTag(const char* name);
		static void RemoveTag(std::string& name);
		static void RemoveTag(const std::string& name);

		static Tag* FindTagByName(const char* name);
		static Tag* FindTagByName(std::string& name);
		static Tag* FindTagByName(const std::string& name);

		static bool IsValid();

	private:
		static bool mbValid;
		static std::unordered_map<std::string, Tag*> mTags;
	};
}