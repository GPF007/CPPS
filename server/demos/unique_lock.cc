#include <iostream>
#include <thread>
#include <functional>
#include <chrono>
#include <atomic>
#include <cstdio>
#include <mutex>

using namespace std;


int counter;
mutex counter_mutex;
const int iters = 10000;

void f1(){
    for(int i=0;i<iters;i++){
        unique_lock<mutex> lock(counter_mutex);
        counter+=1;
        lock.unlock(); 
    }
}
void f2(){
    for(int i=0;i<iters;i++){
        unique_lock<mutex> lock(counter_mutex);
        counter+=1;
        //离开作用域后自动释放
    }
}
void f3(){
    for(int i=0;i<iters;i++){
        unique_lock<mutex> lock(counter_mutex);
        counter+=1;
        //离开作用域后自动释放
    }
}
int main(int argc, char const *argv[])
{
    thread ts[3];

    ts[0] = thread(f1);
    ts[1] = thread(f2);
    ts[2] = thread(f3);

    for(int i=0;i<3;i++)
        ts[i].join();
    printf("expected counter = %d but counter = %d\n", 3 * iters, counter);    
    
    
    return 0;
}
