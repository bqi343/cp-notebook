/**
* Description: faster than standard unordered map
* Source: http://codeforces.com/blog/entry/60737
*/

const int tmp = chrono::high_resolution_clock::now().time_since_epoch().count();

template<class T> struct hsh {
    size_t operator()(const T& x) const { 
        return hash<T>{}(x)^tmp; // avoid anti-hash tests?
    }
};

template<class a, class b> using um = gp_hash_table<a,b,hsh<a>>;

um<int,int> u;