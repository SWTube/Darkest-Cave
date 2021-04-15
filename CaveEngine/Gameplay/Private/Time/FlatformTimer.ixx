/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#ifdef _WIN32
#include <Windows.h>
#else
#include <chrono>
#endif // _WIN32

export module FlatformTimer;

namespace cave
{
	namespace FlatformTimer
	{
#ifdef _WIN32
		export using TimePoint = UINT64;
#else
		export using TimePoint = std::chrono::steady_clock::time_point;

		using SteadyClock = std::chrono::steady_clock;
		using Microseconds = std::chrono::microseconds;

#endif //_WIN32

		export TimePoint GetTimePoint()
		{
#ifdef _WIN32
			LARGE_INTEGER timePoint;
			QueryPerformanceCounter(&timePoint);
			return timePoint.QuadPart;
#else
			return SteadyClock::now();
#endif // _WIN32
		}


#ifdef _WIN32
		float SetFrequency()
		{
			LARGE_INTEGER primaryTimer;
			QueryPerformanceFrequency(&primaryTimer);
			return 1.f / primaryTimer.QuadPart;
		}

		float frequency = SetFrequency();

#endif // _WIN32

		TimePoint creationTimePoint = GetTimePoint();
		TimePoint beginTimePoint = creationTimePoint;
		TimePoint endTimePoint = creationTimePoint;

		bool isSetBeginTimePoint = false;
		bool isSetEndTimePoint = false;

		void ClearTimePoint()
		{
			isSetBeginTimePoint = false;
			isSetEndTimePoint = false;
		}

		export void SetTimePoint()
		{
			if (!isSetBeginTimePoint)
			{
				isSetBeginTimePoint = true;
				beginTimePoint = GetTimePoint();
				return;
			}
			else if (!isSetEndTimePoint)
			{
				isSetEndTimePoint = true;
				endTimePoint = GetTimePoint();
				return;
			}

			ClearTimePoint();
			SetTimePoint();
		}

		export float GetTimeDiffer(TimePoint begin = GetTimePoint(), TimePoint end = GetTimePoint())
		{
			if (!isSetBeginTimePoint)
			{
				beginTimePoint = begin;
			}
			if (!isSetEndTimePoint)
			{
				endTimePoint = end;
			}

			ClearTimePoint();
#ifdef _WIN32
			auto differ = (endTimePoint - beginTimePoint) * frequency;

#else
			auto differ = std::chrono::duration_cast<Microseconds>(endTimePoint - beginTimePoint).count();
#endif // _WIN32

			return  differ;
		}

		export float GetTime()
		{
			return GetTimeDiffer(creationTimePoint);
		}

		export TimePoint GetCreationTimePoint()
		{
			return creationTimePoint;
		}
	}
}