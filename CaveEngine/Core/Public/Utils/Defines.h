/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "CaveEngineConfig.h"

// Turns an preprocessor token into a real string
#define STRINGIZE_TOKEN(x) STRINGIZE_TOKEN_IMPL(x)
#define STRINGIZE_TOKEN_IMPL(x) #x

// Concatenates two preprocessor tokens, performing macro expansion on them first
#define CONCATENATE_TOKENS(x, y) CONCATENATE_TOKENS_IMPL(x, y)
#define CONCATENATE_TOKENS_IMPL(x, y) x##y

// Expands to the second argument or the third argument if the first argument is 1 or 0 respectively
#define IF(cond, x, y) CONCATENATE_TOKENS(IF_IMPL_, cond)(x, y)
#define IF_IMPL_0(x, y) x
#define IF_IMPL_1(x, y) y

#ifdef CAVE_BUILD_DEBUG
	#ifdef __UNIX__
		#define FORCEINLINE __attribute__((always_inline))
	#else
		#define FORCEINLINE __forceinline
	#endif
#else
#endif

#include <stdint.h>
#include <stddef.h>