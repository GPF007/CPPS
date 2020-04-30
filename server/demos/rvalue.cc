
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

class Point{
public:
    Point() = default;
    Point(int x,int y):x_(x),y_(y){ cout<<"Constructer"<<endl; }
    //Point(const Point&p) = delete;
    
    Point(const Point& p){
        x_ =  p.x_;
        y_ = p.y_;
        cout<<"Copy construct"<<endl;
    }
    
    Point& operator=(const Point &p){
        x_ = p.x_;
        y_ = p.y_;
        cout<<"Assignment construct"<<endl;
    }
    Point(Point &&p):x_(p.x_),y_(p.y_){cout<<"Move construct"<<endl;}
    Point& operator=(const Point &&p){
        x_ = p.x_;
        y_ = p.y_;
        cout<<"Move ssignment construct"<<endl;
    }

private:
    int x_;
    int y_;

};


int main(int argc, char const *argv[])
{
    Point p1(1,2);
    Point p2(p1);
    Point p3;
    p3 = p1;

    Point p4(std::move(p1));
    Point p5;
    p5 = std::move(p2);

    return 0;
}
