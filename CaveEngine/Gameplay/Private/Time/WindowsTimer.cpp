/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

module WindowsTimer;

#ifdef _WIN32
namespace cave
{
	WindowsTimer::WindowsTimer()
	{
		LARGE_INTEGER primaryTimer;
		QueryPerformanceFrequency(&primaryTimer);
		frequency = 1.f / primaryTimer.QuadPart;
		frequency64 = 1.0 / primaryTimer.QuadPart;
	}

	WindowsTimer::~WindowsTimer()
	{

	}

	TimePoint WindowsTimer::GetTimePoint()
	{
		LARGE_INTEGER timePoint;
		QueryPerformanceCounter(&timePoint);
		return timePoint.QuadPart;
	}

	float WindowsTimer::GetTimeDiffer(TimePoint begin, TimePoint end)
	{
		return end > begin ? (end - begin) * frequency : 0.f;
	}

	float WindowsTimer::GetStartTime() const
	{
		return mStartTime;
	}

	double WindowsTimer::GetTimeDiffer64(TimePoint begin, TimePoint end)
	{
		return end > begin ? (end - begin) * frequency64 : 0.0;
	}

	double WindowsTimer::GetStartTime64() const
	{
		return (double)mStartTime;
	}
}
#endif // _WIN32
