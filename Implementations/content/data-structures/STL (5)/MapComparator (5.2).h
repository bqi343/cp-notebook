/**
 * Description: custom comparator for map / set
 * Source: StackOverflow
 * Usage: set<int,cmp> s; map<int,int,cmp> m;
 */

struct cmp {
	bool operator()(const int& l, const int& r) const { 
		return l > r; // sort items in decreasing order
	} 
};
