

#include <unordered_set>
#include <string>

using namespace std;

class Sym{
    //static std::unordered_set<string> sym_tab_;



public:
    static std::unordered_set<string> sym_tab_;

    static std::unordered_set<string> init_sym()
    {
        std::unordered_set<string> tmp;
        tmp.insert("hwllo");
        return tmp;
    }

     //得到符号的地址
    static const string* get_sym(string s){
        auto it = sym_tab_.find(s);
        if(it==sym_tab_.end())
            return nullptr;
        return &(*it);//返回该符号的地址
    }

    static void put_sym(string s){
        sym_tab_.insert(s);
    }

};

int main(int argc, char const *argv[])
{

    Sym::sym_tab_ = Sym::init_sym();
    return 0;
}
