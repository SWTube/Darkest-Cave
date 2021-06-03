#include <iostream>

#include "Tmp/Log.h"

namespace cave
{
	extern void Log(const char* string)
	{
#ifdef _DEBUG
		std::cout << string << std::endl;
#endif // _DEBUG
	}

	extern void Log(char* string)
	{
#ifdef _DEBUG
		std::cout << string << std::endl;
#endif // _DEBUG
	}

	extern void Log(std::string& string)
	{
#ifdef _DEBUG
		std::cout << string << std::endl;
#endif // _DEBUG
	}
}