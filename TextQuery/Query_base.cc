/*
 * @Author: xuhuanhuan(hhxu@robvision) 
 * @Date: 2019-12-29 16:37:14 
 * @Last Modified by: xuhuanhuan(hhxu@robvision.cn)
 * @Last Modified time: 2020-01-01 21:38:53
 */

#include "WordQuery.h"
#include "Query_base.h"
#include <iostream>
#include <string>


#include "Query_base.h"

std::ostream &operator<<(std::ostream& os, const Query &query)
{
    os << query.rep();
}

inline Query::Query(const std::string& s):q(new WordQuery(std::cout,s)){}