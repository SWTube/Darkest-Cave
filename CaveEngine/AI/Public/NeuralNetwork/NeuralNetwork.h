/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include <array>
#include <numeric>
#include <vector>

#include "CoreTypes.h"

#include "Debug/Log.h"
#include "Memory/Memory.h"
#include "opennn/opennn.h"
#include "opennn/opennn_strings.h"
// #include "tensorflow/c/c_api.h"

namespace cave
{
	class NeuralNetwork final
	{
	public:
		NeuralNetwork();

		static void DeallocateTensor(void* data, size_t, void*);
	private:
		static MemoryPool msPool;
	};

#if CAVE_BUILD_DEBUG
	namespace NeuralNetworkTest
	{
		void Test();
	} // namespace NeuralNetworkTest
	
#endif
} // namespace cave
