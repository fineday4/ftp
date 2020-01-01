/*
 * @Author: xuhuanhuan(hhxu@robvision) 
 * @Date: 2020-01-01 21:40:04 
 * @Last Modified by:   xuhuanhuan(hhxu@robvision.cn) 
 * @Last Modified time: 2020-01-01 21:40:04 
 */

#pragma once

#include "all.h"

using LineNo = vector<string>::size_type;
class QueryResult{
    public:
        friend std::ostream& operator<<(std::ostream&, const QueryResult&);
        QueryResult(string s, shared_ptr<set<LineNo> > ps, shared_ptr<vector<string> > pf)
             :file(pf)
             ,lines(ps)
             ,sought(s)
    {}

    set<LineNo>::iterator begin(){return lines->begin();}
    set<LineNo>::iterator end(){return lines->end();}
    shared_ptr<vector<string> > get_file(){return file;}
    private:
        shared_ptr<vector<string> > file;
        shared_ptr<set<LineNo> > lines;
        string sought;
};
class TextQuery{
    public:
        TextQuery(ifstream &infile);
        QueryResult query(const string& word) const;
    private:
        shared_ptr<vector<string> > _sp_text;
        map<string, shared_ptr<set<LineNo> > > _sp_words;

};

std::ostream& operator<<(std::ostream& os, const QueryResult& res)
{
    os << "FUNC: " << res.sought << " RES: " << std::endl;
    os << "SIZE: " << res.lines->size() << std::endl;
    for(auto i : *(res.lines)){
        if(res.file){
            std::cout << "i: " << i << std::endl;
            os << "STR: " << res.file->operator[](i) << std::endl;
        }else{
            os << "STR: " << "NOT THIS WORD!!" << std::endl;
        }
    }
    os << "operator<< over" << std::endl;
} 