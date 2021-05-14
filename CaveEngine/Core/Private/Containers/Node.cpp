/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include <cstdlib>

#include "Containers/Node.h"

namespace cave
{
	Node<void*>::Node(void* data, Node* next)
		: Data(data)
		, Next(next)
	{
	}

	Node<void*>::~Node()
	{
		if (Data != nullptr)
		{
			free(Data);
		}
	}
}