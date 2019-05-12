#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define double long double
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

typedef pair<int,vi> T;

const int MOD = 1000000007;

int n, r[20], d[20];
int en;
map<vi,int> m;
deque<T> x;

int rot(int a, int num) {
    if (num&1) a = 11-a;
    if (num&2) {
        int t = a%3;
        a += 2-2*t;
    }
    if (num&4) {
        int t = 2*(a%3)+9;
        a = t-a;
    }
    return a;
}

void process(int num, vi v) { // cused, in current, beg, end
    if (m[v] < num) return;
    /*cout << "HI " << num << "\n";
    for (int i: v) cout << i << " ";
    cout << "\n";
    cout << "-----\n\n";*/
    if (v[0] == en) {
        if (v[1] == 0) {
            cout << num;
            exit(0);
        }
        return;
    }
    
    if (v[1] == 0) {
        F0R(i,n) if (!(v[0]&(1<<i))) {
            v[0] ^= 1<<i;
            v[1] ^= 1<<d[i];
            v[2] = r[i], v[3] = d[i];
            
            if (m.count(v)) return;
            m[v] = num+1;
            x.pb({num+1,v});
            return;
        }
    } else {
        F0R(i,n) if (!(v[0]&(1<<i))) {
            F0R(j,8) {
                pii t = {rot(r[i],j), rot(d[i],j)};
                
                if (v[3] != t.f) continue;
                if (v[1]&(1<<t.s)) continue;
                
                vi V = v;
                V[0] ^= 1<<i;
                V[1] ^= 1<<t.s;
                
                if (t.s == V[2]) {
                    V[1] = 0;
                    V[2] = V[3] = -1;
                } else V[3] = t.s;
                
                if (m.count(V) && m[V] <= num) continue;
                
                m[V] = num;
                x.push_front({num,V});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin >> n; en = (1<<n)-1;
    F0R(i,n) cin >> r[i] >> d[i];
    
    x.pb({0,{0,0,-1,-1}});
    while (x.size()) {
        auto a = x.front(); x.pop_front();
        process(a.f,a.s);
    }
    cout << -1;
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!