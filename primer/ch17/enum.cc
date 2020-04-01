#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

enum color{red,yellow,green};
enum class peppers {red,yello,green};

int main(int argc, char const *argv[])
{
    color c1 = green;
    cout<<c1<<endl;
    peppers p1 = peppers::green;
    return 0;
}
