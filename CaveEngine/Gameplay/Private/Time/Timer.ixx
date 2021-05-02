/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include <cassert>

export module Timer;

import FlatformTimer;

namespace cave
{
	export class Timer
	{
	public:
		using TimePoint = FlatformTimer::TimePoint;
		using Second = float;

		explicit Timer() noexcept
		{
			mCreationTimePoint = FlatformTimer::GetTimePoint();
			mTimePoint = mCreationTimePoint;
			mLifeSpan = 0;
		}

		Second GetDeltaTime() noexcept
		{
			auto newTimePoint = FlatformTimer::GetTimePoint();
			auto deltaTime = FlatformTimer::GetTimeDiffer(mTimePoint, newTimePoint);
			SetTimePoint(newTimePoint);

			return deltaTime;
		}

		TimePoint GetCreationTimePoint() const noexcept
		{
			return mCreationTimePoint;
		}

		Second GetTimeSinceCreation() const noexcept
		{
			return FlatformTimer::GetTimeDiffer(mCreationTimePoint, FlatformTimer::GetTimePoint());
		}

		void SetTimePoint(TimePoint newTimePoint) noexcept
		{
			assert(newTimePoint > mTimePoint);
			mTimePoint = newTimePoint;
		}

		TimePoint GetTimePoint() const noexcept
		{
			return mTimePoint;
		}

		void SetLifeSpan(Second newLifeSpan) noexcept
		{
			assert(newLifeSpan > 0.f && mLifeSpan == 0);
			mLifeSpan = newLifeSpan;
		}

		Second GetLifeSpan() const noexcept
		{
			return mLifeSpan;
		}

		bool IsLifeExpired() const noexcept
		{
			return mLifeSpan < GetTimeSinceCreation() && mLifeSpan != 0.f ? true : false;
		}

	private:
		TimePoint mCreationTimePoint;

		TimePoint mTimePoint;

		Second mLifeSpan;
	};
}