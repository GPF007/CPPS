#include <unordered_set>
#include <string>

using std::string;

class Sym{
private:
    std::unordered_set<string> sym_tab_;

public:

    Sym() = default;

     //得到符号的地址
    const string* get_sym(string s){
        auto it = sym_tab_.find(s);
        if(it==sym_tab_.end())
            return nullptr;
        return &(*it);//返回该符号的地址
    }

    void put_sym(string s){
        sym_tab_.insert(s);
    }

     //得到符号的地址
    const string* get_sym_full(string s){
        auto it = get_sym(s);
        if(it !=nullptr) return it;

        put_sym(s);
        return get_sym(s);

    }

};