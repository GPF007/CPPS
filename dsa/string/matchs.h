
#include <cstring>
#include <cstddef>


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