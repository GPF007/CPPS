
#include <queue>
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
    IsLChild(*((x)->parent))? \
    (p)->parent->parent->rChild:\
    (p)->parent->parent->lChild\
    )

//get the pointer from parent
#define FromParentTo(x) (\
        IsRoot(x)? _root:(\
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

template <typename T> template<typename VST> 
void BinNode<T>::travLevel(VST& visit){
    queue<BinNodePosi(T)> q;
    BinNodePosi(T) x=this;
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