/*
 * @Author: xuhuanhuan(hhxu@robvision) 
 * @Date: 2020-01-01 21:35:12 
 * @Last Modified by: xuhuanhuan(hhxu@robvision.cn)
 * @Last Modified time: 2020-01-01 21:36:30
 */
#pragma once
#include "TextQuery.h"
#include "BinaryQuery.h"

class OrQuery:public BinaryQuery{
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query& lhs, const Query& rhs)
    :BinaryQuery(lhs,rhs, "|")
    {}
    QueryResult eval(const TextQuery& ) const;
};