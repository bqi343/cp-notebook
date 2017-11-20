/*#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>*/
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

int xdir[4] = {0,1,0,-1}, ydir[4] = {1,0,-1,0};
int dist[21][21];
queue<pii> todo;

void process(pii x) {
	F0R(i,4) { // easily iterate through adjacent points
        pii y = {x.f+xdir[i],x.s+ydir[i]};
	if (y.f < 0 || y.f > 20 || y.s < 0 || y.s > 20) continue; // ignore this point if it's outside of grid
        if (dist[y.f][y.s] == MOD) { // test whether point has been visited or not
            dist[y.f][y.s] = dist[x.f][x.s]+1;
            todo.push(y); // push point to queue
        }
    }
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	F0R(i,21) F0R(j,21) dist[i][j] = MOD;
	dist[10][10] = 0; todo.push({10,10}); // initialize queue, distances
	while (todo.size()) {
	    process(todo.front());
	    todo.pop(); // pop point from queue
	}
	cout << dist[4][5]; // 11
}
