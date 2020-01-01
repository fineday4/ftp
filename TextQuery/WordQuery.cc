/*
 * @Author: xuhuanhuan(hhxu@robvision) 
 * @Date: 2019-12-29 16:37:23 
 * @Last Modified by: xuhuanhuan(hhxu@robvision.cn)
 * @Last Modified time: 2020-01-01 21:37:58
 */
#include "WordQuery.h"

// WordQuery::WordQuery(std::ostream& os, std::pair<std::string, std::set<size_t> > res)
// :os_(os), res_(res)
// {
// }
#if 0
bool WordQuery::print()
{
    
    if(res_.first.length()){
        os_ << "Word: " << res_.first << " at: " << std::endl;
        for (auto i = res_.second.cbegin(); i != res_.second.cend(); i++)
        {
            os_ << "LINE: " << *i << " str: " << str_vec[*i] << std::endl;
        } 
        return true;
    }else{
        os_ << "NO WORD!!!" << std::endl;
        return false;
    }
    
}
#endif
#if 0

int main()
{
    TextQuery text("history");
    std::string tmp;
    while(std::cin >> tmp){
        WordQuery& wq = text.Query(tmp, std::cout);
        wq.print();
    }
}

#endif