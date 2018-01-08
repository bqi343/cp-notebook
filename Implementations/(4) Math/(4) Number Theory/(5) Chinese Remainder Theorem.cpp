/**
* Source: Own
* Verification: 
    * Kattis generalchineseremainder
    * POI 9 Rhyme
*/

typedef pair<ll,ll> pll;

struct CRT {
    ll n,m,a,b; 
    map<ll,pii> M;
    bool bad;
    
    ll inv(ll a, ll b) { // 0 < a < b, gcd(a,b) = 1
        a %= b;
        if (a <= 1) return a;
        ll i = inv(b%a,a);
        ll tmp = -((b/a)*i+((b%a)*i)/a) % b;
        while (tmp < 0) tmp += b;
        return tmp;
    }
    
    ll naive(ll n, ll m, ll a, ll b) {
        ll x = (a-b)*inv(m,n) % n;
        ll ans = (m*x+b) % (m*n);
        while (ans < 0) ans += (m*n);
        return ans;
    }
    
    void process(ll a, ll n) {
        vector<pii> z;
        for (int i = 2; i*i <= n; ++i) if (n % i == 0) {
            int co = 0;
            while (n % i == 0) n /= i, co++;
            z.pb({i,co});
        }
        if (n != 1) z.pb({n,1});
        for (auto A: z) {
            if (M.count(A.f)) {
                pii p1 = M[A.f];
                pii p2 = {A.s,a%(ll)pow(A.f,A.s)};
                if (p1 > p2) swap(p1,p2);
                if (p2.s%(ll)pow(A.f,p1.f) != p1.s) bad = 1;
                M[A.f] = p2;
            } else M[A.f] = {A.s,a%(ll)pow(A.f,A.s)};
        }
    }
    
    ll po(ll b, ll p) {
        ll z = 1;
        F0R(i,p) z *= b;
        return z;
    }
    
    pll solve(ll aa, ll nn, ll bb, ll mm) {
        bad = 0, M.clear(); 
        a = aa, n = nn, b = bb, m = mm;
        process(a,n), process(b,m);
        if (bad) {
            cout << "NIE";
            exit(0);
        }
        ll a1 = 0, a2 = 1;
        for (auto& x: M) {
            a1 = naive(a2,po(x.f,x.s.f),a1,x.s.s);
            a2 *= po(x.f,x.s.f);
        }
        return {a1,a2};
    }
};
