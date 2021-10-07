/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <cstdarg>
#include <cstdio>
#include <format>
#include <iostream>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>
#include <thread>

#include "Utils/Crt.h"

#include <windows.h>

#include "CoreTypes.h"

#include "Assertion/Assert.h"

export module cave.Core.Debug.Log;

namespace cave
{
	export enum class eLogVerbosity
	{
		All,
		Verbose,
		Debug,
		Info,
		Warn,
		Error,
		Assert,
		Count,
	};

	export enum class eLogChannel
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

	namespace Log
	{
		constexpr uint32_t MAX_BUFFER = 255u;
		eLogVerbosity gCurrentVerbosity = eLogVerbosity::All;
		char gBuffer[MAX_BUFFER] = { '\0', };
		wchar_t gWBuffer[MAX_BUFFER] = { '\0', };
		std::queue<std::string> gStringQueue;
		std::queue<std::wstring> gWStringQueue;
		bool gbStringPrinting = true;
		bool gbWStringPrinting = true;
		std::ostringstream gOs;
		std::wostringstream gWOs;

		export void SetVerbosity(eLogVerbosity verbosity)
		{
			gCurrentVerbosity = verbosity;
		}

#ifdef __WIN32__
		export void Initialize();
		export void Destroy();
		void ProcessLog();
		void Log(eLogChannel channel, eLogVerbosity verbosity, const char* fileName, const char* functionName, int32_t lineNumber, const char* message);
		void WLog(eLogChannel channel, eLogVerbosity verbosity, const char* fileName, const char* functionName, int32_t lineNumber, const wchar_t* message);

		std::thread gThread;
		std::mutex gQueueMutex;

		void Initialize()
		{
			gThread = std::thread(ProcessLog);
		}

		void Destroy()
		{
			gbStringPrinting = false;
			gbWStringPrinting = false;
			gThread.join();
		}

		void ProcessLog()
		{
			while (gbStringPrinting && gbWStringPrinting)
			{	
				std::lock_guard<std::mutex> lock(gQueueMutex);
				while (!gStringQueue.empty())
				{
					OutputDebugStringA(gStringQueue.front().c_str());
					gStringQueue.pop();
				}

				while (!gWStringQueue.empty())
				{
					OutputDebugStringW(gWStringQueue.front().c_str());
					gWStringQueue.pop();
				}
			}
		}

		export void Verbose(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const char* message)
		{
			Log(channel, eLogVerbosity::Verbose, fileName, functionName, lineNumber, message);
		}

		export void VerboseF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const char* message, ...)
		{
			va_list vl;
			va_start(vl, message);
			vsnprintf(gBuffer, MAX_BUFFER, message, vl);
			Log(channel, eLogVerbosity::Verbose, fileName, functionName, lineNumber, gBuffer);
			va_end(vl);
		}

		export void Debug(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const char* message)
		{
			Log(channel, eLogVerbosity::Debug, fileName, functionName, lineNumber, message);
		}

