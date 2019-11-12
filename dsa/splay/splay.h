#include "../bst/BST.h"


template <typename T>
class Splay:public BST<T> {
protected:
    //Help functions to splay node v
    BinNodePosi(T) splay(BinNodePosi(T) v);

public:
    BinNodePosi(T) & search(const T& e);
    BinNodePosi(T) insert(const T& e);
    bool remove(const T& e);
};


template <typename NodePosi> inline //connect p and lc
void attachAsLChild(NodePosi p,NodePosi lc){
    p->lChild = lc;
    if(lc) lc->parent = p;
}

template <typename NodePosi> inline //connect p and rc
void attachAsRChild(NodePosi p,NodePosi rc){
    p->rChild = rc;
    if(rc) rc->parent = p;
}

//splay start from node v
template <typename T>
BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v){
    if(!v) return NULL;
    BinNodePosi(T) p;//parent of v
    BinNodePosi(T) g;//grandparent of v
    //cout<<"splay: "<<endl;

    while((p=v->parent) && (g = p->parent)){//unil NULL node
        BinNodePosi(T) gg = g->parent;
        if(IsLChild(*v)){
            if(IsLChild(*p)){//zig-zig
                cout<<"zig-zig"<<endl;
                attachAsLChild(g,p->rChild);
                attachAsLChild(p,v->rChild);
                attachAsRChild(p,g);
                attachAsRChild(v,p);
            }else{//zig-zag
                cout<<"zig-zag"<<endl;
                attachAsLChild(p,v->rChild);
                attachAsRChild(g,v->lChild);
                attachAsLChild(v,g);
                attachAsRChild(v,p);
            }
        }else{
            if(IsRChild(*p)){//zag-zag
                cout<<"zag-zag"<<endl;
                attachAsRChild(g,p->lChild);
                attachAsRChild(p,v->lChild);
                attachAsLChild(p,g);
                attachAsLChild(v,p);
            }else{//zag-zig
                cout<<"zag-zig"<<endl;
                attachAsRChild(p,v->lChild);
                attachAsLChild(g,v->rChild);
                attachAsRChild(v,g);
                attachAsLChild(v,p);
            }
        }

        if(!gg) v->parent=NULL;// v is new root
        else{
            (g == gg->lChild)?attachAsLChild(gg,v):attachAsRChild(gg,v);
        }
        this->updateHeight(g);
        this->updateHeight(p);
        this->updateHeight(v);
    }
    
    p=v->parent;
    if(p){//if v is not root then need another zig/zag
        if(IsLChild(*v)){
            attachAsLChild(p,v->rChild);
            attachAsRChild(v,p);
        }else{
            attachAsRChild(p,v->lChild);
            attachAsLChild(v,p);
        }
        this->updateHeight(p);
        this->updateHeight(v);
    }

    //return new root
    v->parent =NULL;
    return v;
}


//search e
template <typename T>
BinNodePosi(T) & Splay<T>::search(const T& e){

    BinNodePosi(T) p=this->searchIn(this->_root,e,this->_hot=NULL);
    this->_root = splay((p?p:this->_hot));//update new root

    return this->_root;
}

//insert with e
template <typename T>
BinNodePosi(T) Splay<T>::insert(const T& e){
    //empty tree; insert as root
    if(!this->_root){this->_size++; return this->_root = new BinNode<T>(e);}

    if(e == search(e)->data) return this->_root;

    this->_size++;
    BinNodePosi(T) t=this->_root;

    if(this->_root->data < e){//insert new root 
        t->parent = this->_root = new BinNode<T>(e,NULL,t,t->rChild);
        if(HasRChild(*t)){
            t->rChild->parent = this->_root;
            t->rChild = NULL;
        } 
    }else{//as t's left
        t->parent = this->_root = new BinNode<T>(e,NULL,t->lChild,t);
        if(HasLChild(*t)){
            t->lChild->parent = this->_root;
            t->lChild = NULL;
        }
    }

    this->updateHeightAbove(t);

    return this->_root;

}


//remove e 
template <typename T>
bool Splay<T>::remove(const T& e){
    if(!this->_root || (e!= search(e)->data)) return false;

    BinNodePosi(T) w = this->_root;

    if(!HasLChild(*(this->_root))){//root only has right subtree then delete left tree directly
        this->_root = this->_root->rChild;
        if(this->_root) this->_root->parent = NULL;//set as root node
    }else if(!HasRChild(*(this->_root))){
        this->_root = this->_root->lChild;
        if(this->_root) this->_root->parent = NULL;//set as root node
    }else{ //both subtrees exist
        BinNodePosi(T) lTree = this->_root->lChild;
        //split left subtree
        lTree->parent =NULL;
        this->_root->lChild = NULL;
        //preserve right subtree
        this->_root = this->_root->rChild;
        this->_root->parent = NULL;
        search(w->data);
        //attach to new root
        this->_root->lChild = lTree;
        lTree->parent = this->_root;
    }

    release(w);
    this->_size--;
    if(this->_root) this->updateHeight(this->_root);

    return true;

}