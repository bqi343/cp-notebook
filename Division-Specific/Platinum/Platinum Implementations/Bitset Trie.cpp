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
 
int tri[3000000][3];
int q,p,l, nex=1;
 
void ins(int d) {
    tri[0][2] += d;
    int cind = 0;
    for (int i = 26; i >= 0; --i) {
        if (p & (1<<i)) {
            if (tri[cind][1] == 0) tri[cind][1] = nex++;
            cind = tri[cind][1];
            tri[cind][2] += d;
        } else {
            if (tri[cind][0] == 0) tri[cind][0] = nex++;
            cind = tri[cind][0];
            tri[cind][2] += d;
        }
    }
}
 
int query() {
    int cind = 0, cnum = 0, ans = 0;
     
    for (int i = 26; i >= 0; --i) {
        int x = cnum + (1<<i);
        if (p & (1<<i)) {
            int temp = p ^ cnum;
            temp = (temp>>i)<<i;
            if (temp < l) { // fix
                if (tri[cind][1] != 0) ans += tri[tri[cind][1]][2];
                cind = tri[cind][0];
            } else {
                cnum = x;
                cind = tri[cind][1];
            }
        } else {
            int temp = p ^ x;
            temp = (temp>>i)<<i;
            if (temp < l) { // fix
                if (tri[cind][0] != 0) ans += tri[tri[cind][0]][2];
                cnum = x;
                cind = tri[cind][1];
            } else {
                cind = tri[cind][0];
            }
        }
        if (cind == 0) break;
    }
    if (cind != 0) ans += tri[cind][2];
    return ans;
}
 
int main() {
    cin >> q;
    F0R(i,q) {
        int z; cin >> z;
        if (z == 1) {
            cin >> p;
            ins(1);
        } else if (z == 2) {
            cin >> p;
            ins(-1);
        } else {
            cin >> p >> l;
            cout << query() << "\n";
        }
    }
}
