/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015-06-29 16:59:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhiyuan (search engine group), zhiyuan@taobao.com
 *        Company:  www.taobao.com
 *
 * =====================================================================================
 */

#include"LogsCount.h"
#include"LogInfor.h"
#include<string>
#include<vector>
#include<iostream>

using namespace std;

int main()
{

    LogsCount logscount;

    logscount.ProcessLog("1");
    logscount.ProcessLog("2");
    logscount.ProcessLog("3");
    logscount.ProcessLog("4");
    logscount.ProcessLog("5");
    logscount.ProcessLog("6");

    vector<LogInfor> result;

    logscount.GetCountResult(result);
    vector<LogInfor>::iterator it = result.begin();
    vector<LogInfor>::iterator end = result.end();

    for (; it!= end; ++it)
        cout << "Log: " << it->m_strLog << " count: " << it->m_count << endl;

}