		export void DebugF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const char* message, ...)
		{
			va_list vl;
			va_start(vl, message);
			vsnprintf(gBuffer, MAX_BUFFER, message, vl);
			Log(channel, eLogVerbosity::Debug, fileName, functionName, lineNumber, gBuffer);
			va_end(vl);
		}

		export void Info(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const char* message)
		{
			Log(channel, eLogVerbosity::Info, fileName, functionName, lineNumber, message);
		}

		export void InfoF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const char* message, ...)
		{
			va_list vl;
			va_start(vl, message);
			vsnprintf(gBuffer, MAX_BUFFER, message, vl);
			Log(channel, eLogVerbosity::Info, fileName, functionName, lineNumber, gBuffer);
			va_end(vl);
		}

		export void Warn(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const char* message)
		{
			Log(channel, eLogVerbosity::Warn, fileName, functionName, lineNumber, message);
		}

		export void WarnF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const char* message, ...)
		{
			va_list vl;
			va_start(vl, message);
			vsnprintf(gBuffer, MAX_BUFFER, message, vl);
			Log(channel, eLogVerbosity::Warn, fileName, functionName, lineNumber, gBuffer);
			va_end(vl);
		}

		export void Error(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const char* message)
		{
			Log(channel, eLogVerbosity::Error, fileName, functionName, lineNumber, message);
		}

		export void ErrorF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const char* message, ...)
		{
			va_list vl;
			va_start(vl, message);
			vsnprintf(gBuffer, MAX_BUFFER, message, vl);
			Log(channel, eLogVerbosity::Error, fileName, functionName, lineNumber, gBuffer);
			va_end(vl);
		}

		export void Assert(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const char* message)
		{
			Log(channel, eLogVerbosity::Assert, fileName, functionName, lineNumber, message);
		}

		export void AssertF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const char* message, ...)
		{
			va_list vl;
			va_start(vl, message);
			vsnprintf(gBuffer, MAX_BUFFER, message, vl);
			Log(channel, eLogVerbosity::Assert, fileName, functionName, lineNumber, gBuffer);
			va_end(vl);
		}

		// wide

		export void WVerbose(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const wchar_t* message)
		{
			WLog(channel, eLogVerbosity::Verbose, fileName, functionName, lineNumber, message);
		}

		export void WVerboseF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const wchar_t* message, ...)
		{
			va_list vl;
			va_start(vl, message);
			vswprintf(gWBuffer, MAX_BUFFER, message, vl);
			WLog(channel, eLogVerbosity::Verbose, fileName, functionName, lineNumber, gWBuffer);
			va_end(vl);
		}

		export void WDebug(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const wchar_t* message)
		{
			WLog(channel, eLogVerbosity::Debug, fileName, functionName, lineNumber, message);
		}

		export void WDebugF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const wchar_t* message, ...)
		{
			va_list vl;
			va_start(vl, message);
			vswprintf(gWBuffer, MAX_BUFFER, message, vl);
			WLog(channel, eLogVerbosity::Debug, fileName, functionName, lineNumber, gWBuffer);
			va_end(vl);
		}

		export void WInfo(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const wchar_t* message)
		{
			WLog(channel, eLogVerbosity::Info, fileName, functionName, lineNumber, message);
		}

		export void WInfoF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const wchar_t* message, ...)
		{
			va_list vl;
			va_start(vl, message);
			vswprintf(gWBuffer, MAX_BUFFER, message, vl);
			WLog(channel, eLogVerbosity::Info, fileName, functionName, lineNumber, gWBuffer);
			va_end(vl);
		}

		export void WWarn(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const wchar_t* message)
		{
			WLog(channel, eLogVerbosity::Warn, fileName, functionName, lineNumber, message);
		}

		export void WWarnF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const wchar_t* message, ...)
		{
			va_list vl;
			va_start(vl, message);
			vswprintf(gWBuffer, MAX_BUFFER, message, vl);
			WLog(channel, eLogVerbosity::Warn, fileName, functionName, lineNumber, gWBuffer);
			va_end(vl);
		}

		export void WError(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const wchar_t* message)
		{
			WLog(channel, eLogVerbosity::Error, fileName, functionName, lineNumber, message);
		}

		export void WErrorF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const wchar_t* message, ...)
		{
			va_list vl;
			va_start(vl, message);
			vswprintf(gWBuffer, MAX_BUFFER, message, vl);
			WLog(channel, eLogVerbosity::Error, fileName, functionName, lineNumber, gWBuffer);
			va_end(vl);
		}

		export void WAssert(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const wchar_t* message)
		{
			WLog(channel, eLogVerbosity::Assert, fileName, functionName, lineNumber, message);
		}

		export void WAssertF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, const wchar_t* message, ...)
		{
			va_list vl;
			va_start(vl, message);
			vswprintf(gWBuffer, MAX_BUFFER, message, vl);
			WLog(channel, eLogVerbosity::Assert, fileName, functionName, lineNumber, gWBuffer);
			va_end(vl);
		}

		void Log(eLogChannel channel, eLogVerbosity verbosity, const char* fileName, const char* functionName, int32_t lineNumber, const char* message)
		{
			std::lock_guard<std::mutex> lock(gQueueMutex);
			if (gCurrentVerbosity == eLogVerbosity::All || verbosity == gCurrentVerbosity)
			{
				std::string buffer;

				switch (channel)
				{
				case eLogChannel::GRAPHICS:
					buffer = "Graphics/";
					break;
				case eLogChannel::PHYSICS:
					buffer = "Physics/";
					break;
				case eLogChannel::AUDIO:
					buffer = "Audio/";
					break;
				case eLogChannel::AI:
					buffer = "AI/";
					break;
				case eLogChannel::GAMEPLAY:
					buffer = "Gameplay/";
					break;
				case eLogChannel::CORE:
					buffer = "Core/";
					break;
				case eLogChannel::CORE_MODULE:
					buffer = "Core/Module/";
					break;
				case eLogChannel::CORE_UNIT_TEST:
					buffer = "Core/UnitTest/";
					break;
				case eLogChannel::CORE_MEMORY:
					buffer = "Core/Memory/";
					break;
				case eLogChannel::CORE_MATH:
					buffer = "Core/Math/";
					break;
				case eLogChannel::CORE_STRING:
					buffer = "Core/String/";
					break;
				case eLogChannel::CORE_LOCALIZATION:
					buffer = "Core/Localization/";
					break;
				case eLogChannel::CORE_PARSER:
					buffer = "Core/Parser/";
					break;
				case eLogChannel::CORE_PROFILE:
					buffer = "Core/Profile/";
					break;
				case eLogChannel::CORE_ENGINE_CONFIG:
					buffer = "Core/EngineConfig/";
					break;
				case eLogChannel::CORE_RNG:
					buffer = "Core/RandomNumberGenerator/";
					break;
				case eLogChannel::CORE_OBJECT:
					buffer = "Core/Object/";
					break;
				case eLogChannel::CORE_THREAD:
					buffer = "Core/Thread/";
					break;
				case eLogChannel::CORE_CONTAINER:
					buffer = "Core/Containers/";
					break;
				case eLogChannel::CORE_FILE_SYSTEM:
					buffer = "Core/FileSystem/";
					break;
				case eLogChannel::CORE_TIMER:
					buffer = "Core/Timer/";
					break;
				case eLogChannel::CORE_RESOURCE_MANAGER:
					buffer = "Core/ResourceManager/";
					break;
				default:
					assert(false);
					break;
				}

				gOs.flush();
				gOs.clear();

				gOs << fileName << '/' << functionName << "line:" << lineNumber << " :\t" << message << std::endl;
				buffer.append(gOs.str());
				gStringQueue.push(buffer);
			}
		}

		void WLog(eLogChannel channel, eLogVerbosity verbosity, const char* fileName, const char* functionName, int32_t lineNumber, const wchar_t* message)
		{
			std::lock_guard<std::mutex> lock(gQueueMutex);
			if (gCurrentVerbosity == eLogVerbosity::All || verbosity == gCurrentVerbosity)
			{
				std::wstring buffer;

				switch (channel)
				{
				case eLogChannel::GRAPHICS:
					buffer = L"Graphics/";
					break;
				case eLogChannel::PHYSICS:
					buffer = L"Physics/";
					break;
				case eLogChannel::AUDIO:
					buffer = L"Audio/";
					break;
				case eLogChannel::AI:
					buffer = L"AI/";
					break;
				case eLogChannel::GAMEPLAY:
					buffer = L"Gameplay/";
					break;
				case eLogChannel::CORE:
					buffer = L"Core/";
					break;
				case eLogChannel::CORE_MODULE:
					buffer = L"Core/Module/";
					break;
				case eLogChannel::CORE_UNIT_TEST:
					buffer = L"Core/UnitTest/";
					break;
				case eLogChannel::CORE_MEMORY:
					buffer = L"Core/Memory/";
					break;
				case eLogChannel::CORE_MATH:
					buffer = L"Core/Math/";
					break;
				case eLogChannel::CORE_STRING:
					buffer = L"Core/String/";
					break;
				case eLogChannel::CORE_LOCALIZATION:
					buffer = L"Core/Localization/";
					break;
				case eLogChannel::CORE_PARSER:
					buffer = L"Core/Parser/";
					break;
				case eLogChannel::CORE_PROFILE:
					buffer = L"Core/Profile/";
					break;
				case eLogChannel::CORE_ENGINE_CONFIG:
					buffer = L"Core/EngineConfig/";
					break;
				case eLogChannel::CORE_RNG:
					buffer = L"Core/RandomNumberGenerator/";
					break;
				case eLogChannel::CORE_OBJECT:
					buffer = L"Core/Object/";
					break;
				case eLogChannel::CORE_THREAD:
					buffer = L"Core/Thread/";
					break;
				case eLogChannel::CORE_CONTAINER:
					buffer = L"Core/Containers/";
					break;
				case eLogChannel::CORE_FILE_SYSTEM:
					buffer = L"Core/FileSystem/";
					break;
				case eLogChannel::CORE_TIMER:
					buffer = L"Core/Timer/";
					break;
				case eLogChannel::CORE_RESOURCE_MANAGER:
					buffer = L"Core/ResourceManager/";
					break;
				default:
					assert(false);
					break;
				}

				gWOs.flush();
				gWOs.clear();

				gWOs << fileName << L'/' << functionName << L"line:" << lineNumber << L" :\t" << message << std::endl;
				buffer.append(gWOs.str());
				gWStringQueue.push(buffer);
			}
		}
