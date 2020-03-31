
#include <memory>

using std::allocator;
using std::pair;

class String{
public:
    String():String(""){}
    String(const char *);
    String(const String&);
    String(const String&&);
    String& operator=(const String&);
    ~String();

    const char* c_str() const {return elements;}
    size_t size() const {return end - elements;}
    size_t length() const {return end - elements -1;}

    char& operator[](int i);
    const char& operator[](int i) const;
    

private:
    pair<char*,char*> alloc_n_copy(const char*,const char*);
    void range_initializer(const char*, const char*);
    void free();



private:
    char *elements;
    char *end;

    allocator<char> alloc;


};