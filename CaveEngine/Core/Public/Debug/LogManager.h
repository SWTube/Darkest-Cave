/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */


#pragma once

#include <cstdarg>
#include <iostream>

#include "CoreTypes.h"

namespace cave
{
	constexpr size_t MAX_BUFFER = 81;

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
		static void Verbose(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message);
		static void VerboseF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message, ...);
		static void Debug(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message);
		static void DebugF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message, ...);
		static void Info(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message);
		static void InfoF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message, ...);
		static void Warn(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message);
		static void WarnF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message, ...);
		static void Error(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message);
		static void ErrorF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message, ...);
		static void Assert(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message);
		static void AssertF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message, ...);
	private:
		static void log(eLogChannel channel, eLogVerbosity verbosity, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message);
		static eLogVerbosity msCurrentVerbosity;
		static char mBuffer[MAX_BUFFER];
	};
} // namespace cave

#define LOGVF(channel, os, message, ...) cave::LogManager::VerboseF(channel, __FILE__, __func__, __LINE__, os, message, __VA_ARGS__)
#define LOGV(channel, os, message) cave::LogManager::Verbose(channel, __FILE__, __func__, __LINE__, os, message)
#define LOGDF(channel, os, message, ...) cave::LogManager::DebugF(channel, __FILE__, __func__, __LINE__, os, message, __VA_ARGS__)
#define LOGD(channel, os, message) cave::LogManager::Debug(channel, __FILE__, __func__, __LINE__, os, message)
#define LOGIF(channel, os, message, ...) cave::LogManager::InfoF(channel, __FILE__, __func__, __LINE__, os, message, __VA_ARGS__)
#define LOGI(channel, os, message) cave::LogManager::Info(channel, __FILE__, __func__, __LINE__, os, message)
#define LOGWF(channel, os, message, ...) cave::LogManager::WarnF(channel, __FILE__,__func__,  __LINE__, os, message, __VA_ARGS__)
#define LOGW(channel, os, message) cave::LogManager::Warn(channel, __FILE__,__func__,  __LINE__, os, message)
#define LOGEF(channel, os, message, ...) cave::LogManager::Error(Fchannel, __FILE__, __func__, __LINE__, os, message, __VA_ARGS__)
#define LOGE(channel, os, message) cave::LogManager::Error(channel, __FILE__, __func__, __LINE__, os, message)
#define LOGAF(channel, os, message, ...) cave::LogManager::AssertF(channel, __FILE__, __func__, __LINE__,  os, message, __VA_ARGS__)
#define LOGA(channel, os, message) cave::LogManager::Assert(channel, __FILE__, __func__, __LINE__,  os, message)