/*
 * @Author: xuhuanhuan(hhxu@robvision) 
 * @Date: 2019-12-29 16:37:10 
 * @Last Modified by: xuhuanhuan(hhxu@robvision.cn)
 * @Last Modified time: 2020-01-01 21:37:13
 */

#include "NotQuery.h"

inline Query operator~(const Query &operand)
{
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

QueryResult NotQuery::eval(const TextQuery& text) const
{
    auto result = query.eval(text);
    auto ret_lines = std::make_shared<std::set<LineNo> >();
    auto beg = result.begin();
    auto end = result.end();
    auto sz = result.get_file()->size();
    for(auto i = 0; i != sz; ++i){
        if(beg == end || *beg != i){
            ret_lines->insert(i);
        }else if(beg != end){
            ++beg;
        }
    }

    return QueryResult(rep(), ret_lines, result.get_file());
}
