typedef pair<ll, ll> pll;

const int MOD = 1000000007;

// insert pair operators here

pll po[200000], ipo[200000], cum[200000];
pll base = mp(948392576,573928192);

ll powe(ll b, ll p) {
    return !p?1:powe(b*b%MOD,p/2)*(p&1?b:1)%MOD;
}

ll inv(ll x) {
    return powe(x,MOD-2);
}

string s; 

void gen() {
    po[0] = ipo[0] = {1,1};
    FOR(i,1,200000) {
        po[i] = po[i-1]*base;
        ipo[i] = {inv(po[i].f),inv(po[i].s)};
    }
    F0R(i,s.length()) cum[i+1] = cum[i]+int(s[i]-'a'+1)*po[i];
}

pll get(int l, int r) {
    return ipo[l]*(cum[r+1]-cum[l]);
}

int main() {
    cin >> s; // abacaba
    gen();
    F0R(i,s.length()) FOR(j,i,s.length()) cout << i << " " << j << " " << get(i,j).f << " " << get(i,j).s << "\n";
}

// read!
// ll vs. int!
