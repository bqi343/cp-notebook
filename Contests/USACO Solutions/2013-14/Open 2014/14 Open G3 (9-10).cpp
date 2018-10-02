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
 
const int MOD = 1234567;
 
struct node {
    array<int,10> nex, bad;
    int val;
    node() {
        val = 0;
        F0R(i,10) nex[i] = -1, bad[i] = 1;
    }
};

node v[750000];
int NEX = 0;

void ins(int cur, string x) {
    for (char i: x) {
        if (v[cur].nex[i-'0'] == -1) v[cur].nex[i-'0'] = NEX++;
        cur = v[cur].nex[i-'0'];
    }
}
 
bool fin(int cur, string x) {
    if (x.length() != 5) return 0;
    for (char i: x) {
        if (v[cur].nex[i-'0'] == -1) return 0;
        cur = v[cur].nex[i-'0'];
    }
    return 1;
}
 
int query(int ind, string cur) {
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
 
int N,M, p[20000];
vi child[20000];
int bad[20000], tri[20000], tot[20000];

ll po(ll b, ll z) {
    ll ans = 1;
    while (z) {
        if (z&1) ans = (ans*b) % MOD;
        b = b*b % MOD;
        z /= 2;
    }
    return ans;
}
 
void comb(int il, int ir) {
    v[il].val = ((ll)v[il].val*v[ir].val) % MOD;
    F0R(i,10) 
        if (v[ir].nex[i] != -1) {
            if (v[il].nex[i] == -1) {
                v[il].nex[i] = NEX;
                v[NEX++].val = 1;
            }
            comb(v[il].nex[i], v[ir].nex[i]);
        } else v[il].bad[i] = ((ll)v[il].bad[i]*v[ir].val) % MOD;
}
 
void fill(int l, int x, int ind, string cur) {
    F0R(i,10) if (!fin(bad[x],char('0'+i)+cur)) 
        v[ind].val = (v[ind].val+query(l,char('0'+i)+cur)) % MOD;
    F0R(i,10) if (v[ind].nex[i] != -1) fill(l,x,v[ind].nex[i],cur+char('0'+i));
}
 
void solve(int x) {
    v[tot[x]].val = 1;
    for (int i: child[x]) {
        solve(i);
        comb(tot[x],tri[i]);
    }
    fill(tot[x],x,tri[x],"");
} 
 
void init() {
    freopen("code.in","r",stdin);
    freopen("code.out","w",stdout);
     
    F0R(i,20000) {
        bad[i] = NEX++;
        tri[i] = NEX++;
        tot[i] = NEX++;
    }
    cin >> N >> M; 
    FOR(i,1,N) {
        cin >> p[i];
        child[p[i]].pb(i);
    }
    F0R(i,M) {
        int v; string s; cin >> v >> s;
        ins(bad[v],s);
         
        F0R(j,5) { 
            s = s.substr(1,s.length()-1);
            ins(tri[v],s);
            v = p[v];
        }
    }
} 
 
int main() {
    init();
    solve(0);
    cout << (po(10,N)-v[tri[0]].val+MOD)%MOD;
}
