/*
 * =====================================================================================
 * 
 *       Filename:  ThreadPool.h
 * 
 *    Description:  ThreadPool
 * 
 *        Version:  1.0
 *        Created:  2015-07-02 16:29:36
 *       Revision:  none
 *       Compiler:  gcc
 * 
 *         Author:  zhiyuan (search engine group), zhiyuan@taobao.com
 *        Company:  www.taobao.com
 * 
 * =====================================================================================
 */

#ifndef  THREADPOOL_INC
#define  THREADPOOL_INC

#include <pthread.h>
#include <list>
#include <iostream>

//using namespace std;

using std::list;

const int ThreadMaxNum = 100;
typedef void (*FunctionType)(void*);

struct Work
{
    FunctionType function;
    void * arg;
};

// ThreadPool可以改造为使用单例模式
class ThreadPool
{
    class lock;

    public:
        ThreadPool(int num);

        static void* ThreadFunc(void *);
        void AddWork(Work w);
        bool AllFree()
        {
            lock instance;
            return m_taskQueue.empty() && m_freeThreadNum == m_iThreadNum;
        }

        ~ThreadPool();
    private:
        static unsigned int m_iThreadNum;
        pthread_t m_threadID[ThreadMaxNum];

        static int m_freeThreadNum;
        static bool m_shutdown;
        static list<Work> m_taskQueue;
        static pthread_cond_t m_isReady;
        static pthread_mutex_t m_mutex;
    private:
        class lock // 异常安全的加锁方式
        {
            public:
                lock()  { pthread_mutex_lock(&m_mutex); }
                ~lock() { pthread_mutex_unlock(&m_mutex); }
        };
        friend class lock;
};



#endif   /* ----- #ifndef THREADPOOL_INC  ----- */
//vim:set tabstop=4 expandtab fileencoding=utf-8 ff=unix ft=cpp norl:

