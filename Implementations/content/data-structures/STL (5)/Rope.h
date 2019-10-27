/**
 * Description: insert element at $n$-th position,
	* cut a substring and re-insert somewhere else
 * Time: O(\log N) per operation? not well tested
 * Source: https://codeforces.com/blog/entry/10355
 * Verification: CEOI 2018 Day 2 Triangles
 */

#include <ext/rope>

using namespace __gnu_cxx;

void ropeExample() {
	// CONSTRUCTION
	rope<int> v(5, 0); // initialize with 5 zeroes
	F0R(i,sz(v)) v.mutable_reference_at(i) = i+1; 
	// rope<int> v; F0R(i,5) v.pb(i+1);

	// CUTTING AND INSERTING
	rope<int> cur = v.substr(1,2); 
	v.erase(1,2); // erase 2 elements starting from 1st element
	v.insert(v.mutable_begin()+2,cur);

	// PRINTING
	for (rope<int>::iterator it = v.mutable_begin(); 
		it != v.mutable_end(); ++it)
		cout << *it << " "; // 1 4 2 3 5
	// F0R(i,sz(v)) cout << v[i] << " ";  // 1 4 5
}