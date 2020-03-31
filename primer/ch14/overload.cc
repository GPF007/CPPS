#include <iostream>
#include <vector>

using namespace std;

class Point{

public:

    friend ostream &operator<<(ostream &os, const Point &p);
    friend istream &operator>>(istream &is, Point &p);


    Point() = default;
    Point(int xx,int yy):x(xx),y(yy){}

    int& operator[](int i);
    const int& operator[](int i) const;


private:
    int x,y;

};


ostream &operator<<(ostream &os, const Point &p){
    os<<"x: "<<p.x<<"\t"<<"y: "<<p.y;
    return os;
}

istream &operator>>(istream &is, Point &p){
    is>>p.x>>p.y;
    if(!is)
        p = Point();
    return is;
}


int& Point::operator[](int i){
    if(i>=2) 
        return x;
    return i==0 ? x : y;
}
const int& Point::operator[](int i) const{
    if(i>=2) return x;
    return i==0 ? x : y;
}


int main(int argc, char const *argv[])
{
    Point p1(1,3);
    cout<<p1<<endl;
    cout<<p1[0]<< " "<<p1[1]<<endl;
    p1[0]=199;
    cout<<p1<<endl;
    /*
    vector<Point> pv;
    Point p;
    while(cin>>p){
        pv.push_back(p);
    }

    for(auto &p:pv)
        cout<<p<<endl;
    */



    return 0;
}

