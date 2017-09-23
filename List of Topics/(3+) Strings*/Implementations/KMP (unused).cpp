// note that Z algorithm can be used in place of this

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

vi kmp_table(string W) { 
    vi T(W.length()+1); T[0] = -1;
    int pos = 1; // the current position we are computing in T
    int cnd = 0; // the zero-based index in W of the next character of the current candidate substring

    while (pos < (int)W.length()) {
        if (W[pos] == W[cnd]) T[pos] = T[cnd];
        else {
            T[pos] = cnd; cnd = T[cnd];
            while (cnd >= 0 && W[pos] != W[cnd]) cnd = T[cnd];
        }
        pos++, cnd++;
    }
    T[pos] = cnd;
    return T;
}

vi kmp_search(string S, string W) {
    int m = 0; // beginning of the current match in S
    int i = 0; // position of the current character in W
    vi T = kmp_table(W);
    vi ans;
    
    while (m+i < (int)S.length()) 
        if (W[i] == S[m+i]) {
            i++;
            if (i == (int)W.length()) {
                ans.pb(m);
                m = m+i-T[i], i = T[i]; 
            }
        } else {
            if (T[i] > -1) m = m+i-T[i], i = T[i];
            else m = m+i+1, i = 0;
        }
    return ans;
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	vi x = kmp_search("abacaba","aba");
	cout << x.size() << "\n";
	for (int i: x) cout << i << " ";
}

// read!
// ll vs. int!