#include <string>
#include <iostream>

using std::string;
using std::ostream;
using std::istream;

class Person{


public:

    /*常有构造函数*/
    Person() = default;
    Person(const string n, const string a):
    name(n),address(a){}
    Person(istream &is) {read (is,*this);}

    auto get_name() const ->string const&{return name;}
    auto get_addr() const ->string const&{return address;} 

    /*friend函数*/
    friend istream &read(istream&, Person&);
    friend ostream &print(ostream&, const Person&);

private:

    string name;
    string address;



};

Person add(const Person&, const Person&);
ostream &print(ostream&, const Person&);
istream &read(istream&, Person&);