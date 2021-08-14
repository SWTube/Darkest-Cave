module;

#include <Windows.h>

#include "Assertion/Assert.h"

export module Timer;

namespace cave
{
	export class Timer final
	{
	public:
		friend class Engine;

		Timer(const Timer&) = delete;
		Timer(Timer&&) = delete;

		~Timer();
		Timer& operator=(const Timer&) = delete;
		Timer& operator=(Timer&&) = delete;

		void Init();
		void Update();
		float GetElapsedTimestepFromLastUpdate();
		float GetInterpolationTimestep();

	private:
		Timer();

	private:
		LARGE_INTEGER mTimer;
		LARGE_INTEGER mTimestep;

		uint64_t mLastUpdateTime;
		uint64_t mCurrentUpdateTime;
	};

	Timer::Timer()
		: mLastUpdateTime(0.f)
		, mCurrentUpdateTime(0.f)
	{
		QueryPerformanceFrequency(&mTimer);
	}

	Timer::~Timer()
	{
		
	}

	void Timer::Init()
	{
		QueryPerformanceCounter(&mTimestep);
		mCurrentUpdateTime = mTimestep.QuadPart;
	}

	void Timer::Update()
	{
		QueryPerformanceCounter(&mTimestep);
		mLastUpdateTime = mCurrentUpdateTime;
		mCurrentUpdateTime = mTimestep.QuadPart;
	}

	float Timer::GetElapsedTimestepFromLastUpdate()
	{
		return (mCurrentUpdateTime - mLastUpdateTime) / static_cast<float>(mTimer.QuadPart);
	}

	float Timer::GetInterpolationTimestep()
	{
		QueryPerformanceCounter(&mTimestep);
		
		return (mTimestep.QuadPart - mCurrentUpdateTime) / static_cast<float>(mTimer.QuadPart);
	}
}