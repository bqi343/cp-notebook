#include <bits/stdc++.h>
 
using namespace std;
 
#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define pb push_back
  
typedef vector<int> vi;
  
const int MAXN = 100001, MAXK = 20;
  
vi edges[MAXN];
int parK[MAXK][MAXN];
int depth[MAXN],wei[MAXN];
  
int V, Q;
  
void dfs(int u, int prev){
  parK[0][u] = prev; 
  depth[u] = depth[prev]+1;
  for (int v: edges[u]) if (v != prev) dfs(v, u);
}
  
int lca(int u, int v){
  int k = MAXK-1;
  while(k>=0){
    int d = 1<<k;
    if(depth[u]>=depth[v]+d) u=parK[k][u];
    if(depth[v]>=depth[u]+d) v=parK[k][v];
    k--;
  }
  k = MAXK-1;
  while(k>=0){
    if(parK[k][u] != parK[k][v]){
      u = parK[k][u];
      v = parK[k][v];
    }
    k--;
  }
  if(u != v){
    u = parK[0][u];
    v = parK[0][v];
  }
  return u;
}
  
int main(){
    cin >> V >> Q;
    FOR(i,1,V+1) cin >> wei[i];
    int u,v,w; 
    F0R(i,V-1) { 
        cin >> u >> v;
        edges[u].pb(v);
        edges[v].pb(u);
    }
    dfs(1, 0);
     
    FOR(k,1,MAXK) 
        FOR(i,1,V+1)
            parK[k][i] = parK[k-1][parK[k-1][i]]; 
}
