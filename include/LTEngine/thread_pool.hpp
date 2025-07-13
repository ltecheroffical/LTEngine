#ifndef _LTENGINE_THREAD_POOL_HPP_
#define _LTENGINE_THREAD_POOL_HPP_

#include <atomic>
#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>

#include <LTEngine/common/compiler_utils.h>


namespace LTEngine {
	class LTENGINE_API ThreadPool {
	public:
		ThreadPool(size_t threads);
		~ThreadPool();

		void enqueue(std::function<void()> task);

	private:
		std::vector<std::thread> _workers;
		std::queue<std::function<void()>> _tasks;

		std::mutex _queue_mutex;
		std::condition_variable _condition;
		std::atomic<bool> _is_shutting_down;
	};
} // namespace LTEngine

#endif
