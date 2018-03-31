// http://codeforces.com/blog/entry/22072

#include<vector>
#include<fstream>

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> pi;

#define f first
#define s second
#define pb push_back
#define F0R(i,a) for (int i = 0; i < a; ++i)
#define F0Rd(i,a) for (int i = a-1; i >= 0; --i)
#define FOR(i,a,b) for (int i = a; i < b; ++i)

const int MOD = 1000000007;

template<int SZ>
class LazySegTree { 
    public:
    	int sum[2*SZ], lazy[2*SZ]; 
    	
    	LazySegTree() {
    		F0R(i,2*SZ) sum[i] = 0;
    		F0R(i,2*SZ) lazy[i] = 0;
    	}
    	
    	void push(int ind, int L, int R) {
    		sum[ind] += (R-L+1)*lazy[ind];
    		if (L != R) lazy[2*ind] = lazy[ind], lazy[2*ind+1] = lazy[ind];
    		lazy[ind] = 0;
    	}
    	
    	void build() {
    		for (int i = SZ-1; i > 0; --i) sum[i] = sum[2*i]+sum[2*i+1];
    	}
    	
    	void pull(int ind) {
    		sum[ind] = sum[2*ind]+sum[2*ind+1];
    	}
    	 
    	int qsum(int lo, int hi, int ind = 1, int L = 0, int R = SZ-1) {
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

vector<vector<pi>> graph;

template <int V>
class HeavyLight {
    public:
        int parent[V], heavy[V], depth[V];
        int root[V], treePos[V];
        LazySegTree<V> tree;
    
        HeavyLight() {
            int n = graph.size();
            fill_n(heavy, n, -1);
            parent[0] = -1, depth[0] = 0;
            dfs(0);
            for (int i = 0, currentPos = 0; i < n; ++i)
                if (parent[i] == -1 || heavy[parent[i]] != i)
                    for (int j = i; j != -1; j = heavy[j]) {
                    root[j] = i;
                    treePos[j] = currentPos++;
                }
        }
        
        int dfs(int v) {
            int size = 1, maxSubtree = 0;
            for (pi u : graph[v]) if (u.f != parent[v]) {
                parent[u.f] = v;
                depth[u.f] = depth[v] + 1;
                int subtree = dfs(u.f);
                if (subtree > maxSubtree) heavy[v] = u.f, maxSubtree = subtree;
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
            op(treePos[u]+1, treePos[v]);
        }

        void modifyPath(int u, int v, int value) {
            processPath(u, v, [this, &value](int l, int r) { tree.upd(l, r, value); });
        }

        int queryPath(int u, int v) {
            int res = 0;
            processPath(u, v, [this, &res](int l, int r) { res = res+tree.qsum(l, r); });
            return res;
        }
};

int N,M;

int main() {
    ifstream cin ("grassplant.in");
    ofstream cout ("grassplant.out");
    
    cin >> N >> M; graph.resize(N);
    F0R(i,N-1) {
        int a,b; cin >> a >> b;
        a--,b--;
        graph[a].pb({b,0});
        graph[b].pb({a,0});
    }
    
	HeavyLight<1<<17> H;
	F0R(i,M) {
	    char c; cin >> c;
	    int a,b; cin >> a >> b;
	    a--, b--;
	    
	    if (c == 'P') H.modifyPath(a,b,1);
	    else cout << H.queryPath(a,b) << "\n";
	}
}
