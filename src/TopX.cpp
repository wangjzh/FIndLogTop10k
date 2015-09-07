/*
 * =====================================================================================
 *
 *       Filename:  TopX.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015-06-30 09:16:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhiyuan (search engine group), zhiyuan@taobao.com
 *        Company:  www.taobao.com
 *
 * =====================================================================================
 */

#include "LogInfor.h"
#include <assert.h>
#include "TopX.h"
void TopX_partion::SetDataSource(LogsInforVector* pDataVec)
{
    assert(NULL != pDataVec);
    m_pDataSourceVec = pDataVec;
    m_targetIter = m_pDataSourceVec->begin();
}

bool TopX_partion::FindTopX(unsigned int X)
{
    LogsInforVector::size_type size = m_pDataSourceVec->size();
    if (NULL == m_pDataSourceVec || X < 1 || X > size)
        return false;

    // 在size个中找出top size，不需要处理
    if (X == size)
        return true;
    
    LIVectorIterator it = m_pDataSourceVec->begin();
    LIVectorIterator first = m_pDataSourceVec->begin();
    LIVectorIterator last = m_pDataSourceVec->end() - 1;

    m_targetIter = first + size - X;


    // 利用快排查找最大的K个数
    while(first < last)
    {
        it = Partion(first, last);

        if (it == m_targetIter)
            return true;
        else if (it > m_targetIter)
            last = it - 1;
        else if (it < m_targetIter)
            first = it + 1;
    }

    return false;
}

LIVectorIterator TopX_partion::Partion(LIVectorIterator first, LIVectorIterator last)
{
    LIVectorIterator l = first, h = last;
    LogInfor base = *l;
    while (l < h)
    {
        for (; l < h; --h)
        {
            if (h->m_count < base.m_count)
            {
                *l = *h;
                ++l;
                break;
            }
        }

        for (; l < h; ++l)
        {
            if (l->m_count > base.m_count)
            {
                *h = *l;
                --h;
                break;
            }
        }
    }

    *l = base;
    return l;
}
