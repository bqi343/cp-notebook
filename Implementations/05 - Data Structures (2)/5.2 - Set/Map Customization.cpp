/**
* Source: StackOverflow
* Description: Define your own comparator / hash function
*/

struct cmp {
    bool operator()(const int& l, const int& r) const {
        return l > r;
    }
};

struct hsh {
    size_t operator()(const pi& k) const {
        return k.f^k.s; // bad, but you get the point
    }
};

set<int,cmp> s;
map<int,int,cmp> m;
unordered_map<pi,int,hsh> u;
