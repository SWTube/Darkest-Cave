#pragma once

#include <string>

namespace cave
{
	void Log(const char* string);

	void Log(char* string);

	void Log(std::string& string);
}