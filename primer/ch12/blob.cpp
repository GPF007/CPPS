#include <vector>
#include <string>
#include <iostream>
#include <memory>

using namespace std;

class StrBlob{
public:
    typedef vector<string>::size_type size_type;
    StrBlob();
    StrBlob(initializer_list<string> il);
    size_type size() const {return data->size();}
    bool empty() const {return data->empty();}

    //add and delete
    void push_back(const string &t){data->push_back(t);}
    void pop_back();

    //access element
    string& front();
    string& back();

private:
    shared_ptr<vector<string>> data;

    void check(size_type i, const string &msg) const;

};


StrBlob::StrBlob(): data(make_shared<vector<string>>()) {}
StrBlob::StrBlob(initializer_list<string> il):
            data(make_shared<vector<string>>(il)){}

void StrBlob::check(size_type i, const string &msg) const
{
    if(i>=data->size())
        throw out_of_range(msg);
}

string& StrBlob::front()
{
    check(0,"front on empty StrBlob");
    return data->front();
}

string& StrBlob::back()
{
    check(0,"back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back()
{
    check(0,"back on empty StrBlob");
    data->pop_back();
}

int main(int argc, char const *argv[])
{
    StrBlob strblob={"as","ee"};
    return 0;
}
