// http://codeforces.com/blog/entry/22072
// http://www.usaco.org/index.php?page=viewproblem2&cpid=102

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

template<int SZ> struct LazySegTree { 
	ll sum[2*SZ], lazy[2*SZ]; 

	LazySegTree() {
		F0R(i,2*SZ) sum[i] = lazy[i] = 0;
	}

	void push(int ind, int L, int R) {
		sum[ind] += (R-L+1)*lazy[ind];
		if (L != R) lazy[2*ind] += lazy[ind], lazy[2*ind+1] += lazy[ind];
		lazy[ind] = 0;
	}

	void build() {
		for (int i = SZ-1; i > 0; --i) sum[i] = sum[2*i]+sum[2*i+1];
	}

	void pull(int ind) {
		sum[ind] = sum[2*ind]+sum[2*ind+1];
	}

	ll qsum(int lo, int hi, int ind = 1, int L = 0, int R = SZ-1) {
		push(ind,L,R);
		if (lo > R || L > hi) return 0;
		if (lo <= L && R <= hi) return sum[ind];

		int M = (L+R)/2;
		return qsum(lo,hi,2*ind,L,M)+qsum(lo,hi,2*ind+1,M+1,R);
	}

	void upd(int lo, int hi, int val, int ind = 1, int L = 0, int R = SZ-1) { // take account for minimum as well
		push(ind,L,R);
		if (hi < L || R < lo) return;
		if (lo <= L && R <= hi) {
			lazy[ind] = val;
			push(ind,L,R);
			return;
		}

		int M = (L+R)/2;
		upd(lo,hi,val,2*ind,L,M); upd(lo,hi,val,2*ind+1,M+1,R);
		pull(ind);
	}
};

vector<vi> graph;

template <int V> struct HeavyLight {
    int parent[V], heavy[V], depth[V];
    int root[V], treePos[V];
    LazySegTree<V> tree;

    void init() {
        int n = graph.size();
        FOR(i,1,n+1) heavy[i] = -1;
        parent[1] = -1, depth[1] = 0;
        dfs(1);
        for (int i = 1, currentPos = 0; i <= n; ++i)
			if (parent[i] == -1 || heavy[parent[i]] != i)
				for (int j = i; j != -1; j = heavy[j]) {
					root[j] = i;
					treePos[j] = currentPos++;
				}
    }
    
    int dfs(int v) {
        int size = 1, maxSubtree = 0;
        for (auto u : graph[v]) if (u != parent[v]) {
            parent[u] = v;
            depth[u] = depth[v] + 1;
            int subtree = dfs(u);
            if (subtree > maxSubtree) heavy[v] = u, maxSubtree = subtree;
            size += subtree;
        }
        return size;
    }

    template <class BinaryOperation>
    void processPath(int u, int v, BinaryOperation op) {
        for (; root[u] != root[v]; v = parent[root[v]]) {
            if (depth[root[u]] > depth[root[v]]) swap(u, v);
            op(treePos[root[v]], treePos[v]);
        }
        if (depth[u] > depth[v]) swap(u, v);
        op(treePos[u]+1, treePos[v]); // assumes values are stored in edges, not vertices
    }

    void modifyPath(int u, int v, int value) {
        processPath(u, v, [this, &value](int l, int r) { tree.upd(l, r, value); });
    }

    ll queryPath(int u, int v) {
        ll res = 0;
        processPath(u, v, [this, &res](int l, int r) { res += tree.qsum(l, r); });
        return res;
    }
};

HeavyLight<1<<17> H;
int N,M;

int main() {
	cin >> N >> M;
	graph.resize(N+1);
	F0R(i,N-1) {
	    int a,b; cin >> a >> b;
	    graph[a].pb(b), graph[b].pb(a);
	}
	H.init();
	F0R(i,M) {
	    char c; int A,B;
	    cin >> c >> A >> B;
	    if (c == 'P') H.modifyPath(A,B,1);
	    else cout << H.queryPath(A,B) << "\n";
	}
}

/*
Input 
4 6
1 4
2 4
3 4
P 2 3
P 1 3
Q 3 4
P 1 4
Q 2 4
Q 1 4
*/

/*
Output
2
1
2
*/
