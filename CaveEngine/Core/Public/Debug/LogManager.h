/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */


#pragma once

#include <iostream>

#include "CoreTypes.h"

namespace cave
{
	enum class eLogVerbosity
	{
		ALL,
		VERBOSE,
		DEBUG,
		INFO,
		WARN,
		ERROR,
		ASSERT
	};

	enum class eLogChannel
	{
		GRAPHICS = 0x00,
		PHYSICS = 0x20,
		AUDIO = 0x40,
		AI = 0x60,
		GAMEPLAY = 0x80,
		CORE = 0xa0,
		CORE_MODULE = 0xa1,
		CORE_UNIT_TEST = 0xa2,
		CORE_MEMORY = 0xa3,
		CORE_MATH = 0xa4,
		CORE_STRING = 0xa5,
		CORE_LOCALIZATION = 0xa6,
		CORE_PARSER = 0xa7,
		CORE_PROFILE = 0xa8,
		CORE_ENGINE_CONFIG = 0xa9,
		CORE_RNG = 0xaa,
		CORE_OBJECT = 0xab,
		CORE_THREAD = 0xac,
		CORE_CONTAINER = 0xad,
		CORE_FILE_SYSTEM = 0xae,
		CORE_TIMER = 0xaf,
		CORE_RESOURCE_MANAGER = 0xb0
	};

	class LogManager final
	{
	public:
		LogManager() = delete;
		LogManager(const LogManager&) = delete;
		LogManager(const LogManager&&) = delete;
		LogManager& operator=(const LogManager&) = delete;
		LogManager& operator=(const LogManager&&) = delete;

		static void SetVerbosity(eLogVerbosity verbosity);
		static void Verbose(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const char* message, std::ostream& os = std::cout);
		static void Debug(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const char* message, std::ostream& os = std::cout);
		static void Info(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const char* message, std::ostream& os = std::cout);
		static void Warn(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const char* message, std::ostream& os = std::cout);
		static void Error(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const char* message, std::ostream& os = std::cout);
		static void Assert(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const char* message, std::ostream& os = std::cout);
	private:
		static void Log(eLogChannel channel, eLogVerbosity verbosity, const char* fileName, const char* functionName, int32_t lineNumber, const char* message, std::ostream& os);
		static eLogVerbosity msCurrentVerbosity;
	};
} // namespace cave

#define LOGV(channel, message, os) cave::LogManager::Verbose(channel, __FILE__, __func__, __LINE__, message, os)
#define LOGD(channel, message, os) cave::LogManager::Debug(channel, __FILE__, __func__, __LINE__, message, os)
#define LOGI(channel, message, os) cave::LogManager::Info(channel, __FILE__, __func__, __LINE__, message, os)
#define LOGW(channel, message, os) cave::LogManager::Warn(channel, __FILE__,__func__,  __LINE__, message, os)
#define LOGE(channel, message, os) cave::LogManager::Error(channel, __FILE__, __func__, __LINE__, message, os)
#define LOGA(channel, message, os) cave::LogManager::Assert(channel, __FILE__, __func__, __LINE__, message, os)
