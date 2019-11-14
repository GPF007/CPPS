#include "../bst/BST.h"


#define IsBlack(p) (!(p) || (RB_BLACK == (p)->color))
#define IsRed(p) (!IsBlack(p))
//whether x need to update height
#define BlackHeightUpdated(x)(\
        (starture((x).lChild) == starture((x).rChild)) && \
        ((x).height == (IsRed(&x)?starture((x).lChild):starture((x).lChild)+1))\
        )



template <typename T>
class RedBlack : public BST<T>{
protected:
    void solveDoubleRed(BinNodePosi(T) x);//solve double red case
    void solveDoubleBlack(BinNodePosi(T) x);//solve double black case
    int updateHeight(BinNodePosi(T) x);

public:
    BinNodePosi(T) insert(const T& e);
    bool remove(const T& e);
};


//update the black height of x
template <typename T>
int RedBlack<T>::updateHeight(BinNodePosi(T) x){
    x->height = max(starture(x->lChild),starture(x->rChild));
    return IsBlack(x)?x->height++:x->height;
}

//insert e
template <typename T>
BinNodePosi(T) RedBlack<T>::insert(const T& e){
    BinNodePosi(T) & x = this->search(e);
    if (x) return x;
    x=new BinNode<T>(e,this->_hot,NULL,NULL,-1);
    this->_size++;
    //cout<<"size:"<<this->_size<<endl;
    if(this->_size==1){
        this->_root->color=RB_BLACK;
        this->_root->height=0;
        return x;
    }
    if(IsRed(x) && IsRed(x->parent))
        solveDoubleRed(x);

    return x;
}



template <typename T>
void RedBlack<T>::solveDoubleRed(BinNodePosi(T) x){
    if(IsRoot(*x)){//until root
        this->_root->color=RB_BLACK;
        this->_root->height++;
        return;
    } 
    if(!(IsRed(x) && IsRed(x->parent))) return;

   // cout<<"x is not root"<<endl;

    BinNodePosi(T) p = x->parent;
    BinNodePosi(T) g = p->parent;
    BinNodePosi(T) u = uncle(x);

    if(IsBlack(u)){//uncle is black, RR-1
        if(IsLChild(*x) == IsLChild(*p))//x and p are the same side
            p->color=RB_BLACK;
        else
            x->color=RB_BLACK;
        g->color=RB_RED;

        //rotate
        BinNodePosi(T) gg=g->parent;
        BinNodePosi(T) &tmp =FromParentTo(*g);
        //BinNodePosi(T) r=FromParentTo(*g)=this->rotateAt(x);
        BinNodePosi(T) r=this->rotateAt(x);
        tmp=r;
        if(!gg)
            this->_root = r;
        /*
        cout<<"r:"<<r->data<<endl;
        cout<<"r->left"<<r->lChild->data<<endl;
        cout<<"r->left->color: "<<r->lChild->color<<endl;
        cout<<"r->right"<<r->rChild->data<<endl;
        cout<<"r->left->color: "<<r->lChild->color<<endl;
        r->parent=gg;
        */
    }else{//uncle is red ,RR-2
        p->color=RB_BLACK;p->height++;
        u->color=RB_BLACK;u->height++;
        if(!IsRoot(*g)) g->color=RB_RED;
        solveDoubleRed(g);

    }

}


template <typename T>
bool RedBlack<T>::remove(const T& e){
    BinNodePosi(T) & x = this->search(e);
    if(!x) return false;

    BinNodePosi(T) r = this->removeAt(x,this->_hot);
    if(0>= --this->_size) return true;

    if(!this->_hot){//parent is NULL ,remove the root
        this->_root->color = RB_BLACK;
        updateHeight(this->_root);
        return true;
    }

    if(BlackHeightUpdated(*(this->_hot)))
        return true;
    if(IsRed(r)){
        r->color=RB_BLACK;
        r->height++;
        return true;
    }
    //x and r are black
    solveDoubleBlack(r);
    return true;
}

template <typename T>
void RedBlack<T>::solveDoubleBlack(BinNodePosi(T) r){
    
    BinNodePosi(T) p = r?r->parent:this->_hot;
    if(!p) return;
    //s is r's brother
    BinNodePosi(T) s = (r==p->lChild)?p->rChild:p->lChild;

    if(IsBlack(s)){
        BinNodePosi(T) t =NULL;
        if(HasLChild(*s) && IsRed(s->lChild)) t=s->lChild;
        else if(HasRChild(*s) && IsRed(s->rChild)) t=s->rChild;
        if(t){//BB-1
            RBColor oldColor = p->color;
            BinNodePosi(T) & tmp=FromParentTo(*p);
            BinNodePosi(T) b = this->rotateAt(t);
            tmp=b;
            if(HasLChild(*b)) b->lChild->color = RB_BLACK;
            updateHeight(b->lChild);
            if(HasRChild(*b)) b->rChild->color = RB_BLACK;
            updateHeight(b->rChild);
            b->color = oldColor;
            updateHeight(b);
        }else{
            s->color=RB_RED;
            s->height--;
            if(IsRed(p)){
                p->color=RB_BLACK;
            }else{
                p->height--;
                solveDoubleBlack(p);
            }
        }
    }else{
        s->color=RB_BLACK;
        p->color=RB_RED;
        BinNodePosi(T) t = IsLChild(*s)?s->lChild:s->rChild;
        this->_hot = p;
        FromParentTo(*p) = this->rotateAt(t);
        solveDoubleBlack(r);

    }
}