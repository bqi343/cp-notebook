/**
 * Description: coordinate compression, get index of x by counting # of elements < x
 * Source: Own
 * Verification: ?
 */

template<class T> void nor(vector<T>& v) {
	sort(all(v)); v.erase(unique(all(v)),end(v)); }
template<class T> int ind(vector<T>& v, T x) { 
	return lb(all(v),x)-begin(v); }