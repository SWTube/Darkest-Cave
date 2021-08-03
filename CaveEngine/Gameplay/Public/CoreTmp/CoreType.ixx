/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <string>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32


export module CoreType;

export namespace cave
{
	using uint8 = unsigned char;
	using uint16 = unsigned short;
	using uint32 = unsigned int;
	using uint64 = unsigned long long;

	using int8 = char;
	using int16 = short;
	using int32 = int;
	using int64 = long long;

	using EventCode = short;
}

export namespace cave
{
#ifdef _WIN32
	using TimePoint = unsigned long long;
#endif // _WIN32

}