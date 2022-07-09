/**
 * @file ThreadPool.h
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>
#include "noncopyable.h"

namespace ChanNet
{

class ThreadPool: noncopyable {

public:
    
    //构造函数
    ThreadPool (size_t);

    //添加任务API
    /*
    C++ 14 
    template< class Func, class ... Args>
    auto addTask(Func&& func, Args&&... args) {return func(args...);}
    */
    template< class Func, class ... Args>
    auto addTask(Func&& func, Args&&... args) -> std::future< typename std::result_of< Func(Args...) >::type >;

    //析构函数
    ~ThreadPool ();

private:
    //线程队列
    std::vector< std::thread > threads_;
    //任务队列
    std::queue< std::function <void()> > tasks_;
    //互斥量 条件变量 线程池运行flag
    std::mutex queue_mutex_;
    std::condition_variable cv_;
    std::atomic<bool> stop_;
};

inline ThreadPool::ThreadPool(size_t threads_num): stop_(false) {
    for (size_t i =0; i < threads_num; ++i) 
        threads_.emplace_back(

            //放进去一个 闭包
            [this] {
                for(;;) {
                    std::function<void()> task;
                    //锁&原子操作空间
                    {
                        std::unique_lock< std::mutex> lock(this->queue_mutex_);
                        this->cv_.wait(lock, [this] {return this->stop_ || !this->tasks_.empty();});
                        if (this->stop_ && this->tasks_.empty()) return;
                        task = std::move(this->tasks_.front());
                        this->tasks_.pop();

                    }
                    task();
        
                }
            }
        );
}

template <class Func, class... Args>
auto ThreadPool::addTask(Func&& func, Args&&... args)
    -> std::future <typename std::result_of <Func(Args...)>::type> {
        using return_type = typename std::result_of<Func(Args...)>::type;
        auto task = std::make_shared < std::packaged_task<return_type()> >(
            std::bind(std::forward<Func>(func), std::forward<Args>(args)... )
            );

        std::future <return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock (queue_mutex_);
            if (stop_) 
                throw std::runtime_error ("enqueue on stopped ThreadPool");
            tasks_.emplace([task](){ (*task)(); });
        }
        cv_.notify_one();
        return res;     
}

inline ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        stop_ = true;
    }
    cv_.notify_all();

    for(auto &t: ThreadPool::threads_)
        t.join();
}

}