#else
		void Log(eLogChannel channel, eLogVerbosity verbosity, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message);

		void Verbose(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message)
		{
			Log(channel, eLogVerbosity::Verbose, fileName, functionName, lineNumber, os, message);
		}

		void VerboseF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message, ...)
		{
			va_list vl;
			va_start(vl, message);
			vsnprintf(gBuffer, MAX_BUFFER, message, vl);
			Log(channel, eLogVerbosity::Verbose, fileName, functionName, lineNumber, os, gBuffer);
			va_end(vl);
		}

		void Debug(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message)
		{
			Log(channel, eLogVerbosity::Debug, fileName, functionName, lineNumber, os, message);
		}

		void DebugF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message, ...)
		{
			va_list vl;
			va_start(vl, message);
			vsnprintf(gBuffer, MAX_BUFFER, message, vl);
			Log(channel, eLogVerbosity::Debug, fileName, functionName, lineNumber, os, gBuffer);
			va_end(vl);
		}

		void Info(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message)
		{
			Log(channel, eLogVerbosity::Info, fileName, functionName, lineNumber, os, message);
		}

		void InfoF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message, ...)
		{
			va_list vl;
			va_start(vl, message);
			vsnprintf(gBuffer, MAX_BUFFER, message, vl);
			Log(channel, eLogVerbosity::Info, fileName, functionName, lineNumber, os, gBuffer);
			va_end(vl);
		}

		void Warn(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message)
		{
			Log(channel, eLogVerbosity::Warn, fileName, functionName, lineNumber, os, message);
		}

		void WarnF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message, ...)
		{
			va_list vl;
			va_start(vl, message);
			vsnprintf(gBuffer, MAX_BUFFER, message, vl);
			Log(channel, eLogVerbosity::Warn, fileName, functionName, lineNumber, os, gBuffer);
			va_end(vl);
		}

		void Error(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message)
		{
			Log(channel, eLogVerbosity::Error, fileName, functionName, lineNumber, os, message);
		}

		void ErrorF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message, ...)
		{
			va_list vl;
			va_start(vl, message);
			vsnprintf(gBuffer, MAX_BUFFER, message, vl);
			Log(channel, eLogVerbosity::Error, fileName, functionName, lineNumber, os, gBuffer);
			va_end(vl);
		}

		void Assert(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message)
		{
			Log(channel, eLogVerbosity::Assert, fileName, functionName, lineNumber, os, message);
		}

		void AssertF(eLogChannel channel, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message, ...)
		{
			va_list vl;
			va_start(vl, message);
			vsnprintf(gBuffer, MAX_BUFFER, message, vl);
			Log(channel, eLogVerbosity::Assert, fileName, functionName, lineNumber, os, gBuffer);
			va_end(vl);
		}
		void Log(eLogChannel channel, eLogVerbosity verbosity, const char* fileName, const char* functionName, int32_t lineNumber, std::ostream& os, const char* message)
		{
			if (gCurrentVerbosity == eLogVerbosity::All || verbosity == gCurrentVerbosity)
			{
				String buffer;

				switch (channel)
				{
				case eLogChannel::GRAPHICS:
					buffer = "Graphics/";
					break;
				case eLogChannel::PHYSICS:
					buffer = "Physics/";
					break;
				case eLogChannel::AUDIO:
					buffer = "Audio/";
					break;
				case eLogChannel::AI:
					buffer = "AI/";
					break;
				case eLogChannel::GAMEPLAY:
					buffer = "Gameplay/";
					break;
				case eLogChannel::CORE:
					buffer = "Core/";
					break;
				case eLogChannel::CORE_UNIT_TEST:
					buffer = "Core/UnitTest/";
					break;
				case eLogChannel::CORE_MEMORY:
					buffer = "Core/Memory/";
					break;
				case eLogChannel::CORE_MATH:
					buffer = "Core/Math/";
					break;
				case eLogChannel::CORE_STRING:
					buffer = "Core/String/";
					break;
				case eLogChannel::CORE_LOCALIZATION:
					buffer = "Core/Localization/";
					break;
				case eLogChannel::CORE_PARSER:
					buffer = "Core/Parser/";
					break;
				case eLogChannel::CORE_PROFILE:
					buffer = "Core/Profile/";
					break;
				case eLogChannel::CORE_ENGINE_CONFIG:
					buffer = "Core/EngineConfig/";
					break;
				case eLogChannel::CORE_RNG:
					buffer = "Core/RandomNumberGenerator/";
					break;
				case eLogChannel::CORE_OBJECT:
					buffer = "Core/Object/";
					break;
				case eLogChannel::CORE_THREAD:
					buffer = "Core/Thread/";
					break;
				case eLogChannel::CORE_CONTAINER:
					buffer = "Core/Container/";
					break;
				case eLogChannel::CORE_FILE_SYSTEM:
					buffer = "Core/FileSystem/";
					break;
				case eLogChannel::CORE_TIMER:
					buffer = "Core/Timer/";
					break;
				case eLogChannel::CORE_RESOURCE_MANAGER:
					buffer = "Core/ResourceManager/";
					break;
				default:
					assert(false);
					break;
				}

				char color = '7';
				switch (verbosity)
				{
				case eLogVerbosity::Verbose:
					buffer += "V/";
					break;
				case eLogVerbosity::Debug:
					buffer += "D/";
					color = '2';
					break;
				case eLogVerbosity::Info:
					buffer += "I/";
					color = '3';
					break;
				case eLogVerbosity::Warn:
					buffer += "W/";
					color = '5';
					break;
				case eLogVerbosity::Error:
					buffer += "E/";
					color = '1';
					break;
				case eLogVerbosity::Assert:
					buffer += "A/";
					color = '6';
					break;
				default:
					assert(false);
					break;
				}

				os << "\033[1;3" << color << 'm' << buffer << fileName << "/" << functionName << "/line:" << lineNumber << " :\t" << message << "\033[0m" << std::endl;
			}
		}
#endif
	}
} // namespace cave