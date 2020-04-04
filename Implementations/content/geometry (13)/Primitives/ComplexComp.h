/**
 * Description: Allows you to sort complex numbers.
 * Source: http://codeforces.com/blog/entry/22175, KACTL
 	* https://codeforces.com/blog/entry/22175#comment-582178
 * Verification: various
 */

#define x real()
#define y imag()
typedef complex<db> P;
namespace std { 
	bool operator<(P l,P r) { return mp(l.x,l.y)<mp(r.x,r.y); } }
/// vector<P> v = {{4,5},{3,6},{5,7}}; sort(all(v)); ps(v);