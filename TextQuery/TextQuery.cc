/*
 * @Author: xuhuanhuan(hhxu@robvision) 
 * @Date: 2019-12-30 22:59:20 
 * @Last Modified by: xuhuanhuan(hhxu@robvision.cn)
 * @Last Modified time: 2020-01-01 21:39:45
 */
#include "TextQuery.h"

TextQuery::TextQuery(ifstream &infile)
    :_sp_text(new vector<string>)
{
    string s;
    LineNo line = 0;
    while(getline(infile,s)){
        _sp_text->push_back(s);
        std::istringstream iss(s);
        string word;
        string word_tmp;
        while(iss >> word){
            std::remove_copy_if(word.begin(),word.end(),std::back_inserter(word_tmp),ispunct);
            auto & sp = _sp_words[word_tmp];
            if(!sp){
                sp.reset(new set<LineNo>);
            }
            sp->insert(line);
            word.clear();
            word_tmp.clear();
        }
        ++line;
    }
#if 1
    for(auto& i : _sp_words){
        cout << "word: " << i.first;
        for(auto& ii : *(i.second)){
            cout << " " << ii;
        }
        cout << endl;
    }
#endif
}

#if 1
QueryResult TextQuery::query(const string &word) const
{
    auto line = _sp_words.find(word);
    if(line == _sp_words.end()){
        std::cout << "NO WORD!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        return QueryResult(word,std::make_shared<std::set<LineNo> >() , std::make_shared<vector<string>>());
    }
    return QueryResult(word, line->second,  _sp_text);
}
#endif
#if 0
class QueryResult{
    private:

};


void runQueries(ifstream &infile)
{
    TextQuery tq(infile);
    while(true){
        cout << "enter word to look for, or q to quit: ";
        string s;
        if(!(std::cin >> s)|| s == "q"){
            break;
        }
        cout << tq.Query(s);
    }
}

int main()
{
    ifstream ifs("TextQuery.cc");
    if(!ifs.good())
    {
        throw std::runtime_error("open file error");
    }
    runQueries(ifs);
}
#endif