/*
 * @Author: xuhuanhuan(hhxu@robvision) 
 * @Date: 2019-12-29 16:34:51 
 * @Last Modified by: xuhuanhuan(hhxu@robvision.cn)
 * @Last Modified time: 2020-01-01 21:36:31
 */
#include "OrQuery.h"

inline Query operator|(const Query& lhs, const Query& rhs)
{
    return shared_ptr<Query_base>(new OrQuery(lhs,rhs));
}

QueryResult OrQuery::eval(const TextQuery& text) const
{
    auto left = lhs.eval(text);
    auto right = rhs.eval(text);
    auto ret_lines = std::make_shared<std::set<LineNo> >(left.begin(), left.end());
    ret_lines->insert(right.begin(), right.end());

    return QueryResult(rep(), ret_lines, left.get_file());
}
