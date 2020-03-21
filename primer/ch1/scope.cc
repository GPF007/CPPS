#include <iostream>
#include <iomanip>
using namespace std;

int reused = 42;//全局变量

int main(int argc, char const *argv[])
{
    /* code */
    int unique = 0;
    //输出全局变量
    cout<<reused<<" "<<unique<<endl;

    //覆盖了全局变量
    int reused =0;
    cout<<reused<<" "<<unique<<endl;
    
    //显示访问全局变量
    cout<<::reused<<" "<<unique<<endl;
    return 0;
}
