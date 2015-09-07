/*
 * =====================================================================================
 * 
 *       Filename:  ReadData.h
 * 
 *    Description:  
 * 
 *        Version:  1.0
 *        Created:  2015-06-29 09:22:21
 *       Revision:  none
 *       Compiler:  gcc
 * 
 *         Author:  zhiyuan (search engine group), zhiyuan@taobao.com
 *        Company:  www.taobao.com
 * 
 * =====================================================================================
 */

#ifndef  READDATA_INC
#define  READDATA_INC

#include<fstream>
#include<string>
using namespace std;

typedef unsigned int uint;

class ReadData
{
    public:
        ReadData() {}
        bool Open(const string& strPath);
        uint GetLine(string& strLine);
        bool Close();

    private:
        ifstream m_infile;

};

#endif   /* ----- #ifndef READDATA_INC  ----- */
//vim:set tabstop=4 expandtab fileencoding=utf-8 ff=unix ft=cpp norl:

