/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Thread.h"

namespace cave 
{
	Thread::Thread(int32_t threadCount) :
		mThreadCount(threadCount), mStopAllThread(false)
	{
		mWorkerVector.reserve(mThreadCount);

		for (int32_t i = 0; i < mThreadCount; ++i)
		{
			mWorkerVector.emplace_back([this]()
				{
					this->ThreadWorker();
				}
			);
		}

	}

	void Thread::ThreadWorker()
	{
		while (true)
		{
			std::unique_lock<std::mutex> lock(mJobQM);
			// wait conditional variable
			mJobQCv.wait(lock, [this]()
				{
					return !this->mJobQueue.empty() || mStopAllThread;
				}
			);
			// stop worker condition
			if (mStopAllThread && this->mJobQueue.empty())
			{
				return;
			}

			// get jobQueue's front job & pop 
			std::function<void()> job = std::move(mJobQueue.front());
			mJobQueue.pop();
			lock.unlock();

			// Execute the job
			job();
		}
	}

	Thread::~Thread()
	{
		mStopAllThread = true;

		// notify_all() is like notify_one()
		// wake all waiting thread in condition variable
		mJobQCv.notify_all();

		for (auto& thread : mWorkerVector)
		{
			thread.join();
		}
	}

	template<class Function, class... Arguments>
	std::future<typename std::result_of<Function(Arguments...)>::type>
		Thread::enqueue(Function&& function, Arguments&& ... arguments)
	{
		if (mStopAllThread)
		{
			throw std::runtime_error("Error");
		}

		using returnType = typename std::result_of<Function(Arguments...)>::type;

		auto job = std::make_shared<std::packaged_task<returnType()>>(
			std::bind(std::forward<Function>(function),
				std::forward<Arguments>(arguments)...));

		std::future<returnType> jobFutureResult = job->get_future();
		{
			std::lock_guard<std::mutex> lock(mJobQM);
			mJobQueue.push([job]() {(*job)(); });
		}
		mJobQCv.notify_all();

		return jobFutureResult;
	}
}