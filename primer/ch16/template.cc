#include <iostream>
#include <vector>
#include <type_traits>
using namespace std;

//显示地模板推断实参
template <typename T1, typename T2, typename T3>
T1 sum(T2 t2,T3 t3){
    return t2 + t3;
}

template <typename It>
auto fcn(It beg, It end) -> decltype(*beg)
{
    while(beg!=end){
        cout<<*beg<<" ";
        ++beg;
    }
    cout<<endl;
    return *beg;//返回引用
}

template <typename It>
auto fcn2(It beg, It end) -> typename remove_reference<decltype(*beg)>::type
{
    auto tmp = beg;
    while(beg!=end){
        cout<<*beg<<" ";
        ++beg;
    }
    cout<<endl;
    return *tmp;//返回拷贝
}

int main(int argc, char const *argv[])
{
    /*
    int i =0;
    long lng = 10;
    auto val3 = sum<long long>(i,lng);//T2->int T3->long
    */
    vector<int> v1 = {1,2,3,4,5};
    vector<string> v2 = {"hello","my","world"};

    auto &i = fcn(v1.begin(),v1.end());
    auto &s = fcn(v2.begin(), v2.end());

    auto i2 = fcn2(v1.begin(),v1.end());
    auto s2 = fcn2(v2.begin(), v2.end());

    return 0;
}
