/*
 * @Author: xuhuanhuan(hhxu@robvision) 
 * @Date: 2020-01-01 21:37:45 
 * @Last Modified by:   xuhuanhuan(hhxu@robvision.cn) 
 * @Last Modified time: 2020-01-01 21:37:45 
 */
#pragma once

#include "TextQuery.h"
#include "Query_base.h"

class WordQuery:public Query_base{
    friend class Query;
    WordQuery(std::ostream& os, const std::string& s):os_(os),query_word(s){}
    QueryResult eval(const TextQuery &t) const
    {
        return t.query(query_word);
    }
    std::string rep() const{return query_word;}
    std::string query_word;
    public:
        WordQuery(std::ostream& , std::pair<std::string, std::set<size_t> > res = {"",{}});
        bool print();

    private:
        std::ostream &os_;
        std::pair<std::string, std::set<size_t> > res_;
};