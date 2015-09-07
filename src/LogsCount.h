/*
 * =====================================================================================
 * 
 *       Filename:  LogsCount.h
 * 
 *    Description:  
 * 
 *        Version:  1.0
 *        Created:  2015-06-29 10:36:29
 *       Revision:  none
 *       Compiler:  gcc
 * 
 *         Author:  zhiyuan (search engine group), zhiyuan@taobao.com
 *        Company:  www.taobao.com
 * 
 * =====================================================================================
 */

#ifndef  LOGSCOUNT_INC
#define  LOGSCOUNT_INC

#include<tr1/unordered_map>
#include<string>
#include<vector>

using std::tr1::unordered_map;
using std::string;
using std::vector;

typedef unordered_map <string, unsigned int> HashMap;
typedef HashMap::iterator hmIterator;
typedef HashMap::const_iterator hmConstIterator;

class LogInfor;  // 使用声明，减少文件间的依赖
class LogsCount;
void SumResult(LogsCount* p, int i, vector<LogInfor>& result);


class LogsCount
{
    // 友元函数，破坏封装，目前已经废弃
    friend void SumResult(LogsCount* p, int i, vector<LogInfor>& result);
    public:
        LogsCount() {}
        bool ProcessLog(const string& strLog);
        bool GetCountResult(vector<LogInfor>& result);
        const LogsCount& operator+=(const LogsCount& logscount);

    private:
        bool Add2Hashtable(const string& strLog);

    private:
        HashMap m_hashmap;
};

#endif   /* ----- #ifndef LOGSCOUNT_INC  ----- */
//vim:set tabstop=4 expandtab fileencoding=utf-8 ff=unix ft=cpp norl:

