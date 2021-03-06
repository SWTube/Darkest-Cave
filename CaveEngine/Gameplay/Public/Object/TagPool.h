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
	class MemoryPool;

	class TagPool final
	{
	public:
		TagPool() = delete;
		TagPool(const TagPool&) = delete;
		TagPool(TagPool&&) = delete;

		~TagPool();
		
		static void Init(MemoryPool& memoryPool);
		static void ShutDown();

		static void AddTag(std::string& name);
		static void AddTag(const char* name);

		static void RemoveTag(std::string& name);
		static void RemoveTag(const char* name);

		static Tag* FindTagByName(std::string& name);
		static Tag* FindTagByName(const char* name);

		static bool IsValid();

#ifdef CAVE_BUILD_DEBUG
		static void PrintElement();
#endif // CAVE_BULID_DEBUG

	private:
		static Tag* createTag(std::string& name);

	private:
		static MemoryPool* mMemoryPool;
		static std::unordered_map<std::string, Tag*> mTags;
	};

#ifdef CAVE_BUILD_DEBUG
	namespace TagPoolTest
	{
		void Test();
	}
#endif
}