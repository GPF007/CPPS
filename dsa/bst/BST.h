#include "../bintree/bintree.h"

template <typename T>
class BST:public BinTree<T> {
public:



    //virtual means subclass could override these methods
    virtual BinNodePosi(T) & search(const T& e);//searh e
    virtual BinNodePosi(T) insert(const T& e);//insert e
    virtual bool remove(const T& e);

    
    //static functions
    static BinNodePosi(T) & searchIn(BinNodePosi(T)& v,const T& e,BinNodePosi(T)& hot);
    static BinNodePosi(T) removeAt(BinNodePosi(T)& x,BinNodePosi(T)& hot);

protected:
    BinNodePosi(T) _hot;//search result's parent
    BinNodePosi(T) connect34(//reconstruct by 3 and 4
        BinNodePosi(T),BinNodePosi(T),BinNodePosi(T),
        BinNodePosi(T),BinNodePosi(T),BinNodePosi(T),BinNodePosi(T));
    BinNodePosi(T) rotateAt(BinNodePosi(T) v);
};

/* recrusion searchIn
    hot is parent node
    return ref of result node
*/
template <typename T>
BinNodePosi(T) & BST<T>::searchIn(BinNodePosi(T)& v,const T& e,BinNodePosi(T)& hot){
    if(!v || (e==v->data)) return v;
    hot = v;
    return searchIn(((e < v->data)?v->lChild:v->rChild),e,hot);
}
//searh the value
template <typename T>
BinNodePosi(T) & BST<T>::search(const T& e){
    return searchIn(this->_root,e,_hot=NULL);
}

//insert a node
template <typename T>
BinNodePosi(T) BST<T>::insert(const T& e){
    BinNodePosi(T) & x=search(e);
    if(x) return x;//x must not exist
    x=new BinNode<T>(e,_hot);
    this->_size++;
    this->updateHeightAbove(x);

    return x;
}

//remove a node
template <typename T>
bool BST<T>::remove(const T& e){
    BinNodePosi(T) & x = search(e);
    if(!x) return false; //x is not exist then return true
    removeAt(x,_hot);
    this->_size--;
    this->updateHeightAbove(_hot);

    return true;
}

template<typename T>
BinNodePosi(T) BST<T>::removeAt(BinNodePosi(T)& x,BinNodePosi(T)& hot){
    BinNodePosi(T) w = x;//w is the target node
    BinNodePosi(T) succ = NULL; //the target's succeed node(left most)
    //x only has one child
    if(!HasLChild(*x)) succ = x = x->rChild;
    else if(!HasRChild(*x)) succ = x = x->lChild;
    else{//x has two children
        w = w->succ();//left most child
        swap(x->data,w->data);
        BinNodePosi(T) u=w->parent;
        ((u==x)?u->rChild:u->lChild) = succ =w->rChild;
    }

    hot=w->parent;
    if(succ) succ->parent=hot;
    release(w);

    return succ;
}


//rebuild tree with 3 nodes, 4 subtrees
template <typename T>
BinNodePosi(T) BST<T>::connect34(//reconstruct by 3 and 4
        BinNodePosi(T) a,BinNodePosi(T) b,BinNodePosi(T) c,
        BinNodePosi(T) T0,BinNodePosi(T) T1,BinNodePosi(T) T2,BinNodePosi(T) T3)
{

    a->lChild = T0; if(T0) T0->parent = a;
    a->rChild = T1; if(T1) T1->parent = a; this->updateHeight(a);
    c->lChild = T2; if(T2) T2->parent = c;
    c->rChild = T3; if(T3) T3->parent = c; this->updateHeight(c);
    b->lChild = a; a->parent = b;
    b->rChild = c; c->parent = b; this->updateHeight(b);

    return b;

}

//rotate at v
template <typename T>
BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v){
    BinNodePosi(T) p = v->parent;
    BinNodePosi(T) g = p->parent;

    if(IsLChild(*p)){//zig
        if(IsLChild(*v)){//zig
            p->parent = g->parent;
            return connect34(v,p,g,v->lChild,v->rChild,p->rChild,g->rChild);
        }else{//zag
            v->parent = g->parent;
            return connect34(p,v,g,p->lChild,v->lChild,v->rChild,g->rChild);
        }
    }else{//zag
        if(IsRChild(*v)){//zag
            p->parent = g->parent;
            return connect34(g,p,v,g->lChild,p->lChild,v->lChild,v->rChild);
        }else{//zig
            v->parent = g->parent;
            return connect34(g,v,p,g->lChild,v->lChild,v->rChild,p->rChild);
        }
    }

    return NULL;
}