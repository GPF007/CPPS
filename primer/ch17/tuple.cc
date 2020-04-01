#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <list>

using namespace std;

int main(int argc, char const *argv[])
{
    tuple<size_t,size_t,size_t> threeD;
    tuple<string,vector<double>,int,list<int>>
        someVal("constants",{3.14,2.7},42,{0,1,2,3});

    auto item = make_tuple("0-999-78",3,20.00);
    auto book = get<0>(item);
    auto cnt = get<1>(item);
    auto price = get<2>(item)/cnt;
    get<2>(item) *=0.8;

    typedef decltype(item) trans;
    //返回trans类型对象成员的数量
    size_t sz = tuple_size<trans>::value;

    tuple_element<1,trans>::type cnt = get<1>(item);


    return 0;
}
