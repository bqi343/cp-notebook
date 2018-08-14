#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
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

int num, ans, sq[51], pri[51], co[51];
string tmp;
vector<string> ok;

int getvowel(string t) {
    int ret = 0;
    for (char& c: t) {
        if ('A' <= c && c <= 'Z') c = char(int(c-'A')+'a');
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') ret += 2;
        if (c == 'y') ret ++;
    }
    return ret;
}

bool valid1(string z) {
    if (!pri[sz(z)]) return 0;
    int Z = getvowel(z);
    if (Z % 2 == 1) return 0;
    Z /= 2;
    return Z&1;
}

bool valid2(string z) {
    if (!sq[sz(z)]) return 0;
    int Z = getvowel(z);
    if (Z % 2 == 1) return 0;
    Z /= 2;
    return sq[Z];
}

void test(string tmp) {
    while (tmp[tmp.size()-1] == '\n' || tmp[tmp.size()-1] == '\r') tmp.erase(tmp.end()-1);
    if (valid1(tmp) || valid2(tmp)) {
        ok.pb(tmp);
        ans ++;
    }
}

void solve() {
    cin >> num; 
    ans = 0; ok.clear();
    
    getline(cin,tmp);
    F0R(i,num) {
        getline(cin,tmp);
        test(tmp);
    }
    
    if (ans == 0) {
        cout << "It's hopeless!\n";
        return;
    }
    
    cout << ans << " valid options\n";
    for (auto a: ok) cout << a << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    F0R(i,8) sq[i*i] = 1;
    FOR(i,2,51) if (!co[i]) {
        pri[i] = 1;
        for (int j = i; j <= 50; j += i) co[j] = 1;
    }
    
    int n; cin >> n;
    FOR(i,1,n+1) {
        cout << "Practice #" << i << ": ";
        solve();
        cout << "\n";
    }
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!
