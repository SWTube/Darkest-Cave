module;

#include <Windows.h>

#include "Assertion/Assert.h"

export module EngineTimer;

namespace cave
{
	export class EngineTimer final
	{
	public:
		friend class Engine;

		EngineTimer(const EngineTimer&) = delete;
		EngineTimer(EngineTimer&&) = delete;

		~EngineTimer();
		EngineTimer& operator=(const EngineTimer&) = delete;
		EngineTimer& operator=(EngineTimer&&) = delete;

		void Init();
		void Update();
		float GetElapsedTimestepFromLastUpdate();
		float GetInterpolationTimestep();

	private:
		EngineTimer();

	private:
		LARGE_INTEGER mTimer;
		LARGE_INTEGER mTimestep;

		uint64_t mLastUpdateTime;
		uint64_t mCurrentUpdateTime;
	};

	EngineTimer::EngineTimer()
		: mLastUpdateTime(0.f)
		, mCurrentUpdateTime(0.f)
	{
		QueryPerformanceFrequency(&mTimer);
	}

	EngineTimer::~EngineTimer()
	{
		
	}

	void EngineTimer::Init()
	{
		QueryPerformanceCounter(&mTimestep);
		mCurrentUpdateTime = mTimestep.QuadPart;
	}

	void EngineTimer::Update()
	{
		QueryPerformanceCounter(&mTimestep);
		mLastUpdateTime = mCurrentUpdateTime;
		mCurrentUpdateTime = mTimestep.QuadPart;
	}

	float EngineTimer::GetElapsedTimestepFromLastUpdate()
	{
		return (mCurrentUpdateTime - mLastUpdateTime) / static_cast<float>(mTimer.QuadPart);
	}

	float EngineTimer::GetInterpolationTimestep()
	{
		QueryPerformanceCounter(&mTimestep);
		
		return (mTimestep.QuadPart - mCurrentUpdateTime) / static_cast<float>(mTimer.QuadPart);
	}
}