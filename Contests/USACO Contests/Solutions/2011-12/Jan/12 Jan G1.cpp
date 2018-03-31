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

struct mat {
    int d[300][300];
    mat() {
        F0R(i,300) F0R(j,300) d[i][j] = -1;
    }
    mat operator*(const mat& B) {
        mat C;
        F0R(i,300) F0R(j,300) if (d[i][j] > -1) F0R(k,300) if (B.d[j][k] > -1) {
            C.d[i][k] = max(C.d[i][k],d[i][j]+B.d[j][k]);
        }
        return C;
    }
};

vector<string> posi;
set<string> combo;
map<string,int> rposi;
int N,K,co;
mat ori;

int get(string s) {
    while (rposi.find(s) == rposi.end()) s = s.substr(1,s.length()-1);
    return rposi[s];
}

int val (string s) {
    int z = 0;
    while (s.size()) {
        if (combo.find(s) != combo.end()) z++;
        s = s.substr(1,s.length()-1);
    }    
    return z;
}

mat po(mat b, int p) {
    mat ans; F0R(i,300) ans.d[i][i] = 0;
    while (p) {
        if (p&1) ans = ans*b;
        b = b*b;
        p /= 2;
    }
    return ans;
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> N >> K;
	posi.pb("");
	F0R(i,N) {
	    string x; cin >> x;
	    combo.insert(x);
	    
	    string x1;
	    F0R(j,x.length()) {
	        x1 += x[j];
	        posi.pb(x1);
	    }
	}
	sort(posi.begin(),posi.end());
	posi.erase(unique(posi.begin(),posi.end()),posi.end());
	F0R(i,posi.size()) rposi[posi[i]] = i;
	
	F0R(i,posi.size()) F0R(j,3) {
	    string s = posi[i]+char('A'+j);
	    ori.d[i][get(s)] = val(s);
	}
	
	ori = po(ori,K);
	int ans = 0;
	F0R(i,300) ans = max(ans,ori.d[0][i]);
	cout << ans;
}
