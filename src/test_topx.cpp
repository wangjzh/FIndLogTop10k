/*
 * =====================================================================================
 *
 *       Filename:  test_topx.cpp
 *
 *    Description:  test
 *
 *        Version:  1.0
 *        Created:  2015-06-30 11:52:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhiyuan (search engine group), zhiyuan@taobao.com
 *        Company:  www.taobao.com
 *
 * =====================================================================================
 */
#include <assert.h>
#include <unistd.h>
#include "ThreadPool.h"
#include "LogsCount.h"
#include <iostream>
#include "TopX.h"
#include "LogInfor.h"
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <pthread.h>

using namespace std;

const int g_nProductLogSum = 50000;  // 产生日志条数
const int g_nThreadNum = 5;             // 使用几个线程同时count 
const int g_nTopX = 100;              // top x

LogsCount g_logscount[g_nThreadNum]; // 每个线程产生的中间结果 

// 输出vector<LogInfor>容器元素
void prt(vector<LogInfor>& datavec)
{
    vector<LogInfor>::iterator it = datavec.begin();
    vector<LogInfor>::iterator end = datavec.end();
    int flage = 0;
    int prtSum = 0;
    for (; it != end; ++it)
    {
        cout << it->m_strLog << ":" << it->m_count << "   ";
        prtSum += it->m_count;
        ++flage;
        if (flage %10 == 0)
            cout << endl;
    }

    cout << "prtSum :" << prtSum << endl;
}

// 用于count的线程参数
typedef struct thread_arg
{
    LogsCount* pLogsCount;
    int i;  // g_logscount的下标
    vector<string>::iterator first;
    vector<string>::iterator last;
} ThreadArg;

// 用于sum的参数
typedef struct thread_arg_2
{
    LogsCount* pLogsCount;
    int i; // g_logscount数组下标
    int j; // g_logscount数组下标
} ThreadArg2;

// thread count
void thread_fun_count(void *arg)
{
    ThreadArg* threadarg = (ThreadArg*)arg;
    LogsCount* pLogsCount = threadarg->pLogsCount; 
    vector<string>::iterator it = threadarg->first;
    vector<string>::iterator last = threadarg->last;
    int i = threadarg->i;

    assert(NULL != pLogsCount);
    for (; it != last; ++it)
        pLogsCount[i].ProcessLog(*it);

    delete arg;
    arg = NULL;
}

// thread sum,把中间结果合起来
void thread_fun_sum(void *arg)
{
    ThreadArg2* threadArg2 = (ThreadArg2*)arg;
    LogsCount* pLogsCount = threadArg2->pLogsCount;
    int i = threadArg2->i;
    int j = threadArg2->j;

    // i < j
    assert(i < j);
    assert(NULL != pLogsCount);
    pLogsCount[i] += pLogsCount[j];

    delete arg;
    arg = NULL;
}

// 调用线程count
// 直接依赖与全局变量是不好的做法，有时间的话可以改为传入参数的方式
void countSum(int num, ThreadPool& threadpool)
{
    for (int i = 0; i < num/2; ++i)
    {
        ThreadArg2* arg = new ThreadArg2;
        arg->pLogsCount = g_logscount;
        arg->i = i;
        arg->j = num - i -1;
        Work w;
        w.function = thread_fun_sum;
        w.arg = arg;
        threadpool.AddWork(w);
    }

    while(!threadpool.AllFree())
        sleep(1);
}

void CreateLog(vector<string>& datasrc)
{
    // 直接调整大小为g_nProductLogSum,优化vector存放数据的性能
    datasrc.reserve(g_nProductLogSum);
    srand((int)time(NULL));
    char tmp[1024];
    for(int i = 0; i < g_nProductLogSum; ++i)
    {
        sprintf(tmp, "%d", (rand() + rand())%10000);
        datasrc.push_back(tmp);
    }
}

// 直接依赖与全局变量是不好的做法，有时间的话可以改为传入参数的方式
void LogCount(vector<string>& datasrc, ThreadPool& threadpool)
{
    cout << "start logcount" << endl;
    time_t beginTime = time(0);
    vector<string>::iterator first = datasrc.begin();
    vector<string>::iterator last = datasrc.end();
    vector<string>::size_type size = datasrc.size();
    for (int i = 0; i < g_nThreadNum ; ++i)
    {
        ThreadArg* arg = new ThreadArg;
        arg->i = i;
        arg->pLogsCount = g_logscount;
        arg->first = first + size/g_nThreadNum * i;
        arg->last = first + size/g_nThreadNum * (i + 1);
        if (i == g_nThreadNum - 1)
            arg->last = last;

        cout << "第" << i << "个线程:" << "count [" << arg->first - first << "," << arg->last - first << "]" << endl;
        Work w;
        w.function = thread_fun_count;
        w.arg = (void *)arg;
        threadpool.AddWork(w);  // 向线程池添加任务
    }

    while(!threadpool.AllFree()) // 等待任务执行结束
        sleep(1);

    time_t countEndTime = time(0);
    cout << "thread count time: " << countEndTime - beginTime << endl;

    // g_logscount[n], 每次把 g_logscount[n -i - 1] 数据合入g_logscount[i];
    int needSumNum = g_nThreadNum;
    while (needSumNum > 1)
    {
        countSum(needSumNum, threadpool);

        if (needSumNum % 2 == 0)
            needSumNum = needSumNum / 2;
        else
            needSumNum = needSumNum / 2 + 1;
    }

    time_t threadSumTime  = time(0);
    cout << "thread count sum time : " << threadSumTime - countEndTime << endl;
 
}

// 直接依赖与全局变量是不好的做法，有时间的话可以改为传入参数的方式
vector<LogInfor>::iterator FindTopX(vector<LogInfor>& datavec)
{
    time_t startFindTopTime  = time(0);
    g_logscount[0].GetCountResult(datavec);  // 获取最终的统计结果
    cout << "size after logscount: " << datavec.size() << endl;
    
    TopX_partion topx;
    topx.SetDataSource(&datavec);
    cout << "start find top" << g_nTopX << endl;
    topx.FindTopX(g_nTopX);  // 获取topx的数据,topx数据最终存储在 datavec.end()-x ~ datavec.end()

    time_t endFindTopTime = time(0);
    cout << "Find topX time : " << endFindTopTime - startFindTopTime << endl;
    cout << "finish" << endl;
    vector<LogInfor>::iterator start = datavec.end() - g_nTopX;
    return start;
}

int main()
{
	ThreadPool  threadpool(30);
    vector<string> datasrc;         // 用于存储产生的伪造日志
    CreateLog(datasrc); // 目前没有真实的日志数据，则自己伪造数据
    LogCount(datasrc, threadpool); // 统计数据
   
    vector<LogInfor> datavec;
    vector<LogInfor>::iterator start = FindTopX(datavec); // find topx
    vector<LogInfor>::iterator end = datavec.end();  // target: start~end

    return 0; 
}
