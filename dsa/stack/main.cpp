#include <iostream>
#include <cstdio>
#include "stack.h"
using namespace std;

//function object




int main(int argc, char const *argv[])
{
    cout<<"Hello world"<<endl;
    Stack<int> st;
    st.push(10);
    st.push(11);
    while(st.size()!=0){
        cout<<st.pop()<<endl;
    }

    return 0;
}


