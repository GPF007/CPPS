#include <iostream>
#include "../stack.h"
#include <string>
#include <cctype>
#include <cstdio>
#include <map>
#include <cmath>

using namespace std;



typedef enum {ADD=0,SUB=0,MUL=1,DIV=1,POW=2,L_P=3,R_P=3,EOE=0} Operator;


map<char,int> ops{
    {'+',0},
    {'-',0},
    {'*',1},
    {'/',1},
    {'^',2},
    {'(',3},
    {')',3},
    {'\0',-1}
};


/*
    evaluate string *S and output the 'reverse polish notation' to *RPN;
    use 2 stacks 
*/

void readNumber(const char* &S,float &num);


float calcu(float f1,char op,float f2){
    
    switch (op)
    {
    case '+': return f1 + f2;
    case '-': return f1 - f2;
    case '*': return f1 * f2;
    case '/': return f1 / f2;
    case '^': return pow(double(f1),double(f2));
    }

    return 0;
}

float evaluate(const char *S,string &RPN){

    Stack<float> opnd;//stack of numbers
    Stack<char> optr; //stack of operators

    optr.push('\0');

    float num;

    while(!optr.empty()){//stack of operators must not be empty
        if(isdigit(*S)){
            readNumber(S,num);
            opnd.push(num);
            //cout<<"number is: "<<num<<endl;
            RPN+=to_string(num);

        }else{
            const char top_optr=optr.top();
            if((ops[top_optr] < ops[*S] || top_optr=='(') && *S!=')'){
                optr.push(*S);
                S++;
            }else if(ops[top_optr] >= ops[*S] || *S==')'){ //top_optr >= *s

                char op=optr.pop();
                RPN+=op;
                float opnd2=opnd.pop();
                float opnd1=opnd.pop();
                float res=calcu(opnd1,op,opnd2);
                //printf("%f %c %f = %f\n",opnd1,op,opnd2,res);
                opnd.push(res);
                if(*S==')'){
                    optr.pop();
                    S++;
                }
                
            }
            
            if(*S=='\0' && optr.size()==1){
                optr.pop();
            }
        }
    }
    return opnd.pop();
}














/*
    read a float number from *S
*/

void readNumber(const char* &S,float &num){
    num=0;
    bool point=false;
    int power=1;
    while(*S!='\0'){
        if(!isdigit(*S) && *S!='.'){
            num/=power;
          //  cout<<"ss:"<<*S<<endl;
            return;
        }
        else if(*S == '.'){
            if(point == false){//only one '.'
                point=true;
                S++;
            }else{
                num=0;
                return;
            }
        }else if(isdigit(*S)){
            num=num*10+ (*S-'0');
            if(point)
                power*=10;
            S++;
        }
    }
}

void test(const char* &s){
    while(*s!='\0'){
        cout<<s<<endl;
        s++;
    }
}



int main(int argc, char const *argv[])
{
    
    float f;
    const char *s="(1+2)*(3+4)";
    string ss;
    float res=evaluate(s,ss);
    cout<<res<<endl; 
    cout<<ss<<endl;

    float f1=123.45;
    float f2=456;
  //printf("%f + %f = %f\n",f1,f2,f1+f2);


    return 0;
}
