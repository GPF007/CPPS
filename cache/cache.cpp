#include "cache.h"

namespace cache{
/*Put the value in cache*/
template <typename K,typename V>
void Cache<K,V>::Put(const K key,const V val){
    auto it=mp.find(key);
    items_list.push_front(pair_t(key,val));

    //redistribute the point
    if(it!=mp.end()){
        items_list.erase(it->second);
        mp.erase(it);
    }

    mp[key]=items_list.begin();

    //delete the last item of list
    if(mp.size() > max_size){
        auto last=items_list.end();
        --last;
        mp.erase(it->first);
        items_list.pop_back();
    }
}


/*Get the value in cache */
template <typename K,typename V>
V& Cache<K,V>::Get(const K& key){
    auto it=mp.find(key);
    if(it == mp.end()){
        /*not found*/
        throw std::range_error("There is no such key in cache");
    }else{
        items_list.splice(items_list.begin(),items_list,it->second);
        return it->second->second;
    }

}
template <typename K,typename V>
std::string Cache<K,V>::Get_hi()
{return "Hello!";}

template class Cache<std::string,int>;
};
