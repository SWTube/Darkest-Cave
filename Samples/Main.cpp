/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include <iostream>

#include "Core.h"

using namespace cave;

void InitGame();
void RunGame();

int main(int argc, char* argv[])
{
	InitGame();

	return 0;
}

void InitGame()
{
	LOGI(eLogChannel::CORE, "Hi!", std::cout);
	// Initialize Memory
	// Initialize File System Manager
	// Initialize Video Manager
	// Initialialize Render Manager
	// Initialize Animation Manager
	// Initialize Physics Manager
	// Initialize Game Manager

	RunGame();
	LOGE(eLogChannel::CORE, "hi", std::cout);
}

void RunGame()
{

}
