
#include <queue>
#include <stack>
#include <cstdlib>
#include <iostream>
using namespace std;

#define BinNodePosi(T) BinNode<T>* //pointer of node
#define starture(p) ((p)?(p)->height:-1)
typedef enum{RB_RED,RB_BLACK} RBColor;

//some judgement functions of binnode (x is a binnode)
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lChild))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rChild))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lChild)
#define HasRChild(x) ((x).rChild)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))

//get the relation node of x(x is a pointer)
//get the sibling o
#define sibling(p)( \
    IsLChild(*(p)) ?\
    (p)->parent->rChild:\
    (p)->parent->lChild\
    )

#define uncle(x) ( \
    IsRoot(*((x)->parent))?NULL:\
    (IsLChild(*((x)->parent))?\
    (x)->parent->parent->rChild:\
    (x)->parent->parent->lChild\
    ))

//get the pointer from parent
#define FromParentTo(x) (\
        IsRoot(x)?(this)->_root:(\
        IsLChild(x)?(x).parent->lChild : (x).parent->rChild)\
        )

//struct of BinNode
template <typename T>
struct BinNode{
    //data
    T data;
    BinNodePosi(T) parent;
    BinNodePosi(T) lChild;
    BinNodePosi(T) rChild;
    int height;//the height of this subtree
    int npl;
    RBColor color;

    //Construct functions
    BinNode():parent(NULL),lChild(NULL),rChild(NULL),height(0),npl(1),color(RB_RED){}
    BinNode(T e,BinNodePosi(T) p=NULL,BinNodePosi(T) lc=NULL,BinNodePosi(T) rc=NULL,
            int h=0,int l=1,RBColor c=RB_RED)
        :data(e),parent(p),lChild(lc),rChild(rc),height(h),npl(l),color(c){}
    
    //functions
    int size();
    BinNodePosi(T) insertAsLC(T const&);//insert as left child
    BinNodePosi(T) insertAsRC(T const&);
    BinNodePosi(T) succ();//get the succeed node
    template <typename VST> void travLevel(VST&);//travese by level
    template <typename VST> void travPre(VST&);
    template <typename VST> void travIn(VST&);
    template <typename VST> void travPost(VST&);

    //comparators: < and ==
    bool operator<(BinNode const& bn){return data < bn.data;}
    bool operator==(BinNode const& bn){return data == bn.data;}



    
};

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const& e){
    return lChild = new BinNode(e,this);
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const& e){
    return rChild = new BinNode(e,this);
}

//get next inorder travase node
template <typename T>
BinNodePosi(T) BinNode<T>::succ(){
    BinNodePosi(T) x=this;

    if(rChild){//in it's right subtree
        x=rChild;
        while(HasLChild(*x)) x=x->lChild;
    }else{//backtrack to it ancestor
        while(IsRChild(*x)) x=x->parent;
        x=x->parent;
    }

    return x;

}

//travel by level
template <typename T> template<typename VST> 
void BinNode<T>::travLevel(VST& visit){
    travLevel_I(this,visit);
}
//travel by preorder 
template <typename T> template<typename VST> 
void BinNode<T>::travPre(VST& visit){
    switch(rand()%2){
        case 1:travPre_R(this,visit);break;
        default:travPre_I(this,visit);break;
    }
}
//travel by inorder 
template <typename T> template<typename VST> 
void BinNode<T>::travIn(VST& visit){
    switch(rand()%2){
        case 1:travIn_R(this,visit);break;
        default:travIn_I(this,visit);break;
    }
}
//travel by postorder 
template <typename T> template<typename VST> 
void BinNode<T>::travPost(VST& visit){
    switch(rand()%2){
        case 1:travPost_R(this,visit);break;
        default:travPost_I(this,visit);break;
    }
}







/* Traverse functions
    Out of class
*/
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
    int h=0;

    while(!q.empty()){
        int n=q.size();
        cout<<"Level "<<h<<": ";
        while(n--){
            x=q.front();
            q.pop();
            visit(x->data);

            if(x->lChild) q.push(x->lChild);
            if(x->rChild) q.push(x->rChild);
        }
        cout<<endl;
        ++h;
    }

    
}



//release function
template<typename T>
void release(T *t){
    delete t;
}