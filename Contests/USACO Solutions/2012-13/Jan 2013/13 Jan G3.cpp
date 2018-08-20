// #include<iostream>
#include<fstream>
#include<set>
#include<map>
#include<unordered_map>
#include<cmath>
#include<cstring>
#include<string>
#include<bitset>
#include<algorithm>
#include<vector>

using namespace std;
//using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

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

int N,M,ans=0;
set<pi> stor[1<<20];

void modify(pi val, bool x) {
	for (int p = val.s-val.f+(1<<19);p > 0; p >>= 1) {
		if (x) stor[p].insert(val);
		else stor[p].erase(val);
	}
}

pi query(int l, int r) {
	pi ans = {MOD,MOD};
  	for (l += (1<<19), r += (1<<19); l < r; l >>= 1, r >>= 1) {
	    if (l&1) {
	    	if (stor[l].size()) ans = min(ans,*stor[l].begin());
	    	l++;
	    }
	    if (r&1) {
	    	r--;
	    	if (stor[r].size()) ans = min(ans,*stor[r].begin());
	    }
  	}
  	return ans;
}

int main() {
    ifstream cin ("seating.in");
    ofstream cout ("seating.out");
	cin >> N >> M;
	modify({1,N},1);
	F0R(i,M) {
		char t; cin >> t;
		if (t == 'A') {
			int p; cin >> p;
			pi q = query(p-1,N);
			if (q.f == MOD) {
				ans++;
				continue;
			}
			modify(q,0);
			if (q.f+p <= q.s) modify({q.f+p,q.s},1); // correct
		} else {
			int a,b; cin >> a >> b; 
			vector<pi> todo;
			auto it = stor[1].lb({a,0}); // first coordinate at least a
			if (it != stor[1].begin() && (*prev(it)).s >= a-1)  it = prev(it);
			while (it != stor[1].end() && (*it).f <= b+1) {
				a = min(a,(*it).f);
				b = max(b,(*it).s);
				todo.pb(*it);
				it = next(it);
			}
			for (auto p: todo) modify(p,0);
			modify({a,b},1);
		}
	}
	cout << ans;
}
