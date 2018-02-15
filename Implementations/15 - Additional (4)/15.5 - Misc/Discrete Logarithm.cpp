/**
 * Description: find k such that primitive^k=x
 * meet in the middle, O(sqrt(MOD))
 * Source: Own
 * Verification: PA 2006 - Professor Laugh's Numbers
 */
 
const int BLOCK = 32000;

int primitive = 5, invy[BLOCK];
unordered_map<int,int> u;

ll po (ll b, ll p) {
    return !p?1:po(b*b%MOD,p/2)*(p&1?b:1)%MOD;
}

ll inv (ll b) { return po(b,MOD-2); }
    
ll query(int x) {
	F0R(i,BLOCK) if (u.count(x*invy[i]%MOD)) 
	    return i*BLOCK+u[x*invy[i]%MOD];
	return -1;
}

int main() {
    ll cur = 1;
	F0R(i,BLOCK) {
	    u[cur] = i;
	    cur = primitive*cur%MOD;
	}
	ll t = 1;
	F0R(i,BLOCK) {
	    invy[i] = inv(t);
	    t = t*cur%MOD;
	}
	ll x; cin >> x;
	cout << query(x) << "\n";
}
