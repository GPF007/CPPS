#include <iostream>

#include "rbtree.h"

using namespace std;


//function object
template <typename T>
struct Print{
    virtual void operator()(T& e){
        cout<<e<<" ";
    }
};

int main(int argc, char const *argv[])
{
    cout<<"Hello world!"<<endl;
    RedBlack<int>* tree = new RedBlack<int>;
    tree->insert(0);
    tree->insert(1);
    
    tree->insert(2);
    tree->insert(3);
    tree->insert(4);
    tree->insert(5);
    tree->insert(6);
    tree->insert(7);
    tree->insert(8);
    tree->insert(9);


    auto prt=Print<int>();
    cout<<"Travel by inoder:"<<endl;
    tree->travIn(prt);
    cout<<endl;
    cout<<"The height of tree is: "<<tree->root()->height<<endl;

    cout<<"Travel by Level:"<<endl;
    tree->travLevel(prt);
    cout<<endl;
    cout<<"The height of tree is: "<<tree->root()->height<<endl;

    return 0;
}