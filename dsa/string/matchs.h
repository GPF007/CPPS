
#include <cstring>
#include <cstddef>

#define MAX(a,b) ((a)<(b)?(b):(a))


/*Brute match
  P is pattern,length is m
  T is text,length is n
  Time complexity is O(m*n)
  return the matched position of T
  if i-j == n then false

*/
int brute_match(const char* P,const char* T){
    size_t n = strlen(T),i=0;
    size_t m = strlen(P),j=0;

    while(j<m && i < n){
        if(T[i] == P[j]){
            i++;
            j++;
        }else{
            i-=j-1;
            j=0;
        }
    }

    return i-j;
}


int* buildNext(const char* P){
    size_t m = strlen(P),j=0;
    int* N = new int[m];
    int t=N[0]=-1;
    while(j < m-1){
        if(t<0 || P[j]==P[t]){
            j++;t++;
            N[j]=(P[j]!=P[t]?t:N[t]);
        }else
            t=N[t];
    }

    return N;
}

/* KMP match
   Time complexity is O(n)+ O(m)
*/
int kmp_match(const char* P,const char* T){
    int* next=buildNext(P);
    int n = (int) strlen(T),i=0;
    int m = (int) strlen(T),j=0;

    while(j<m && i<n){
        if(j<0 || T[i]==P[j]){
            i++;
            j++;
        }else
            j=next[j];
    }

    delete [] next;
    return i-j;
    
}




/* BM match 
int match_bm(char* P,char* T){
    int *bc = buildBC(P);
    int *gs = buildGS(P);

    size_t i = 0;
    int n =(int) strlen(T);
    while(n >= i + strlen(P)){
        int j =strlen(P) - 1;
        while(P[j] == T[i+j])
            if(0 > --j) break;
        if(0> j)
            break;
        else
            i+= MAX(gs[j],j-bc[T[i+j]]);
    }
    delete [] gs;
    delete [] bc;
}

int* buildBC(char* P){
    int* bc = new int[256];
    for(size_t j=0;j<256;j++)
        bc[j]=-1;
    for(size_t m = strlen(P),j=0;j<m;j++){
        bc[P[j]]=j;
    }

    return bc;
}

int* buildSS(char* P){
    int m = strlen(P);
    int* ss = new int[m];

    ss[m-1]=m;
    for(int lo = m-1,hi=m-1,j=lo-1;j>=0;j--){
        if((lo<j) && (ss[m-hi+j-1] <= j - lo))
            ss[j]=ss[m-hi+j-1];
        else{
            hi = j;
            lo = (lo<hi)?lo:hi;
            while((0<=lo) && (P[lo] == P[m-hi+lo-1]))
                lo--;
            ss[j]= hi -lo;
        }
    }
}


int* buildBC(char* P){
    int* ss=buildSS(P);
    size_t m = strlen(P);
    int *gs =new int[m];

    for(size_t j=0;j<m;j++) gs[j]=m;
    for(size_t i=0,j=m-1;)
}

*/