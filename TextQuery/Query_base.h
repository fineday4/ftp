/*
 * @Author: xuhuanhuan(hhxu@robvision) 
 * @Date: 2020-01-01 21:38:43 
 * @Last Modified by:   xuhuanhuan(hhxu@robvision.cn) 
 * @Last Modified time: 2020-01-01 21:38:43 
 */
#pragma once

//面向接口使用者的类
#include "TextQuery.h"

class Query_base{
    private:
        friend class Query;
        virtual QueryResult eval(const TextQuery& ) const = 0;
        virtual std::string rep() const = 0;
    
    protected:
        using line_no = size_t;
        virtual ~Query_base() = default;
};

class Query{
    private:
        friend Query operator~(const Query &);
        friend Query operator|(const Query &, const Query &);
        friend Query operator&(const Query &, const Query &);

    public:
        Query(const std::string&);
        QueryResult eval(const TextQuery &t) const{return q->eval(t);}
        std::string rep() const{return q->rep();}

    private:
        Query(std::shared_ptr<Query_base> query): q(query){}
        std::shared_ptr<Query_base> q;
};
