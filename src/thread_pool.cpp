#include <LTEngine/thread_pool.hpp>


using namespace LTEngine;


ThreadPool::ThreadPool(size_t threads) {
    for (size_t i = 0; i < threads; i++) {
        _workers.emplace_back([this] {
            while (true) {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(_queue_mutex);
                    _condition.wait(lock, [this] { return !_tasks.empty() || _is_shutting_down; });
                    if (_is_shutting_down && _tasks.empty()) {
                        return;
                    }
                    task = std::move(_tasks.front());
                    _tasks.pop();
                }

                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(_queue_mutex);
        _is_shutting_down = true;
    }
    _condition.notify_all();
    for (std::thread& worker : _workers) {
        worker.join();
    }
}


void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(_queue_mutex);
        _tasks.push(task);
    }
    _condition.notify_one();
}
