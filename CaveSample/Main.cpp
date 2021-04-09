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
	// prints verbose log message "Hello, World!" to Core channel stdout
	LOGV(eLogChannel::CORE, "Hello, World!", std::cout);
	// prints debug log message "Hello, World!" to Core channel stdout
	LOGD(eLogChannel::CORE, "Hello, World!", std::cout);
	// prints informational log message "Hello, World!" to Core channel stdout
	LOGI(eLogChannel::CORE, "Hello, World!", std::cout);
	// prints warning log message "Hello, World!" to Core channel stdout
	LOGW(eLogChannel::CORE, "Hello, World!", std::cout);
	// prints error log message "Hello, World!" to Core channel stdout
	LOGE(eLogChannel::CORE, "Hello, World!", std::cout);
	// prints assert log message "Hello, World!" to Core channel stdout
	LOGA(eLogChannel::CORE, "Hello, World!", std::cout);
	// Initialize Memory
	// Initialize File System Manager
	// Initialize Video Manager
	// Initialialize Render Manager
	// Initialize Animation Manager
	// Initialize Physics Manager
	// Initialize Game Manager

	RunGame();
}

void RunGame()
{

}
