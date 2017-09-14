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
 
const int MOD = 1000000007, SZ = 1000;

struct BIT2D { 
    int bit[SZ+1][SZ+1];
    void upd(int X, int Y, int val) {
        for (; X <= SZ; X += (X&-X))
            for (int Y1 = Y; Y1 <= SZ; Y1 += (Y1&-Y1))
                bit[X][Y1] += val;
    }
    int query(int X, int Y) {
        int ans = 0;
        for (; X > 0; X -= (X&-X))
            for (int Y1 = Y; Y1 > 0; Y1 -= (Y1&-Y1))
                ans += bit[X][Y1];
        return ans;
    }
    int query(int X1, int X2, int Y1, int Y2) {
        return query(X2,Y2)-query(X1-1,Y2)-query(X2,Y1-1)+query(X1-1,Y1-1);
    }
};
 
int main() {
	BIT2D x; 
	x.upd(2,5,7);
	x.upd(3,6,8);
	x.upd(4,6,9);
	cout << x.query(2,3,5,6);
}
