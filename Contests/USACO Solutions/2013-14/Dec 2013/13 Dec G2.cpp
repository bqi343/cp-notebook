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

vi ans;
int N,D;
ll sum = 0, seg[1<<17][2][2];

ifstream cin ("optmilk.in");
ofstream cout ("optmilk.out");
 
void upd(int ind, int low, int high, int x, int val) {
    if (high < x || x < low) return;
    if (low == high) seg[ind][1][1] = val;
    else {
	    upd(2*ind,low,(low+high)/2,x,val);
	    upd(2*ind+1,(low+high)/2+1,high,x,val);
    	seg[ind][0][0] = seg[ind][1][0] = seg[ind][0][1] = seg[ind][1][1] = 0;
	    F0R(a,2) F0R(b,2) F0R(c,2) F0R(d,2) if (b == 0 || c == 0) 
	    	seg[ind][a][d] = max(seg[ind][a][d],seg[2*ind][a][b]+seg[2*ind+1][c][d]);
    }
}

void init() {
	cin >> N >> D;
	F0R(i,N) {
		int m; cin >> m;
		upd(1,0,N-1,i,m);
	}
}

int main() {
	init();
	F0R(j,D) {
		int x,y; cin >> x >> y;
		upd(1,0,N-1,x-1,y);
		sum += max(max(seg[1][1][0],seg[1][0][1]),max(seg[1][1][1],seg[1][0][0]));
	}
	cout << sum;
}
