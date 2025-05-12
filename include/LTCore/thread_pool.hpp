#ifndef _LTCORE_THREAD_POOL_HPP_
#define _LTCORE_THREAD_POOL_HPP_

#include <atomic>
#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>

#include <LTCore/common/compiler_utils.h>


namespace LTCore {
	class LTCORE_API ThreadPool {
	public:
		ThreadPool(size_t threads);
		~ThreadPool();

		void enqueue(std::function<void()> task);

	private:
		std::vector<std::thread> m_workers;
		std::queue<std::function<void()>> m_tasks;

		std::mutex m_queueMutex;
		std::condition_variable m_condition;
		std::atomic<bool> m_isShuttingDown;
	};
} // namespace LTCore

#endif
