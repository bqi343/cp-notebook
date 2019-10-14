/**
 * Description: custom comparator for map / set
 * Source: StackOverflow
 */

struct cmp {
	bool operator()(const int& l, const int& r) const {
		return l > r;
	}
};

set<int,cmp> s; // F0R(i,10) s.insert(rand()); trav(i,s) ps(i);
map<int,int,cmp> m;
