/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <basetsd.h>

import FlatformTimer;

export module Timer;

namespace cave
{
	export class Timer
	{
	public:
		using TimePoint = FlatformTimer::TimePoint;

		Timer()
		{
			mCreationTimePoint = FlatformTimer::GetTimePoint();
			mTimePoint = mCreationTimePoint;
		}

		float GetDeltaTime()
		{
			auto newTimePoint = FlatformTimer::GetTimePoint();
			auto deltaTime = FlatformTimer::GetTimeDiffer(mTimePoint, newTimePoint);
			mTimePoint = newTimePoint;

			return deltaTime;
		}

		float GetCreationTime() const
		{
			return FlatformTimer::GetTimeDiffer(FlatformTimer::GetCreationTimePoint(), mCreationTimePoint);
		}

		FlatformTimer::TimePoint GetTimePoint() const
		{
			return mTimePoint;
		}

		float GetLifeSpan()
		{
			return FlatformTimer::GetTimeDiffer(mCreationTimePoint);
		}

	private:
		FlatformTimer::TimePoint mCreationTimePoint;

		FlatformTimer::TimePoint mTimePoint;
	};
}