#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()

const int MOD = 1000000007;

int N,D;
vector<vi> b[2];
ll ans[2][100000], fin[100000];
queue<pi> q;
set<int> todo[2];

pi binsearch(int giver, int ind) {
    // 0: Bessie gave, Elsie received
    int lo = b[giver][ind][1]-D, hi = b[giver][ind][1];
    vi v1 = {lo,0,0}, v2 = {hi+1,0,0};
    return {lb(all(b[giver^1]),v1)-b[giver^1].begin(),
            lb(all(b[giver^1]),v2)-b[giver^1].begin()-1};
}

void input() {
    freopen("piepie.in","r",stdin);
    freopen("piepie.out","w",stdout);
	cin >> N >> D; 
	b[0].resize(N), b[1].resize(N);
	
	F0R(i,N) {
	    b[0][i].resize(3);
	    cin >> b[0][i][1] >> b[0][i][0]; // pies which bessie gives
	    b[0][i][2] = i;
	}
	F0R(i,N) {
	    b[1][i].resize(3);
	    cin >> b[1][i][0] >> b[1][i][1];
	    b[1][i][2] = i;
	}
	sort(all(b[0])), sort(all(b[1]));
}

void solve() {
	F0R(i,2) F0R(j,N) {
	    ans[i][j] = MOD; 
	    if (b[i][j][0] == 0) {
	        q.push({i,j});
	        ans[i][j] = 0;
	    } else todo[i].insert(j);
	}
	
	while (sz(q)) {
	    pi t = q.front(); q.pop();
	    pi tmp = binsearch(t.f,t.s);
	    
	    while (1) {
	        auto it = todo[t.f^1].lb(tmp.f);
	        if (it == todo[t.f^1].end() || *it > tmp.s) break;
	        q.push({t.f^1,*it});
	        ans[t.f^1][*it] = ans[t.f][t.s]+1;
	        todo[t.f^1].erase(it); 
	    }
	}
}

int main() {
    input();
    solve();
	F0R(i,N) {
	    if (ans[0][i] == MOD) fin[b[0][i][2]] = -2;
	    else fin[b[0][i][2]] = ans[0][i];
	}
	F0R(i,N) cout << fin[i]+1 << "\n";
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!
