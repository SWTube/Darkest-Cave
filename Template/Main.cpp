/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include <cstdint>
#include <iostream>

int main(int argc, char* argv[])
{
	std::cout << "THIS IS A TEMPLATE" << std::endl;
	std::cout << "Your Command-Line Arguments are:";

	for (int i = 0; i < argc; ++i)
	{
		std::cout << " " << argv[i];
	}
	std::cout << std::endl;

	return 0;
}