// http://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/

#include <bits/stdc++.h>
  
using namespace std;
//using namespace __gnu_pbds;
  
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
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
  
pii p1, p2;
int H,W, grid[202][202];
int parent[202], max_flow = 0;   
  
bool bfs() {
    bool visited[202];
    memset(visited, 0, sizeof(visited));
  
    queue <int> q;
    q.push(0);
    visited[0] = true;
    parent[0] = -1;
  
    // Standard BFS Loop
    while (!q.empty()) {
        int u = q.front();
        q.pop();
  
        for (int v=0; v<202; v++) {
            if (visited[v] == false && grid[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
  
    return (visited[201] == true);
}
  
int fordFulkerson() {
    int u,v;
    while (bfs()) {
        int path_flow = INT_MAX;
        for (v = 201; v != 0; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, grid[u][v]);
        }
  
        for (v = 201; v != 0; v = parent[v]) {
            u = parent[v];
            grid[u][v] -= path_flow;
            grid[v][u] += path_flow;
        }
  
        max_flow += path_flow;
    }
  
    return max_flow;
}
  
int main() {
 
}
