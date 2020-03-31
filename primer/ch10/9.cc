#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

void print_vec(vector<string>& words){
    for(auto &w:words)
        cout<<w<<" ";
    cout<<endl;
}

int main(int argc, char const *argv[])
{
    vector<string> words{"hello", "world", "my","my","love"};

    cout<<"origin vector:"<<endl;
    print_vec(words);
    cout<<"after sort:"<<endl;
    sort(words.begin(),words.end());
    print_vec(words);
    
    cout<<"after unique:"<<endl;
    auto end_unique = unique(words.begin(),words.end());
    print_vec(words);
    cout<<"after erase:"<<endl;
    words.erase(end_unique,words.end());
    print_vec(words);

    return 0;
}
