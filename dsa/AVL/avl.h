#include "../bst/BST.h"
#include <iostream>


//balance factor
#define Balanced(x) (starture((x).lChild) == starture((x).rChild)) //ideal
#define BalFac(x) (starture((x).lChild) - starture((x).rChild))
//AVL tree balanced condition
#define AvlBalanced(x) (( -2 < BalFac(x)) && (BalFac(x) < 2))
//get the taller child,if same take get the same side of parent node
#define tallerChild(x) (\
        starture((x)->lChild) > starture((x)->rChild) ? (x)->lChild :(\
        starture((x)->rChild) > starture((x)->lChild) ? (x)->rChild :(\
        IsLChild(*(x))?(x)->lChild:(x)->rChild\
        )))


//AVL TREE
template <typename T>
class AVL:public BST<T>{
public:
    //overide insert and remove
    BinNodePosi(T) insert(const T& e);

    bool remove(const T& e);

};

//insert a node
template <typename T>
BinNodePosi(T) AVL<T>::insert(const T& e){
    BinNodePosi(T) & x=this->search(e);
    if(x) return x;
    //x must not exist

    x=new BinNode<T>(e,this->_hot);
    this->_size++;

    for(BinNodePosi(T) g=this->_hot;g;g=g->parent){
        if(!AvlBalanced(*g)){//rotate once

            BinNodePosi(T) &tmp= FromParentTo(*g);
            tmp = this->rotateAt(tallerChild(tallerChild(g)));
            break;
        }else{//do not need to rotate
            this->updateHeight(g);
        }
    }

    return x;
}

//remove a node
template <typename T>
bool AVL<T>::remove(const T& e){
    BinNodePosi(T) & x = this->search(e);
    if(!x) return false;

    this->removeAt(x,this->_hot);this->_size--;;

    for(BinNodePosi(T) g=this->_hot;g;g=g->parent){
        if(!AvlBalanced(*g)){
            BinNodePosi(T) &tmp= FromParentTo(*g);
            tmp = this->rotateAt(tallerChild(tallerChild(g)));
            g=tmp;
        }
        //g=FromParentTo(*g)=this->rotateAt(tallerChild(tallerChild(g)));
        this->updateHeight(g);
    } 

    return true;
}