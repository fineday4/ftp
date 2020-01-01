/*
 * @Author: xuhuanhuan(hhxu@robvision) 
 * @Date: 2020-01-01 21:36:59 
 * @Last Modified by:   xuhuanhuan(hhxu@robvision.cn) 
 * @Last Modified time: 2020-01-01 21:36:59 
 */
#pragma once
#include "TextQuery.h"
#include "Query_base.h"

class NotQuery:public Query_base{
    friend Query operator~(const Query &);
    NotQuery(const Query &q):query(q){}
    std::string rep() const{return "~(" + query.rep() + ")";}
    QueryResult eval(const TextQuery&) const;
    Query query;
};