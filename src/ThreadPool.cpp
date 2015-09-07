/*
 * =====================================================================================
 *
 *       Filename:  ThreadPool.cpp
 *
 *    Description:  ThreadPool
 *
 *        Version:  1.0
 *        Created:  2015-07-02 19:33:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhiyuan (search engine group), zhiyuan@taobao.com
 *        Company:  www.taobao.com
 *
 * =====================================================================================
 */

#include "ThreadPool.h"

unsigned int ThreadPool::m_iThreadNum = 0;
int ThreadPool::m_freeThreadNum = 0;
bool ThreadPool::m_shutdown = false;
list<Work>    ThreadPool::m_taskQueue;
pthread_cond_t  ThreadPool::m_isReady = PTHREAD_COND_INITIALIZER;
pthread_mutex_t ThreadPool::m_mutex   = PTHREAD_MUTEX_INITIALIZER;

ThreadPool::ThreadPool(int num)
{
    m_iThreadNum = num > ThreadMaxNum ? ThreadMaxNum : num;
    m_freeThreadNum = m_iThreadNum;

    for (int i = 0; i < m_iThreadNum; ++i)
        pthread_create(&m_threadID[i], NULL, ThreadFunc, NULL);
}

void* ThreadPool::ThreadFunc(void* arg)
{
    while(true)
    {
        {
            lock instance;
            if (m_taskQueue.empty() && !m_shutdown)
                pthread_cond_wait(&m_isReady, &m_mutex);
        }

        if (m_shutdown)
            break;

        Work work;

        work.function = NULL;
        
        {
            lock instance; // lock
            if (!m_taskQueue.empty())
            {
                work = m_taskQueue.front();
                m_taskQueue.pop_front();
                --m_freeThreadNum;
            }
        }

        if (work.function != NULL)
        {
            FunctionType func = work.function;
            func(work.arg);

            lock instance;
            ++m_freeThreadNum;
        }
    }
    pthread_exit(0);
}

void ThreadPool::AddWork(Work w)
{
    {
        lock instance;
        m_taskQueue.push_back(w);
    }
    pthread_cond_signal(&m_isReady);
}

ThreadPool::~ThreadPool()
{
    m_shutdown = true;
    pthread_cond_broadcast(&m_isReady);

    for (int i = 0; i < m_iThreadNum; ++i)
        pthread_join(m_threadID[i], NULL);

}
