/**
* Description: Custom comparator for map / set
* Source: StackOverflow
* Verification: ?
*/

struct cmp {
    bool operator()(const int& l, const int& r) const {
        return l > r;
    }
};

set<int,cmp> s;
map<int,int,cmp> m;