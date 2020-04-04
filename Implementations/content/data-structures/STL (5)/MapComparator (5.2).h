/**
 * Description: example of function object (functor) for map or set
 * Source: StackOverflow
 * Usage: set<int,cmp> s; map<int,int,cmp> m;
 */

struct cmp{bool operator()(int l,int r)const{return l>r;}};