/*#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>*/
#include <bits/stdc++.h>

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

int grid[9][9];
int dp[3][512], cur[9][9];
int cdp[512];

int csum = 0, sq[3], ro[9], co = 0, cost = 0;

void search(int r, int c) {
    if (c == 8) {
        int lst = ro[r];
        if (lst)csum ^= 256, sq[2] ^= 1,ro[r] ^= 1;
        cost += (grid[r][c]^lst);
        
        if (r % 3 == 2) dp[r/3][csum] = min(dp[r/3][csum],cost); 
        else search(r+1,0);
        
        if (lst) csum ^= 256, sq[2] ^= 1, ro[r] ^= 1;
        cost -= (grid[r][c]^lst);
    } else if (r % 3 == 2 && c % 3 == 2) {
        int lst = sq[c/3];
        if (lst) csum ^= (1<<c), sq[c/3] ^= 1, ro[r] ^= 1;
        cost += (grid[r][c]^lst);
        
        search(r,c+1);
        
        if (lst) csum ^= (1<<c), sq[c/3] ^= 1, ro[r] ^= 1;
        cost -= (grid[r][c]^lst);
    } else {
        cost += (grid[r][c]^0);
        search(r,c+1);
        cost -= (grid[r][c]^0);
        
        cost += (grid[r][c]^1);
        csum ^= (1<<c), sq[c/3] ^= 1, ro[r] ^= 1;
        search(r,c+1);
        csum ^= (1<<c), sq[c/3] ^= 1, ro[r] ^= 1;
        cost -= (grid[r][c]^1);
    }
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	F0R(i,9) F0R(j,9) {
	    char c; cin >> c;
	    if (c == '1') grid[i][j] = 1;
	}
	F0R(i,3) F0R(j,512) dp[i][j] = 1000;
	
	search(0,0);
	search(3,0);
	search(6,0); 
	cdp[0] = 0;
	FOR(i,1,512) cdp[i] = 1000;
	
	F0R(i,3) {
	    int tmp[512]; F0R(j,512) tmp[j] = 1000;
	    F0R(j,512) F0R(k,512) tmp[j^k] = min(tmp[j^k],cdp[j]+dp[i][k]);
	    F0R(j,512) cdp[j] = tmp[j];
	}
	cout << cdp[0];
}
