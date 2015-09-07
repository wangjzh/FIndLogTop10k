/*
 * =====================================================================================
 *
 *       Filename:  ReadData.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015-06-29 09:38:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhiyuan (search engine group), zhiyuan@taobao.com
 *        Company:  www.taobao.com
 *
 * =====================================================================================
 */

#include"ReadData.h"

bool ReadData::Open(const string& strPath)
{
    m_infile(strPath.c_str());

    return !m_infile ? false : true;
}

bool ReadData::GetLine(string& strLine)
{
    if (m_infile)
    {
        getline(m_infile, );
    }
}
