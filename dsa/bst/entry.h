
template <typename K,typename V>
struct Entry{
    K key;
    V value;

    //Construct function
    Entry(K k=K(),V v=V()):key(k),value(v){};
    Entry(Entry<K,V> const &e):key(e.key),value(e.value){};

    //Comparators
    bool operator<(Entry<K,V> const& e){return key<e.key;}
    bool operator>(Entry<K,V> const& e){return key>e.key;}
    bool operator==(Entry<K,V> const& e){return key==e.key;}
    bool operator!=(Entry<K,V> const& e){return key!=e.key;}
};