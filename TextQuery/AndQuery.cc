/*
 * @Author: xuhuanhuan(hhxu@robvision) 
 * @Date: 2019-12-29 16:38:23 
 * @Last Modified by: xuhuanhuan(hhxu@robvision.cn)
 * @Last Modified time: 2020-01-01 21:36:13
 */
#include "AndQuery.h"

inline Query operator&(const Query& lhs, const Query& rhs)
{
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

QueryResult AndQuery::eval(const TextQuery& text) const
{
    auto left = lhs.eval(text);
    auto right = rhs.eval(text);
    auto ret_lines = std::make_shared<std::set<LineNo> >();
    std::set_intersection(left.begin(), left.end(),right.begin(), right.end(),std::inserter(*ret_lines,ret_lines->begin()));  
    return QueryResult(rep(), ret_lines, left.get_file());
}
