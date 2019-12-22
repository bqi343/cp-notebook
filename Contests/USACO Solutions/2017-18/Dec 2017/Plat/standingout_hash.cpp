#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<ll, ll> pl;
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
#define all(x) x.begin(), x.end()

const int MOD = 1000000007;
const int MX = 100000;

pl base = {5839283,68294319};

pl operator+(const pl& l, const pl& r) {
    return {(l.f+r.f)%MOD,(l.s+r.s)%MOD};
};

pl operator-(const pl& l, const pl& r) {
    return {(l.f-r.f+MOD)%MOD,(l.s-r.s+MOD)%MOD};
};

pl operator*(const pl& l, const pl& r) {
    return {l.f*r.f%MOD,l.s*r.s%MOD};
}

pl operator*(const ll& l, const pl& r) {
    return {l*r.f%MOD,l*r.s%MOD};
}

struct hsh {
    int N;
    string S;
    vector<pl> po, ipo, cum;
    
    ll modpow(ll b, ll p) { return !p?1:modpow(b*b%MOD,p/2)*(p&1?b:1)%MOD; }
    
    ll inv(ll x) { return modpow(x,MOD-2); }
    
    void init(string _S) {
        S = _S, N = sz(S); S += char('a'-1);
        po.resize(N), ipo.resize(N); cum.resize(N+1);
        
        po[0] = ipo[0] = {1,1};
        FOR(i,1,N) {
            po[i] = base*po[i-1];
            ipo[i] = {inv(po[i].f),inv(po[i].s)};
        }
        F0R(i,N) cum[i+1] = cum[i]+(S[i]-'a'+1)*po[i];
    }
    
    pl get(int l, int r) {
        return (cum[r+1]-cum[l])*ipo[l];
    }
};

int N, ind[MX];
hsh S[MX];
ll ans[MX];

int lcp(pl a, pl b) {
    if (a.f == -1) return 0;
    
    int lo = 0, hi = min(S[a.f].N-a.s,S[b.f].N-b.s); // how many characters match
    while (lo < hi) {
        int mid = (lo+hi+1)/2;
        if (S[a.f].get(a.s,a.s+mid-1) == S[b.f].get(b.s,b.s+mid-1)) lo = mid;
        else hi = mid-1;
    }
    return lo;
}

struct cmp {
    bool operator()(const pl& a, const pl& b) const {
        int t = lcp(a,b);
        if (S[a.f].S[a.s+t] != S[b.f].S[b.s+t]) return S[a.f].S[a.s+t] < S[b.f].S[b.s+t];
        return a.f < b.f;
    }
};

set<pl,cmp> cur, todo[MX];
pl pre = {-1,-1};

void init() {
    freopen("standingout.in","r",stdin);
    freopen("standingout.out","w",stdout);
    
    cin >> N;
    F0R(i,N) {
        string _S; cin >> _S;
        S[i].init(_S);
    }
}

int main() {
    init();
    F0R(i,N) {
        F0R(j,S[i].N) todo[i].insert({i,j});
        cur.insert(*todo[i].begin()); todo[i].erase(todo[i].begin());
    }
    
    while (sz(cur)) {
        auto a = *cur.begin(); cur.erase(cur.begin());
        int c = lcp(pre,a);
        if (sz(cur)) c = max(c,lcp(a,*cur.begin()));
        ans[a.f] += S[a.f].N-a.s-c;
        
        if (sz(todo[a.f])) {
            cur.insert(*todo[a.f].begin());
            todo[a.f].erase(todo[a.f].begin());
        }
        pre = a;
    }
    F0R(i,N) cout << ans[i] << "\n";
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!
