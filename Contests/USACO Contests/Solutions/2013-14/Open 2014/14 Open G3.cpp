/*#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>*/
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

const int MOD = 1234567;

struct node {
    array<int,10> nex, bad;
    int val;
    node (int v) {
        val = v;
        F0R(i,10) nex[i] = -1, bad[i] = 1;
    }
};

/////////// OK
struct trie {
    vector<node> v;
    
    void ins(string x) {
        int cur = 0;
        for (char i: x) {
            if (v[cur].nex[i-'0'] == -1) {
                v[cur].nex[i-'0'] = v.size();
                v.pb(node(0));
            }
            cur = v[cur].nex[i-'0'];
        }
    }
    
    bool fin(string x) {
        if (x.length() != 5) return 0;
        int cur = 0;
        for (char i: x) {
            if (v[cur].nex[i-'0'] == -1) return 0;
            cur = v[cur].nex[i-'0'];
        }
        return 1;
    }
    
    int query(string cur) {
        int ind = 0;
        ll ans = 1;
        
        F0R(i,cur.length()) {
            if (v[ind].nex[cur[i]-'0'] != -1) {
                ans = ans*v[ind].bad[cur[i]-'0'] % MOD;
                ind = v[ind].nex[cur[i]-'0'];
            } else {
                ans = ans*v[ind].val % MOD;
                break;
            }
            if (i == (int)cur.length()-1) {
                ans = ans*v[ind].val % MOD;
                break;
            }
        }
        return ans;
    }
    void prin() {
        for (auto a: v) {
            cout << a.val << "\n";
            F0R(i,10) cout << a.nex[i] << " ";
            cout << "\n";
            F0R(i,10) cout << a.bad[i] << " ";
            cout << "\n";
        }
        cout << "-----\n";
    }
};

int N,M, p[20000];
vi child[20000];
trie bad[20000], tri[20000], tot[20000];

/////////// OK
ll po(ll b, ll z) {
    ll ans = 1;
    while (z) {
        if (z&1) ans = (ans*b) % MOD;
        b = b*b % MOD;
        z /= 2;
    }
    return ans;
}

void comb(trie& l, trie& r, int il, int ir) {
    l.v[il].val = ((ll)l.v[il].val*r.v[ir].val) % MOD;
    F0R(i,10) 
        if (r.v[ir].nex[i] != -1) {
            if (l.v[il].nex[i] == -1) {
                l.v[il].nex[i] = l.v.size();
                l.v.pb(node(1));
            }
            comb(l,r,l.v[il].nex[i], r.v[ir].nex[i]);
        } else l.v[il].bad[i] = ((ll)l.v[il].bad[i]*r.v[ir].val) % MOD;
}

void fill(trie& l, int x, int ind, string cur) {
    F0R(i,10) if (!bad[x].fin(char('0'+i)+cur)) {
        tri[x].v[ind].val = (tri[x].v[ind].val+l.query(char('0'+i)+cur)) % MOD;
    }
    F0R(i,10) if (tri[x].v[ind].nex[i] != -1) fill(l,x,tri[x].v[ind].nex[i],cur+char('0'+i));
}

void solve(int x) {
    tot[x].v.pb(node(1));
    for (int i: child[x]) {
        solve(i);
        comb(tot[x],tri[i],0,0);
    }
    fill(tot[x],x,0,"");
} 

/////////// OK
void init() {
    freopen("code.in","r",stdin);
    freopen("code.out","w",stdout);
    
    cin >> N >> M; 
    FOR(i,1,N) {
        cin >> p[i];
        child[p[i]].pb(i);
    }
    F0R(i,N) tri[i].v.pb(node(0)), bad[i].v.pb(node(0));
    F0R(i,M) {
        int v; string s; cin >> v >> s;
        bad[v].ins(s);
        
        F0R(j,5) { 
            s = s.substr(1,s.length()-1);
            tri[v].ins(s);
            v = p[v];
        }
    }
} 

int main() {
    init();
    solve(0);
    cout << (po(10,N)-tri[0].v[0].val+MOD)%MOD;
}