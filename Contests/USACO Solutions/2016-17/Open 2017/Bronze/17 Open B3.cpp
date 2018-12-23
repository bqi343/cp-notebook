// #include<iostream>
#include<fstream>
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

ifstream cin("art.in");
ofstream cout ("art.out");

pair<pi,pi> col[10];
int N,num,grid[10][10];
bool posi[10];

int main() {
	cin >> N;
	F0R(i,10) col[i] = {{N,N},{-1,-1}};
	F0R(i,N) F0R(j,N) {
		char c; cin >> c;
		int x = c-'0';
		grid[i][j] = x;
		posi[x] = 1;
		col[x].f.f = min(col[x].f.f,i);
		col[x].s.f = max(col[x].s.f,i);
		col[x].f.s = min(col[x].f.s,j);
		col[x].s.s = max(col[x].s.s,j);
	}
	FOR(i,1,10) if (col[i].f.f != N) {
		FOR(j,col[i].f.f,col[i].s.f+1)
			FOR(k,col[i].f.s,col[i].s.s+1) 
				if (grid[j][k] != i) posi[grid[j][k]] = 0;
	}
	FOR(i,1,10) num += posi[i];
	cout << num;
}
