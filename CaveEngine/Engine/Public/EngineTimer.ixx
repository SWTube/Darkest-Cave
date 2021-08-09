module;

#include "tictoc.h"
#include "Assertion/Assert.h"

export module EngineTimer;

namespace cave
{
	export class EngineTimer final
	{
	public:
		EngineTimer();
		EngineTimer(const EngineTimer&) = delete;
		EngineTimer(EngineTimer&&) = delete;

		~EngineTimer();
		EngineTimer& operator=(const EngineTimer&) = delete;
		EngineTimer& operator=(EngineTimer&&) = delete;

		void Init();
		double GetElapsedFromLastUpdate();

	private:
		TicTocTimer mTimer;
	};

	EngineTimer::EngineTimer()
		: mTimer(tic())
	{

	}

	EngineTimer::~EngineTimer()
	{
		
	}

	void EngineTimer::Init()
	{
		toc(&mTimer);
	}

	double EngineTimer::GetElapsedFromLastUpdate()
	{
		return toc(&mTimer);
	}
}