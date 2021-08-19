/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "Assertion/Assert.h"
#include "Debug/Log.h"

export module Scheduler;

import Array;

namespace cave
{
	class Schedule
	{
	public:
		Schedule() = delete;
		constexpr Schedule(double startTime, double endTime);
		constexpr Schedule(const Schedule& other) = default;
		constexpr Schedule(Schedule&& other) = default;
		virtual ~Schedule() = default;

		constexpr Schedule& operator=(const Schedule& other) = default;
		constexpr Schedule& operator=(Schedule&& other) = default;

		constexpr double GetStartTime() const;
		constexpr void SetStartTime(double startTime);
		constexpr double GetEndTime() const;
		constexpr void SetEndTime(double endTime);
		constexpr double GetInterval() const;
	protected:
		double mStartTime;
		double mEndTime;
	};

	class Scheduler
	{
	public:
		static Array<Schedule> GetSchedule(const Array<Schedule>& schedules);
	protected:
		static constexpr void quicksortSchedulesByEndTime(Array<Schedule>& schedules);
		static constexpr void quicksortSchedulesByEndTimeRecursive(Array<Schedule>& schedules, size_t leftIndex, size_t rightIndex);
		static constexpr size_t partitionSchedulesByEndTimeRecursive(Array<Schedule>& schedules, size_t leftIndex, size_t rightIndex);
	};

	constexpr Schedule::Schedule(double startTime, double endTime)
		: mStartTime(startTime)
		, mEndTime(endTime)
	{
		assert(startTime < endTime);
	}

	constexpr double Schedule::GetStartTime() const
	{
		return mStartTime;
	}

	constexpr void Schedule::SetStartTime(double startTime)
	{
		assert(startTime < mEndTime);

		mStartTime = startTime;
	}

	constexpr double Schedule::GetEndTime() const
	{
		return mEndTime;
	}

	constexpr void Schedule::SetEndTime(double endTime)
	{
		assert(mStartTime < endTime);

		mEndTime = endTime;
	}

	constexpr double Schedule::GetInterval() const
	{
		return mEndTime - mStartTime;
	}

	Array<Schedule> Scheduler::GetSchedule(const Array<Schedule>& schedules)
	{
		Array<Schedule> sortedSchedules = schedules;
		quicksortSchedulesByEndTime(sortedSchedules);
		Array<Schedule> result;
		result.SetCapacity(schedules.GetSize());

		if (schedules.GetSize() > 0)
		{
			result.InsertBack(sortedSchedules[0]);

			for (size_t i = 1; i < sortedSchedules.GetSize(); ++i)
			{
				if (sortedSchedules[i].GetStartTime() < result.GetBack().GetEndTime())
				{
					continue;
				}

				result.InsertBack(sortedSchedules[i]);
			}
		}

		return result;
	}

	constexpr void Scheduler::quicksortSchedulesByEndTime(Array<Schedule>& schedules)
	{
		quicksortSchedulesByEndTimeRecursive(schedules, 0, schedules.GetSize() - 1);
	}

	constexpr void Scheduler::quicksortSchedulesByEndTimeRecursive(Array<Schedule>& schedules, size_t leftIndex, size_t rightIndex)
	{
		if (leftIndex >= rightIndex) {
			return;
		}
		
		size_t pivotIndex = partitionSchedulesByEndTimeRecursive(schedules, leftIndex, rightIndex);
		
		quicksortSchedulesByEndTimeRecursive(schedules, leftIndex, pivotIndex);
		quicksortSchedulesByEndTimeRecursive(schedules, pivotIndex + 1, rightIndex);
	}

	constexpr size_t Scheduler::partitionSchedulesByEndTimeRecursive(Array<Schedule>& schedules, size_t leftIndex, size_t rightIndex)
	{
		size_t i = leftIndex - 1;
		size_t j = rightIndex + 1;
		
		while (true) {
			do {
				++i;
			} while (schedules[i].GetEndTime() < schedules[leftIndex].GetEndTime());
			
			do {
				--j;
			} while (schedules[j].GetEndTime() > schedules[leftIndex].GetEndTime());

			if (i >= j) {
				return j;
			}

			Schedule temp = schedules[i];
			schedules[i] = schedules[j];
			schedules[j] = temp;
		}
	}

#ifdef CAVE_BUILD_DEBUG
	namespace SchedulerTest
	{
		export void Main();

		void Main()
		{
			{
				Array<Schedule> schedules;
				schedules.SetCapacity(4);

				Schedule schedule0(2.0, 4.0);
				Schedule schedule1(0.0, 3.0);
				Schedule schedule2(6.0, 8.0);
				Schedule schedule3(3.0, 6.0);

				schedules.InsertBack(schedule0);
				schedules.InsertBack(schedule1);
				schedules.InsertBack(schedule2);
				schedules.InsertBack(schedule3);

				Array<Schedule> result = Scheduler::GetSchedule(schedules);

				for (const Schedule& schedule : result)
				{
					LOGDF(cave::eLogChannel::CORE, "schedule(%lf, %lf)", schedule.GetStartTime(), schedule.GetEndTime());
				}
			}
		}
	}
#endif
}