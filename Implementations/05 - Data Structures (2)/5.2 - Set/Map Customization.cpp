/**
* Source: StackOverflow
* Description: Define your own comparator / hash function
*/

// map

struct cmp {
    bool operator()(const int& l, const int& r) const {
        return l > r;
    }
};

set<int,cmp> s;
map<int,int,cmp> m;

// unordered map

int tmp = chrono::high_resolution_clock::now().time_since_epoch().count();

template<class T> struct hsh {
    size_t operator()(const T& x) const {
        return hash<T>{}(x)^tmp;
    }
};

template<class a, class b> using um = unordered_map<a,b,hsh<a>>;

um<int,int> u;
