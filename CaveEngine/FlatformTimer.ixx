/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <chrono>
#include <Windows.h>

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
		using Milliseconds = std::chrono::milliseconds;

#endif //_WIN32

		export TimePoint GetTimePoint()
		{
#ifdef _WIN32
			return GetTickCount64();

#else
			return SteadyClock::now();
#endif // _WIN32

		}

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
			auto differ = (endTimePoint - beginTimePoint);

#else
			auto differ = std::chrono::duration_cast<Milliseconds>(endTimePoint - beginTimePoint).count();
#endif // _WIN32

			return  differ * 0.001f;
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