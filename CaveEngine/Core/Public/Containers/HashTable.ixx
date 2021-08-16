/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "CoreGlobals.h"

export module HashTable;

namespace cave
{
	export class HashTable
	{
	public:
		HashTable();
		HashTable(MemoryPool& pool);
	protected:
		MemoryPool* mPool;
	};
}