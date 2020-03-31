#include <iostream>
#include <string>
#include <map>

using namespace std;

struct Point{
    int x;
    int y;
};

bool comparePoint(const Point &lhs,const Point &rhs){
    return lhs.x < rhs.x && lhs.y <rhs.y;
}

int main(int argc, char const *argv[])
{
    using Less = bool(*)(const Point &lhs,const Point &rhs);
    map<Point, int,decltype(comparePoint)*> m1;
    map<Point, int,Less> m2;


    return 0;
}
