// https://en.wikipedia.org/wiki/Lexicographically_minimal_string_rotation#Booth.27s_Algorithm

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int MOD = 1000000007;

int least_rotation(string S) {
    S += S;
    vi f = vi(S.length(),-1);
    int k = 0;       
    FOR(j,1,S.length()) {
        char sj = S[j];
        int i = f[j-k-1];
        while (i != -1 and sj != S[k+i+1]) {
            if (sj < S[k+i+1]) k = j-i-1;
            i = f[i];
        }
        if (sj != S[k+i+1]) {
            if (sj < S[k]) k = j;
            f[j-k] = -1;
        } else f[j-k] = i+1;
    }
    return k;
}
    
int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	cout << least_rotation("cccaabbb");
}

// read!
// ll vs. int!
