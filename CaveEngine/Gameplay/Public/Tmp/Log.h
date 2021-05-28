#pragma once

#include <iostream>
#include <string>

namespace cave
{
	void Log(const char* string)
	{
#ifdef _DEBUG
		std::cout << string << std::endl;
#endif // _DEBUG
	}

	void Log(char* string)
	{
#ifdef _DEBUG
		std::cout << string << std::endl;
#endif // _DEBUG
	}

	void Log(std::string& string)
	{
#ifdef _DEBUG
		std::cout << string << std::endl;
#endif // _DEBUG
	}
}