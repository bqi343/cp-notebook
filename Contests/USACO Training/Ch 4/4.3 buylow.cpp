/*
ID: bqi3431
PROG: buylow
LANG: C++11
*/

#include<iostream>
#include <fstream>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
const int MOD = 1000000007;
double PI = 4*atan(1);

int num[5001],N;
pair<ll,vi> best[5000];


vi add(vi A, vi B) {
	while (A.size()<B.size()) A.pb(0);
	while (B.size()<A.size()) B.pb(0);
   	int carry = 0;
	vi C(A.size());
	F0R(pos,A.size()) {
		C[pos] = A[pos]+B[pos]+carry;
	    carry = C[pos]/10;
	    C[pos] %= 10;
	}
	if (carry != 0) C.pb(carry);
	return C;
}

void print(vi x) {
	F0Rd(i,x.size()) cout << x[i];
}
int main() {
	//ifstream cin ("buylow.in");
	//ofstream cout ("buylow.out");
	cin >> N;
	F0R(i,N) cin >> num[i], best[i].f = 1;
	F0R(i,N+1) {
		F0R(j,i) if (num[j]>num[i]) best[i].f = max(best[i].f,best[j].f+1);
		if (best[i].f == 1) best[i].s = {1};
		else {
			set<int> z;
			F0Rd(j,i) if (best[i].f == best[j].f+1 && num[j]>num[i] && z.find(num[j]) == z.end()) {
				z.insert(num[j]);
				best[i].s = add(best[i].s,best[j].s);
			}
		}
		/*cout << i << " " << best[i].f << " " << num[i] << " ";
		print(best[i].s);
		cout << "\n";*/
	}
	cout << best[N].f-1 << " ";
	print(best[N].s);
	cout << "\n";
}
