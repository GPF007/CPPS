#include <iostream>
#include <string>
using namespace std;


class Point{

public:
    Point() = default;
    Point(string xx,string yy):x(xx),y(yy){ cout<<"Construct"<<endl; }
    Point(const Point&);
    Point(Point &&)noexcept;

    string x,y;

};


Point::Point(const Point& p){
    x = p.x;
    y = p.y;
    cout<<"Copy construct"<<endl;
}

Point::Point(Point&& p) noexcept{
    x = std::move(p.x);
    y = std::move(p.y);
    cout<<"Move construct"<<endl;
}







int main(int argc, char const *argv[])
{
    /* code */

    Point p1("a","b");
    Point p2(p1); 

    Point p3(std::move(p2));
    cout<<p3.x<<p3.y<<endl;
    

    return 0;
}
