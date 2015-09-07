/*
 * =====================================================================================
 * 
 *       Filename:  TopX.h
 * 
 *    Description:  获取topX的元素
 * 
 *        Version:  1.0
 *        Created:  2015-06-29 17:22:38
 *       Revision:  none
 *       Compiler:  gcc
 * 
 *         Author:  zhiyuan (search engine group), zhiyuan@taobao.com
 *        Company:  www.taobao.com
 * 
 * =====================================================================================
 */

#ifndef  TOPX_INC
#define  TOPX_INC

#include<vector>

using std::vector;

class LogInfor;
typedef vector<LogInfor> LogsInforVector;
typedef LogsInforVector::iterator LIVectorIterator;
typedef unsigned int uint;

class TopX_interface
{
    public:
        virtual bool FindTopX(unsigned int X) = 0;
};

class TopX_partion: public TopX_interface
{
    public:
        TopX_partion(): m_pDataSourceVec(NULL), m_uiTopX(0) {}
        
        void SetDataSource(LogsInforVector* dataVec);

        virtual bool FindTopX(uint X);

    private:
        LIVectorIterator Partion(LIVectorIterator first, LIVectorIterator last);

    private:
        LogsInforVector* m_pDataSourceVec;
        uint m_uiTopX;
        LIVectorIterator m_targetIter;
};

#endif   /* ----- #ifndef TOPX_INC  ----- */
//vim:set tabstop=4 expandtab fileencoding=utf-8 ff=unix ft=cpp norl:

