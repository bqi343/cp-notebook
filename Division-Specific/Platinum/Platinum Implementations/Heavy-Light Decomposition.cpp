// http://codeforces.com/blog/entry/22072

#include<bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> pii;

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
    	int mn[2*SZ], lazy[2*SZ]; 
    	
    	LazySegTree() {
    		F0R(i,2*SZ) mn[i] = 0;
    		F0R(i,2*SZ) lazy[i] = -MOD;
    	}
    	
    	void push(int ind, int L, int R) {
    		if (lazy[ind] == -MOD) return;
    		mn[ind] = lazy[ind];
    		if (L != R) lazy[2*ind] = lazy[ind], lazy[2*ind+1] = lazy[ind];
    		lazy[ind] = -MOD;
    	}
    	
    	void build() {
    		for (int i = SZ-1; i > 0; --i) mn[i] = min(mn[2*i],mn[2*i+1]);
    	}
    	
    	void pull(int ind) {
    		mn[ind] = min(mn[2*ind],mn[2*ind+1]);
    	}
    	 
    	int qmin(int lo, int hi, int ind = 1, int L = 0, int R = SZ-1) {
    		push(ind,L,R);
    		if (lo > R || L > hi) return MOD;
    		if (lo <= L && R <= hi) return mn[ind];
    		
    		int M = (L+R)/2;
    		return min(qmin(lo,hi,2*ind,L,M),qmin(lo,hi,2*ind+1,M+1,R));
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

vector<vector<pii>> graph;

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
            for (pii u : graph[v]) if (u.f != parent[v]) {
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

        void set(int v, int value) {
            tree.upd(treePos[v], treePos[v], value);
        }

        void modifyPath(int u, int v, int value) {
            processPath(u, v, [this, &value](int l, int r) { tree.upd(l, r, value); });
        }

        int queryPath(int u, int v) {
            int res = MOD;
            processPath(u, v, [this, &res](int l, int r) { res = min(res,tree.qmin(l, r)); });
            return res;
        }
};

int main() {
	
}
