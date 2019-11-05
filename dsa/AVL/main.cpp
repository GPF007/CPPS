#include <iostream>
#include "avl.h"

using namespace std;

//function object
template <typename T>
struct Print{
    virtual void operator()(T& e){
        cout<<e<<" ";
    }
};

void levelPrint(AVL<int>* tree,Print<int> & prt){
    cout<<"Travel by Level:"<<endl;
    tree->travLevel(prt);
    cout<<endl;
    cout<<"The height of tree is: "<<tree->root()->height<<endl;
}

void inorderPrint(AVL<int>* tree,Print<int> & prt){
    cout<<"Travel by Inorder:"<<endl;
    tree->travIn(prt);
    cout<<endl;
    //cout<<"The height of tree is: "<<tree->root()->height<<endl;
}

int main(int argc, char const *argv[])
{
    cout<< "Hello world!"<<endl;
    AVL<int> *tree = new AVL<int>;

    auto prt=Print<int>();

    tree->insertAsRoot(1);
    tree->insert(2);
    tree->insert(3);
    tree->insert(4);
    tree->insert(5);
    tree->insert(6);
    tree->insert(7);
    tree->insert(8);

    levelPrint(tree,prt);

    inorderPrint(tree,prt);


    tree->remove(6);
    levelPrint(tree,prt);

    //inorderPrint(tree,prt);

    return 0;


}
