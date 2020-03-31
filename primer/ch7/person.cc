#include "person.h"

istream &read(istream &is, Person& p)
{
    is>>p.name>>p.address;
    return is;
}

ostream &print(ostream &os, const Person &p)
{
    os<<"name: "<<p.name<<" address: "<<p.address;
    return os;
}

