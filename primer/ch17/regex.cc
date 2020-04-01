#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <regex>

using namespace std;

int main(int argc, char const *argv[])
{
    string pattern("[^c]ei");
    //查找整个单词
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern);
    smatch results;

    string test_str = "receipt freind theif receive";
    if(regex_search(test_str,results,r))
        cout<<results.str()<<endl;


    for(sregex_iterator it(test_str.begin(),test_str.end(),r),end_it;
            it!=end_it; ++it)
            cout<<it->str()<<endl;

    return 0;
}
