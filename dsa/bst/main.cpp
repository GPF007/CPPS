#include <iostream>
#include "BST.h"

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
    //BinTree<int> *tree=new BinTree<int>;
    BST<int> *tree=new BST<int>;
    tree->insertAsRoot(36);
    tree->insert(27);
    tree->insert(58);
    tree->insert(6);
    tree->insert(53);
    tree->insert(46);
    tree->insert(69);

    auto prt=Print<int>();
    cout<<"Travel by inoder:"<<endl;
    tree->travIn(prt);
    cout<<endl;
    cout<<"The height of tree is: "<<tree->root()->height<<endl;
    tree->remove(36);

    cout<<"Travel by inoder:"<<endl;
    tree->travIn(prt);
    cout<<endl;
    cout<<"The height of tree is: "<<tree->root()->height<<endl;
    return 0;


}
