/**
 * @project Devkits
 * @file ThreadPool.h
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/10/27 22:57:18
 */

#ifndef DEVKITS_THREADPOOL_H
#define DEVKITS_THREADPOOL_H

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <memory>

namespace dev {
    class ThreadPool {
    public:
        typedef std::shared_ptr<ThreadPool> Ptr;

        explicit ThreadPool(size_t pool_size) : m_work(m_ioService) {
            // Allow up to pool_size parallel tasks
            for (size_t i = 0; i < pool_size; ++i) {
                m_workers.create_thread([this] {
                    m_ioService.run();
                });
            }
        }
        void stop() {
            m_ioService.stop();
            if (!m_workers.is_this_thread_in()) {
                m_workers.join_all();
            }
        }

        ~ThreadPool() { stop(); }

        // Add new work item to the pool.
        template <class F>
        void enqueue(F f) {
            m_ioService.post(f);
        }

    private:
        boost::thread_group m_workers;
        boost::asio::io_service m_ioService;
        // m_work ensures that io_service's run() function will not exit while work is underway
        boost::asio::io_service::work m_work;
    };

}  // namespace dev

#endif //DEVKITS_THREADPOOL_H
