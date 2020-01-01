/*
 * @Author: xuhuanhuan(hhxu@robvision) 
 * @Date: 2020-01-01 21:35:51 
 * @Last Modified by:   xuhuanhuan(hhxu@robvision.cn) 
 * @Last Modified time: 2020-01-01 21:35:51 
 */
#pragma once

#include "TextQuery.h"
#include "BinaryQuery.h"

class AndQuery:public BinaryQuery{
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query &left, const Query &right)
    :BinaryQuery(left, right, "&")
    {}

    QueryResult eval(const TextQuery& ) const;
};
