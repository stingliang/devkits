/**
 * @project Devkits
 * @file ThreadPool.h
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/10/27 22:57:18
 */

#ifndef DEVKITS_THREADPOOL_H
#define DEVKITS_THREADPOOL_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include <memory>
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

//#define SAMPLE_BOOST_THREAD_POOL

namespace dev {

    class ThreadPool {
    public:
        typedef std::shared_ptr<ThreadPool> Ptr;

        ThreadPool() = delete;

        explicit ThreadPool(size_t pool_size): m_work(m_ioContext) {
            // Allow up to pool_size parallel tasks
            for (size_t i = 0; i < pool_size; ++i) {
                m_workers.create_thread([this] {
                    m_ioContext.run();
                });
            }
        }

        ~ThreadPool() { stop(); }

        void stop() {
            m_ioContext.stop();
            if (!m_workers.is_this_thread_in()) {
                m_workers.join_all();
            }
        }

        // Add new task to the pool.
        template<typename F, typename ... Args>
        auto enqueue(F&& f, Args&&... args)->std::future<typename std::result_of<F(Args...)>::type> {
            using return_type = typename std::result_of<F(Args...)>::type;
            // package function f as a callable object which stores task and shares state
            auto task = std::make_shared<std::packaged_task<return_type()>>(
                    std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );
            std::future<return_type> res = task->get_future();
            // executes task in a thread of io_context
            m_ioContext.post([task]{ (*task)(); });
            return res;
        }

    private:
        boost::thread_group m_workers;
        boost::asio::io_context m_ioContext;
        boost::asio::io_context::work m_work;
    };

}  // namespace dev

#endif //DEVKITS_THREADPOOL_H
