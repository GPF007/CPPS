#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char const *argv[])
{
    const char s1[]="hello ";
    const char *s2 = "world";
    char s3[80];

    strcpy(s3,s1);
    strcat(s3,s2);
    cout<<s3<<endl;

    return 0;
}
