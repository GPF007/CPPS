#include "binnode.h"

using namespace std;

template <typename T>
class BinTree{
protected:
    int _size;
    BinNodePosi(T) _root;//root of tree
    virtual int updateHeight(BinNodePosi(T) x);//update height of x;(vitural function can be override)
    void updateHeightAbove(BinNodePosi(T) x);//update height of x and x's ancestor


public:
    //Construct/Destruct function
    BinTree():_size(0),_root(NULL){}
    ~BinTree() {if (_size>0) remove(_root);}

    //public interface
    int size() const{return _size;}
    bool empty() const {return !_root;}
    BinNodePosi(T) root() const {return _root;}
    BinNodePosi(T) insertAsRoot(T const& e);
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x,T const& e);//insert e as x's left child
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x,T const& e);
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x,BinTree<T>* &t);//insert subtree T to x's left child
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x,BinTree<T>* &t);
    int remove(BinNodePosi(T) x);//delete subtree x;return x's size
    static int removeAt(BinNodePosi(T) x);
    BinTree<T>* secede(BinNodePosi(T) x);

    //traverse functions
    template <typename VST>
    void travLevel(VST& visit){if (_root) _root->travLevel(visit);}//by level
    template <typename VST>//preorder
    void travPre(VST& visit){if (_root) _root->travPre(visit);}
    template <typename VST>//inorder
    void travIn(VST& visit){if (_root) _root->travIn(visit);}
    template <typename VST>//post order
    void travPost(VST& visit){if (_root) _root->travPost(visit);}

    //comparators
    bool operator<(BinTree<T> const& t) {return _root && t._root && (_root<t._root);}
    bool operator==(BinTree<T> const& t) {return _root && t._root && (_root==t._root);}
};


//update height
template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x){
    return x->height=1+max(starture(x->lChild),starture(x->rChild));
}

template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x){
    while(x){
        updateHeight(x);
        x=x->parent;
    }
    /*could be optimized*/
}

//insert nodes
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e){
    _size=1;
    return _root=new BinNode<T>(e);
}
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x,T const& e){
    _size++;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lChild;
}
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x,T const& e){
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rChild;
}

//insert subtrees
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x,BinTree<T>* &S){
    x->lChild=S->_root;
    if(x->lChild) x->lChild->parent=x;//new subtree is not null

    _size+=S->_size();
    updateHeightAbove(x);
    //clear S to empty
    S->_root = NULL;
    S->_size=0;
    release(S);
    S=NULL;

    return x;
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x,BinTree<T>* &S){
    x->rChild=S->_root;
    if(x->rChild) x->rChild->parent=x;//new subtree is not null

    _size+=S->_size();
    updateHeightAbove(x);
    //clear S to empty
    S->_root = NULL;
    S->_size=0;
    release(S);
    S=NULL;

    return x;

}

//remove x and x' children
template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x){
    FromParentTo(*x) = NULL;//seprate from parent
    updateHeightAbove(x->parent);

    int n=removeAt(x);
    _size-=n;
    return n;
}
//help function: remove at x
template <typename T>
int BinTree<T>::removeAt(BinNodePosi(T) x){
    if(!x) return 0;
    int n = 1 + removeAt(x->lChild) + removeAt(x->rChild);
    //release(x->data);
    release(x);
    return n;
}

//seperate subtree and return to caller
template <typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x){
    FromParentTo(*x) = NULL;
    updateHeightAbove(x->parent);

    BinTree<T>* S=new BinTree<T>;
    S->_root=x;
    x->parent=NULL;
    S->_size=x->size();
    _size-=S->_size;

    return S;
}











/* Traverse functions
    Out of class

//recrusion version
//preorder traverse
template<typename T,typename VST>
void travPre_R(BinNodePosi(T) x,VST& visit){
    if(!x) return;
    visit(x->data);
    travPre_R(x->lChild,visit);
    travPre_R(x->rChild,visit);
}
//inorder traverse
template<typename T,typename VST>
void travIn_R(BinNodePosi(T) x,VST& visit){
    if(!x) return;
    travIn_R(x->lChild,visit);
    visit(x->data);
    travIn_R(x->rChild,visit);
}
//pstorder traverse
template<typename T,typename VST>
void travPost_R(BinNodePosi(T) x,VST& visit){
    if(!x) return;
    travPost_R(x->lChild,visit);
    travPost_R(x->rChild,visit);
    visit(x->data);
}


//iteration version
template<typename T,typename VST>
void travPre_I(BinNodePosi(T) x,VST& visit){
    stack<BinNodePosi(T)> st;

    while(x || !st.empty()){
        if(x==NULL){
            x=st.top();
            st.pop();
        }

        visit(x->data);
        if(x->rChild) st.push(x->rChild);
        x=x->lChild;
    }
}
//Inorder
template<typename T,typename VST>
void travIn_I(BinNodePosi(T) x,VST& visit){
    
    stack<BinNodePosi(T)> st;
    //BinNodePosi(T) cur;
    while(x || !st.empty()){
        while(x!=NULL){
            st.push(x);
            x=x->lChild;
        }

        x=st.top();
        st.pop();
        visit(x->data);
        x=x->rChild;
        
    }  
}
//Postorder
template<typename T,typename VST>
void travPost_I(BinNodePosi(T) x,VST& visit){
    
    stack<BinNodePosi(T)> st;
    BinNodePosi(T) cur=x;//current node
    BinNodePosi(T) prev=NULL; //last visited node
    
    while(cur){
        st.push(cur);
        cur=cur->lChild;
    }

    while(!st.empty()){
        cur=st.top();
        st.pop();
        if(!cur->rChild || prev == cur->rChild){
            visit(cur->data);
            prev=cur;
        }else{
            st.push(cur);
            cur=cur->rChild;
            while(cur){
                st.push(cur);
                cur=cur->lChild;
            }
        }
    }    
}

//trave by level
template <typename T,typename VST>
void travLevel_I(BinNodePosi(T) x,VST& visit){
    queue<BinNodePosi(T)> q;
    q.push(x);

    while(!q.empty()){
        int n=q.size();
        while(n--){
            x=q.front();
            q.pop();
            visit(x->data);

            if(x->lChild) q.push(x->lChild);
            if(x->rChild) q.push(x->rChild);
        }
    }

    
}


*/