// http://codeforces.com/blog/entry/12143

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

vi pal_array(string s) {
	int n = s.length();
	s = "@" + s + "$";
	vi len(n + 1);
	
	int l = 1, r = 1;
    	FOR(i,1,n+1) {
        	len[i] = min(r - i, len[l + (r - i)]);
        	while(s[i - len[i]] == s[i + len[i]]) len[i]++;
        	if(i + len[i] > r) l = i - len[i], r = i + len[i];
    	}
    
    	len.erase(len.begin());
    	return len;
}

int main() {
	vi x = pal_array("abacaba");
	for (int i: x) cout << i << " ";
}

// Output 1 2 1 4 1 2 1
// Insert #'s between characters for even-length palindromes
