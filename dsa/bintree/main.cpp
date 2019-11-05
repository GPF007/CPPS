#include <iostream>

#include "bintree.h"

using namespace std;


/*
                1
            /       \
            2       3
        /       \   /
        4        5  6
*/


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
    
    BinTree<int> *tree=new BinTree<int>;
    tree->insertAsRoot(1);
    BinNodePosi(int) l=tree->insertAsLC(tree->root(),2);
    BinNodePosi(int) r=tree->insertAsRC(tree->root(),3);
    tree->insertAsLC(l,4);
    tree->insertAsRC(l,5);
    tree->insertAsLC(r,6);

    auto prt=Print<int>();
    /*
    cout<<"Preorder recrusion:"<<endl;
    travPre_R(tree->root(),prt);
    cout<<endl;

    cout<<"Preorder iteration:"<<endl;
    travPre_I(tree->root(),prt);
    cout<<endl;

    cout<<"Inorder recrusion:"<<endl;
    travIn_R(tree->root(),prt);
    cout<<endl;

    cout<<"Inorder iteration:"<<endl;
    travIn_I(tree->root(),prt);
    cout<<endl;

    cout<<"Postorder recrusion:"<<endl;
    travPost_R(tree->root(),prt);
    cout<<endl;

    cout<<"Postorder literation:"<<endl;
    travPost_I(tree->root(),prt);
    cout<<endl;

    cout<<"Level literation:"<<endl;
    travLevel_I(tree->root(),prt);
    cout<<endl;
    */

    cout<<"Preorder:"<<endl;
    tree->travPre(prt);
    cout<<endl;

    tree->remove(tree->root()->lChild);
    tree->travPre(prt);
    return 0;
}
