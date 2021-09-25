module;

#include <Windows.h>

#include "CoreTypes.h"
#include "Assertion/Assert.h"

export module cave.Core.Timer.Timer;

namespace cave
{
	export class Timer
	{
	public:
		Timer();
		Timer(const Timer&) = delete;
		Timer(Timer&&) = delete;

		~Timer();
		Timer& operator=(const Timer&) = delete;
		Timer& operator=(Timer&&) = delete;

		void Init();
		void StartMeasuring();
		void EndMeasuring();

		float GetMeasuredTime() const;
		double GetMeasuredTime64() const;

		float GetTime();
		double GetTime64();

	private:
		LARGE_INTEGER mTimer;
		LARGE_INTEGER mTimestep;

		uint64_t mInitializedTime;
		uint64_t mMeasurementStartTime;
		uint64_t mMeasurementEndTime;

		bool mbMeasuring;
	};

	Timer::Timer()
		: mInitializedTime(0)
		, mMeasurementStartTime(0)
		, mMeasurementEndTime(0)
		, mbMeasuring(false)
	{
		QueryPerformanceFrequency(&mTimer);
	}

	Timer::~Timer()
	{
		
	}

	void Timer::Init()
	{
		QueryPerformanceCounter(&mTimestep);
		mInitializedTime = mTimestep.QuadPart;
	}

	void Timer::StartMeasuring()
	{
		assert(!mbMeasuring);
		mbMeasuring = true;
		QueryPerformanceCounter(&mTimestep);
		mMeasurementStartTime = mTimestep.QuadPart;
	}

	void Timer::EndMeasuring()
	{
		assert(mbMeasuring);
		mbMeasuring = false;
		QueryPerformanceCounter(&mTimestep);
		mMeasurementEndTime = mTimestep.QuadPart;
	}

	float Timer::GetMeasuredTime() const
	{
		assert(!mbMeasuring);
		return (mMeasurementEndTime - mMeasurementStartTime) / static_cast<float>(mTimer.QuadPart);
	}

	double Timer::GetMeasuredTime64() const
	{
		assert(!mbMeasuring);
		return (mMeasurementEndTime - mMeasurementStartTime) / static_cast<double>(mTimer.QuadPart);
	}

	float Timer::GetTime()
	{
		QueryPerformanceCounter(&mTimestep);
		return (mTimestep.QuadPart - mInitializedTime) / static_cast<float>(mTimer.QuadPart);
	}

	double Timer::GetTime64()
	{
		QueryPerformanceCounter(&mTimestep);
		return (mTimestep.QuadPart - mInitializedTime) / static_cast<double>(mTimer.QuadPart);
	}
}