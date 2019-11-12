#include <iostream>
#include "splay.h"




using namespace std;

//function object
template <typename T>
struct Print{
    virtual void operator()(T& e){
        cout<<e<<" ";
    }
};

void levelPrint(BinTree<int>* tree,Print<int> & prt){
    cout<<"Travel by Level:"<<endl;
    tree->travLevel(prt);
    cout<<endl;
    cout<<"The height of tree is: "<<tree->root()->height<<endl;
}

void inorderPrint(BinTree<int>* tree,Print<int> & prt){
    cout<<"Travel by Inorder:"<<endl;
    tree->travIn(prt);
    cout<<endl;
    //cout<<"The height of tree is: "<<tree->root()->height<<endl;
}


int main(int argc, char const *argv[])
{
    cout<<"Hello world!"<<endl;
    Splay<int> *tree=new Splay<int>;
    auto prt=Print<int>();
    for(int i=0;i<16;i++){
        tree->insert(15-i);
    }
    tree->search(15);
    //tree->search(12);
    levelPrint(tree,prt);
    inorderPrint(tree,prt);

    return 0;
}
