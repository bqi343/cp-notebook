// https://open.kattis.com/problems/primesieve

template<int SZ> struct Sieve {
    bitset<SZ+1> comp;
    Sieve() {
        for (int i = 2; i*i <= SZ; ++i) if (!comp[i]) {
            for (int j = i*i; j <= SZ; j += i) comp[j] = 1;
        }
    }
    bool isprime(int x) {
        if (x == 1) return 0;
        return !comp[x];
    }
};

int n,q,ans=0;

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    Sieve<100000000> s; cin >> n >> q;
    FOR(i,1,n+1) if (s.isprime(i)) ans ++;
    cout << ans << "\n";
    F0R(i,q) {
        int x; cin >> x;
        cout << s.isprime(x) << "\n";
    }
}
