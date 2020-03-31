#include <iostream>
#include <cstddef>
#include <string>
#include <cstdio>

using namespace std;


int main(int argc, char const *argv[])
{
    string res;
    char *cp;
    printf("argv is %d\n",argc);
    for(int i=0;i<argc;i++){
        printf("argv[%d] = %s\n",i,argv[i]);
        res+=argv[i];
    }

    cout<<res<<endl;
    return 0;
}
