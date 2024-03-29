/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "CoreGlobals.h"

import cave.Core.Containers.Hash;

namespace cave
{
	MemoryPool gCoreMemoryPool(CORE_MEMORY_POOL_SIZE);
	Hash gHash;
}