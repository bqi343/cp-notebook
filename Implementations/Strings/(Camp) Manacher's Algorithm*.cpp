// http://codeforces.com/blog/entry/12143
// Manacher's Algorithm: Calculates length of largest palindrome centered at each character of string
// Also computes even-length palindromes

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

vi manacher(string s) {
    string s1 = "@";
    for (char c: s) s1 += c, s1 += "#";
    s1[s1.length()-1] = '&'; 
    
    vi ans(s1.length()-1);
    int lo = 0, hi = 0; 
    FOR(i,1,s1.length()-1) {
        ans[i] = min(hi-i,ans[hi-i+lo]);
        while (s1[i-ans[i]-1] == s1[i+ans[i]+1]) ans[i] ++;
        if (i+ans[i] > hi) lo = i-ans[i], hi = i+ans[i];
    }
    
    ans.erase(ans.begin());
    F0R(i,ans.size()) if ((i&1) == (ans[i]&1)) ans[i] ++; // adjust lengths
    return ans;
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	vi a1 = manacher("abacaba");
	for (int i: a1) cout << i << " ";
	cout << "\n";
	
	vi a2 = manacher("aabbaaccaabbaa");
	for (int i: a2) cout << i << " ";
}

// read!
// ll vs. int!
