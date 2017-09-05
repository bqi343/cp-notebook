#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
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

const int MOD = 1000000007;

Tree<int> val[100001];

int N,K;
pii pos[100000];
ll ans = 0;

void upd(int x, int y) {
    for (;x <= N; x += (x&-x)) val[x].insert(y);
}

int query(int x, int y) {
    int t = 0;    
    for (;x > 0; x -= (x&-x)) t += val[x].order_of_key(y+1);
    return t;
}

int query(int lox, int hix, int loy, int hiy) {
    return query(hix,hiy)-query(lox-1,hiy)-query(hix,loy-1)+query(lox-1,loy-1);
}

int main() {
}

// read!
// ll vs. int!
