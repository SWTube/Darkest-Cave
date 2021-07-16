/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <iostream>
#include <string>

export module Log;

export namespace cave
{
	void Log(const char* log)
	{
#if _DEBUG
		std::cout << log << std::endl;
#endif // _DEBUG

	}

	void Log(std::string& log)
	{
#if _DEBUG
		std::cout << log << std::endl;
#endif // _DEBUG

	}

	void Log(char* log)
	{
#if _DEBUG
		std::cout << log << std::endl;
#endif // _DEBUG

	}
}