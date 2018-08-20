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
 
int ans = 0, N, M[20];
vi vec[1<<20];

void merg(int x, int ad) {
    int i1 = 0, i2 = 0;
    while (i1 < (int)vec[x].size() && i2 < (int)vec[x].size()) {
        if (vec[x][i1] < M[ad]+vec[x][i2]) vec[x^(1<<ad)].pb(vec[x][i1++]);
        else vec[x^(1<<ad)].pb(M[ad]+vec[x][i2++]);
    }
    while (i2 < (int)vec[x].size()) vec[x^(1<<ad)].pb(M[ad]+vec[x][i2++]);
    return;
}

void gen(int x) {
    if (vec[x].size()) return;
    if (x == 0) {
        vec[0].pb(0);
        return;
    }
    F0Rd(i,N) if (x&(1<<i)) {
        gen(x^(1<<i));
        merg(x^(1<<i),i);
        return;
    }
}

bool get(int x0, int x1, int sum) {
    gen(x0), gen(x1);
    int i1 = 0, i2 = vec[x1].size()-1;
    bool f = 1;
    while (f) {
        f = 0;
        while (i1 < (int)vec[x0].size()-1 && vec[x0][i1]+vec[x1][i2] < sum) i1++, f = 1;
        while (i2 > 0 && vec[x0][i1]+vec[x1][i2] > sum) i2--, f = 1;
        if (vec[x0][i1]+vec[x1][i2] == sum) return 1;
    }
    return 0;
}

bool test(int ind) {
    vi x(2);
    int co = 0, sum = 0;
    F0R(i,N) if (ind&(1<<i)) {
        x[co^=1]^=(1<<i);
        sum += M[i];
    }
    if (sum % 2 != 0) return 0;
    return get(x[0],x[1],sum/2);
}

int main() {
    cin >> N; 
    F0R(i,N) cin >> M[i];
    FOR(i,1,1<<N) if (test(i)) ans++;
    cout << ans;
}
