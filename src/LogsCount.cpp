/*
 * =====================================================================================
 *
 *       Filename:  LogsCount.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015-06-29 11:54:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhiyuan (search engine group), zhiyuan@taobao.com
 *        Company:  www.taobao.com
 *
 * =====================================================================================
 */

#include <assert.h>
#include<vector>
#include<utility>
#include"LogsCount.h"
#include"LogInfor.h"

using std::vector;

// 使用友元函数，不是非常好，因为破坏了数据的封装性
// 目前该函数已经废弃
void SumResult(LogsCount* pLogsCount, int n, vector<LogInfor>& result)
{
    assert(NULL != pLogsCount);
    HashMap hashmap;
    for (int i = 0; i < n; ++i)
    {
        hmIterator it = pLogsCount[i].m_hashmap.begin();
        hmIterator end = pLogsCount[i].m_hashmap.end();
        for(; it != end; ++it)
            hashmap[it->first] += it->second;
    }
    
    hmIterator it = hashmap.begin();
    hmIterator end = hashmap.end();

    result.clear();
    for(; it != end; ++it)
    {
        result.push_back(LogInfor(it->first, it->second));
    }
}


bool LogsCount::ProcessLog(const string& strLog)
{
    return Add2Hashtable(strLog);
}

bool LogsCount::GetCountResult(vector<LogInfor>& resultVec)
{
    hmIterator it = m_hashmap.begin();
    hmIterator end = m_hashmap.end();

    resultVec.clear();
    for(; it != end; ++it)
    {
        resultVec.push_back(LogInfor(it->first, it->second));
    }

    return true;
}

bool LogsCount::Add2Hashtable(const string& strLog)
{
    // 如果之前没有strLog,对应的value会初始化为0吗?,测试结果是会
    ++m_hashmap[strLog];
    return true;
}

// return const LogsCount&
const LogsCount& LogsCount::operator+=(const LogsCount& other)
{
    hmConstIterator it = other.m_hashmap.begin();
    hmConstIterator end = other.m_hashmap.end();

    for (; it != end; ++it)
        m_hashmap[it->first] += it->second;
    return *this;
}
