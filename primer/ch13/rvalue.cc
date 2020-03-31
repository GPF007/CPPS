#include <iostream>

using namespace std;



class Foo{
public:
    Foo &operator=(const Foo&) &;

    int a;
};

Foo &Foo::operator=(const Foo &rhs) &
{
    this->a = rhs.a;
    return *this;
}

int main(int argc, char const *argv[])
{
    /* code */

    int i =42;

    int &&rr1 = 42;
    int &&r3 = std::move(i);
    cout<<r3<<endl;



    return 0;
}
