/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include <atomic>
#include <mutex>
#include <thread>
#include <future>
#include <vector>
#include <functional>
#include <condition_variable>
#include <queue>

namespace cave
{
	class Thread
	{
	public:
		//	Create empty thread object
		//Thread();

		//	Create thread object, count worker thread
		Thread(int32_t threadCount);

		//	Destructor
		~Thread();

		//	Enqueue job
		template<class Function, class... Arguments>
		std::future<class std::invoke_result<Function(Arguments...)>::type>
			enqueue(Function&& function, Arguments&& ... arguments);

		//	Non-copyable
		Thread(const Thread&) = delete;
		Thread& operator=(const Thread&) = delete;

	private:
		//	Worker thread count
		int32_t mThreadCount;

		//	Vector, contain worker thread
		std::vector<std::thread> mWorkerVector;

		//	Queue, contain to do
		std::queue<std::function<void()>> mJobQueue;

		//	jobQueue's conditional variable
		std::condition_variable mJobQCv;

		//	jobQueue's conditional variable
		std::mutex mJobQM;

		//	Stop all thread
		bool mStopAllThread;

		//	Thread worker
		void ThreadWorker();
	};
}

//cave::Thread::Thread() : mThreadCount(0), mStopAllThread(false)
//{
//
//}