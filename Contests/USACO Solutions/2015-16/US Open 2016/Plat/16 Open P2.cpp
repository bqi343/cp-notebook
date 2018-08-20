#include<bits/stdc++.h>
  
using namespace std;
  
#define FOR(i, a, b) for (int i=a; i<int(b); i++)
#define F0R(i, a) for (int i=0; i<int(a); i++)
 
#define pb push_back
#define f first
#define s second
#define mp make_pair
 
typedef vector<string> mat;
typedef pair<int,int> pi;
typedef vector<short> vi;
typedef long long ll;
  
const pi MOD = {975919579,975979579};
pi M1[1000], M2[1000];
int K,N,M;
clock_t b;
set<vi> ans;
 
pi operator*(const pi& l, const int& r) {
    return mp(1LL*l.f*r % MOD.f,1LL*l.s*r % MOD.s);
}
pi operator*(const pi& l, const pi& r) {
    return mp(1LL*l.f*r.f % MOD.f,1LL*l.s*r.s % MOD.s);
}
pi operator+(const pi& l, const pi& r) {
    return mp((l.f+r.f)%MOD.f,(l.s+r.s)%MOD.s);
}
pi operator-(const pi& l, const pi& r) {
    return mp((l.f-r.f+MOD.f)%MOD.f,(l.s-r.s+MOD.s)%MOD.s);
}
vi operator+(const vi& l, const vi& r) {
    vi c(26);
    F0R(i,26) c[i] = l[i]+r[i];
    return c;
}
 
void print(mat& x) {
    F0R(i,x.size()) {
        F0R(j,x[i].size()) cout << x[i][j];
        cout << "\n";
    }
}
 
struct figure {
    pi hsh, lef;
    vi cnt;
    vector<vi> sum_table;
    figure() {}
    figure (mat& d) {
        sum_table.resize(d.size()); F0R(i,d.size()) sum_table[i].resize(d[0].size());
         
        cnt.resize(26); hsh = mp(0,0);
        lef = mp(-1,-1);
         
        int lst = 0;
        F0R(i,d.size()) F0R(j,d[i].size()) {
            if (d[i][j] != '.') {
                hsh = hsh+M1[i]*M2[j]*(26+int(d[i][j]-'a'));
                lst++;
                cnt[d[i][j]-'a'] ++;
                if (lef == mp(-1,-1)) lef = mp(i,j);
            }
            sum_table[i][j] = lst;
        }
    }
};
 
figure target;
figure fig[800];
 
void vflip(mat& x) {
    F0R(i,x.size()/2) swap(x[i],x[x.size()-1-i]);
}
 
void rotate(mat& x) {
    mat x1; x1.resize(x[0].size());
    F0R(i,x[0].size()) x1[i].resize(x.size());
    F0R(a,x.size()) F0R(b,x[0].size()) x1[x[0].size()-1-b][a] = x[a][b];
    x = x1;
}
 
bool emp(string& x) {
    for (char i: x) if (i != '.') return 0;
    return 1;
}
 
bool EMP(mat& x, int ind) {
    F0R(i,x.size()) if (x[i][ind] != '.') return 0;
    return 1;
}
 
void REM(mat& x, int ind) {
    F0R(i,x.size()) x[i].erase(x[i].begin()+ind);
}
 
void cut(mat& x) {
    while (x.size() > 0 && emp(x[x.size()-1])) x.erase(x.end()-1);
    while (x.size() > 0 && emp(x[0])) x.erase(x.begin());
    while (x.size() > 0 && EMP(x,x[0].size()-1)) REM(x,x[0].size()-1);
    while (x.size() > 0 && EMP(x,0)) REM(x,0);
}
 
mat read() {
    int R,C; cin >> R >> C;
    mat tmp(R);
    char x;
    F0R(j,R) F0R(k,C) {
        cin >> x;
        tmp[j].pb(x);
    }
    cut(tmp);
    return tmp;
}
 
void init() {
    freopen("bcs.in","r",stdin);
    freopen("bcs.out","w",stdout);
     
    ios_base::sync_with_stdio(0); cin.tie(0);
    M1[0] = M2[0] = {1,1};
    FOR(i,1,1000) M1[i] = M1[i-1]*849382918;
    FOR(i,1,1000) M2[i] = M2[i-1]*118398428;
     
    cin >> K;
    mat r = read(); target = figure(r);
    N = target.sum_table.size(), M = target.sum_table[0].size();
     
    int nex = 0;
    F0R(i,K) {
        mat r = read();
        F0R(i,4) {
            fig[nex++] = figure(r);
            rotate(r);
        }
        vflip(r);
        F0R(i,4) {
            fig[nex++] = figure(r);
            rotate(r);
        }
    }
}
 
pi shift(int x, pi pos) {
    return fig[x].hsh*M1[pos.f]*M2[pos.s];
}
 
int get(pi pos, int x) {
    int N = fig[x].sum_table.size(), M = fig[x].sum_table[0].size();
    if (pos.s < 0) pos.f--, pos.s = M-1;
    else if (pos.s >= M) pos.s = M-1;
     
    if (pos.f >= N) pos.f = N-1, pos.s = M-1;
    if (pos.f < 0) return 0;
    return fig[x].sum_table[pos.f][pos.s];
}
 
pi get_offset(int num, vi A, vector<pi> B) {
    int lo = 0, hi = N*M-1;
    while (lo < hi) {
        int mid = (lo+hi)/2;
        int x = mid/M, y = mid%M;
        short tot = target.sum_table[x][y];
        F0R(i,A.size()) tot -= get(mp(x-B[i].f,y-B[i].s),A[i]);
        if (tot != 0) hi = mid;
        else lo = mid+1;
    }
    return mp(lo/M-fig[num].lef.f,lo%M-fig[num].lef.s);
}
 
bool ok(vi a) {
    pi p0 = get_offset(a[0],{},{});
    if (p0.f < 0 || p0.s < 0) return 0;
    pi p1 = get_offset(a[1],{a[0]},{p0});
    if (p1.f < 0 || p1.s < 0) return 0;
    pi p2 = get_offset(a[2],{a[0],a[1]},{p0,p1});
    if (p2.f < 0 || p2.s < 0) return 0;
    return shift(a[0],p0)+shift(a[1],p1)+shift(a[2],p2) == target.hsh;
}
 
int main() {
    init();
    
    F0R(i,K) F0R(j,K) F0R(k,K) {
        if (i == j || j == k || i == k) continue;
        if (fig[8*i].cnt+fig[8*j].cnt+fig[8*k].cnt == target.cnt) {
            vi a1 = {i,j,k}; sort(a1.begin(),a1.end());
            if (ans.find(a1) != ans.end()) continue;
            bool z = 0;
            F0R(i1,8) {
                F0R(j1,8) {
                    F0R(k1,8) 
                        if(ok({8*i+i1,8*j+j1,8*k+k1})) {
                            z = 1;
                            break;
                        }
                    if (z) break;
                }
                if (z) break;
            }
            if (z) ans.insert(a1);
        }
    }
    cout << ans.size();
}
