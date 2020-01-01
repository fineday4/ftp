/*
 * @Author: xuhuanhuan(hhxu@robvision) 
 * @Date: 2019-12-29 16:37:37 
 * @Last Modified by: xuhuanhuan(hhxu@robvision.cn)
 * @Last Modified time: 2020-01-01 21:42:26
 */

#pragma once

#include "Query_base.h"
#include <string>

class BinaryQuery:public Query_base{
    protected:
        BinaryQuery(const Query &l, const Query &r, std::string s)
        :lhs(l), rhs(r), opSym(s)
        {}
        Query lhs, rhs;

        std::string rep()const{return "(" + lhs.rep()+ " " + opSym + " " + rhs.rep() + ")";}
        std::string opSym;
};