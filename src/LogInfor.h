/*
 * =====================================================================================
 * 
 *       Filename:  LogInfor.h
 * 
 *    Description: 
 * 
 *        Version:  1.0
 *        Created:  2015-06-29 10:27:37
 *       Revision:  none
 *       Compiler:  gcc
 * 
 *         Author:  zhiyuan (search engine group), zhiyuan@taobao.com
 *        Company:  www.taobao.com
 * 
 * =====================================================================================
 */

#ifndef  LOGINFOR_INC
#define  LOGINFOR_INC

#include<string>

using std::string;

class LogInfor
{
    public:
        LogInfor(): m_count(0), m_strLog() {}
        LogInfor(const string& strLog, unsigned int count): m_count(count), m_strLog(strLog) {}
        unsigned int m_count; // 该日志出现的次数
        string m_strLog;  // 日志内容
};

#endif   /* ----- #ifndef LOGINFOR_INC  ----- */
//vim:set tabstop=4 expandtab fileencoding=utf-8 ff=unix ft=cpp norl:

