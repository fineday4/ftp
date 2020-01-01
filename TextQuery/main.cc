//#include "./basket.cc"
#include "OrQuery.cc"
#include "AndQuery.cc"
#include "NotQuery.cc"
#include "WordQuery.cc"
#include "Query_base.cc"
#include "TextQuery.cc"

#include <iostream>

#if 0
double print_total(std::ostream &os, const Quote &item, size_t n)
{
    os << "ISBN: " << item.isbn() << " #sold: " << n << " total due: " << item.net_price(n) << std::endl;
}
#endif

int main()
{
#if 0 
    Quote quo("C++ Primer", 102.22);
    Bulk_quote bkq("CXXXXX", 102.22, 3, 0.3);
   // print_total(std::cout, bkq, 5);
    Basket my_basket;
    my_basket.add_item(quo);
    my_basket.add_item(bkq);
    my_basket.add_item(bkq);
    my_basket.add_item(quo);
    my_basket.add_item(quo);
    my_basket.add_item(bkq);
    my_basket.total_receipt(std::cout);
#endif
    Query q = Query("rm") & ~Query("te");
    std::ifstream ifs("test.txt");
    if(!ifs.good()){
        std::cerr << "file open error" << std::endl;
        return 0;
    }
    TextQuery text(ifs);
    QueryResult res = q.eval(text);
    std::cout <<"RESULT: " << res << std::endl;
    std::cout << "over~" << std::endl;
    return 0;
}