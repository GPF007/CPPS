#include <iostream>
#include <unordered_map>
#include <string>
#include <list>
#include <utility>
#include <cstddef>
#include <algorithm>
namespace cache{

template <typename K,typename V>
class Cache{
public:
    typedef typename std::pair<K,V> pair_t;
    typedef typename std::list<pair_t>::iterator list_iterator_t;

    Cache(size_t maxx):max_size(maxx)
    {}
    ~Cache(){}

    /*insert an item*/
    void Put(const K,const V);
    V& Get(const K& key);

    /*get size*/
    size_t Get_max_size(){return max_size;}
    std::string Get_hi();


private:
    std::unordered_map<K,list_iterator_t> mp;
    std::list<pair_t> items_list;
    size_t max_size;

};

};