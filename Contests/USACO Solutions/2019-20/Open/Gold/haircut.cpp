#include "bits/stdc++.h"
 
using namespace std;
 
void setIO(string s) {
	ios_base::sync_with_stdio(0); cin.tie(0); 
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}
 
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T> using Tree = tree<T, null_type, less<T>, 
	rb_tree_tag, tree_order_statistics_node_update>; 
 
const int MX = 1e5+5;
 
int N;
long long numInv[MX];
vector<int> todo[MX];
 
int main() {
	setIO("haircut");
	int N; cin >> N;
	vector<int> A(N); for (int& t: A) cin >> t;
	for (int i = 0; i < N; ++i) todo[A[i]].push_back(i);
	Tree<int> T;
	for (int i = N; i >= 0; --i) {
		for (int t: todo[i]) numInv[i+1] += T.order_of_key(t);
		for (int t: todo[i]) T.insert(t);
	}
	for (int i = 1; i < N; ++i) numInv[i] += numInv[i-1];
	for (int i = 0; i < N; ++i) cout << numInv[i] << "\n";
}