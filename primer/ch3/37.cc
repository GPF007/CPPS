#include <iostream>


using namespace std;

/*该做法十分不安全，ca后面没有\0*/
int main(int argc, char const *argv[])
{
    const char ca[] = {'h','e','l','l','o'};
    const char *cp =ca;
    while(*cp){
        cout<<*cp<<endl;
        ++cp;
    }
    return 0;
}
