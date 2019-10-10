#include <iostream>
#include <string>

#include "cache.h"

using namespace std;

int main(){
    std::cout<<"Hello world!"<<std::endl;
    cache::Cache<string,int> cache(10);
    cache.Put("SS",123);
    cout<<cache.Get("ss")<<endl;
    return 0;
}