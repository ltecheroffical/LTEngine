#include <LTCore/thread_pool.hpp>


using namespace LTCore;


ThreadPool::ThreadPool(size_t threads) {
    for (size_t i = 0; i < threads; i++) {
        m_workers.emplace_back([this] {
            while (true) {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(m_queueMutex);
                    m_condition.wait(lock, [this] { return !m_tasks.empty() || m_isShuttingDown; });
                    if (m_isShuttingDown && m_tasks.empty()) {
                        return;
                    }
                    task = std::move(m_tasks.front());
                    m_tasks.pop();
                }

                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(m_queueMutex);
        m_isShuttingDown = true;
    }
    m_condition.notify_all();
    for (std::thread& worker : m_workers) {
        worker.join();
    }
}


void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(m_queueMutex);
        m_tasks.push(task);
    }
    m_condition.notify_one();
}
