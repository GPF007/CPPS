#include <iostream>
#include "../stack.h"

using namespace std;

/*
    Convert demical number n to other base(hex,oct...)
    1 < base <= 16
*/
void convert(Stack<char>& S,long n,int base){
    static char digit[]={'0','1','2','3','4','5','6','7',
                        '8','9','A','B','C','D','E','F'};
    while(n>0){
        S.push(digit[n%base]);
        n/=base;
    }
}

void show_digit(Stack<char>& S){
    while(!S.empty()){
        cout<<S.pop();
    }
    cout<<endl;
    
}

int main(int argc, char const *argv[])
{
    cout<<"Hello world!"<<endl;    
    Stack<char> st;
    convert(st,100,16);
    show_digit(st);
    return 0;
}
