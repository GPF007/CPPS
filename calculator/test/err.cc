#include <iostream>
#include <cstdio>



int main(int argc, char const *argv[])
{
    int expected ='a';
    int pek_ = 'c';

    fprintf(stderr,"expected %c but got %c",expected,pek_);
    return 0;
}
