#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define f first
#define s second

const int MOD = 1e9+7; 

void setIO(string s) {
  ios_base::sync_with_stdio(0); cin.tie(0); 
  freopen((s+".in").c_str(),"r",stdin);
  freopen((s+".out").c_str(),"w",stdout);
}
 
struct mi {
  int v; explicit operator int() const { return v; }
  mi(ll _v) : v(_v%MOD) { v += (v<0)*MOD; }
  mi() : mi(0) {}
};
mi operator+(mi a, mi b) { return mi(a.v+b.v); }
mi operator-(mi a, mi b) { return mi(a.v-b.v); }
mi operator*(mi a, mi b) { return mi((ll)a.v*b.v); }
 
vector<pair<int,int>> v;
mi res;
int N,K;

typedef array<mi,11> T; 
// set of size t corresponds to x^t in polynomial
// store k-th derivatives of polynomial f(x)
// what happens when polynomial is multiplied by x:
  // (xf(x))’=f(x)+xf’(x)
  // (xf(x))’’=2f’(x)+xf’’(x)
  // (xf(x))’’’=3f’’(x)+xf’’’(x)

mi cum[11][11];
 
T seg[1<<18];
mi lazy[1<<18];
 
vector<int> y = {0};
 
void push(int ind, int L, int R) {
  if (lazy[ind].v == 1) return;
  for (int i = 0; i <= K; ++i) seg[ind][i] = seg[ind][i]*lazy[ind];
  if (L != R) {
    lazy[2*ind] = lazy[2*ind]*lazy[ind];
    lazy[2*ind+1] = lazy[2*ind+1]*lazy[ind];
  }
  lazy[ind] = 1;
}
 
void mul(int pos, int ind, int L, int R) {
  push(ind,L,R);
  if (pos > R) return;
  if (pos <= L) {
    lazy[ind] = 2;
    push(ind,L,R);
    return;
  }
  int M = (L+R)/2;
  mul(pos,2*ind,L,M); mul(pos,2*ind+1,M+1,R);
  for (int i = 0; i <= K; ++i) seg[ind][i] = seg[2*ind][i]+seg[2*ind+1][i];
}
 
void upd(int pos, const T& val, int ind, int L, int R) {
  push(ind,L,R);
  if (pos < L || pos > R) return;
  for (int i = 0; i <= K; ++i) seg[ind][i] = seg[ind][i]+val[i];
  if (L == R) return;
  int M = (L+R)/2;
  if (pos <= M) upd(pos,val,2*ind,L,M);
  else upd(pos,val,2*ind+1,M+1,R);
}
 
void query(int lo, int hi, T& t, int ind, int L, int R) {
  push(ind,L,R);
  if (hi < L || lo > R) return;
  if (lo <= L && R <= hi) { 
    for (int i = 0; i <= K; ++i) t[i] = t[i]+seg[ind][i]; 
    return; 
  }
  int M = (L+R)/2;
  query(lo,hi,t,2*ind,L,M); query(lo,hi,t,2*ind+1,M+1,R);
}
 
void ad(int a, int b) {
  auto i1 = lower_bound(begin(y),end(y),a)-begin(y)-1;
  auto i2 = lower_bound(begin(y),end(y),b)-begin(y);
  T A = T(); query(0,i1,A,1,0,N); 
  for (int i = K; i > 0; --i) A[i] = A[i]+i*A[i-1];
  T B = T(); query(i1+1,i2,B,1,0,N); 
  for (int i = 0; i <= K; ++i) A[i] = A[i]+B[i];
  upd(i2,A,1,0,N);
  mul(i2+1,1,0,N);
}

mi part[11][11];

int main() {
  setIO("help");
  for (int i = 1; i < (1<<18); ++i) lazy[i] = 1;
  cin >> N >> K; v.resize(N); 
  for (auto& t: v) {
    cin >> t.f >> t.s;
    y.push_back(t.s);
  }
  sort(begin(v),end(v)); sort(begin(y),end(y));
  T ori = T(); ori[0] = 1;
  upd(0,ori,1,0,N);
  for (auto t: v) ad(t.f,t.s);
  T res = T(); query(0,N,res,1,0,N);
  part[0][0] = 1;
  for (int i = 0; i < K; ++i) for (int j = 0; j <= i; ++j) {
    part[i+1][j] = part[i+1][j]+j*part[i][j];
    part[i+1][j+1] = part[i+1][j+1]+part[i][j];
  }
  mi ans = 0;
  /*for (int i = 0; i <= K; ++i) 
    cout << res[i].v << " ";
  cout << "\n";*/
  /*for (int i = 0; i <= K; ++i) 
    cout << part[K][i].v << " ";
  cout << "\n";*/
  for (int i = 0; i <= K; ++i) 
    ans = ans+res[i]*part[K][i];
  cout << ans.v << "\n";
}