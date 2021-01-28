// https://acm.timus.ru/problem.aspx?space=1&num=1653

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef double db; 
typedef string str; 

typedef pair<int,int> pi;
typedef pair<ll,ll> pl; 
typedef pair<db,db> pd; 

typedef vector<int> vi; 
typedef vector<ll> vl; 
typedef vector<db> vd; 
typedef vector<str> vs; 
typedef vector<pi> vpi;
typedef vector<pl> vpl; 
typedef vector<pd> vpd; 

#define mp make_pair
#define f first
#define s second
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rall(x) (x).rbegin(), (x).rend() 
#define rsz resize
#define ins insert 
#define ft front() 
#define bk back()
#define pf push_front 
#define pb push_back
#define eb emplace_back 
#define lb lower_bound 
#define ub upper_bound 

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define each(a,x) for (auto& a: x)

const int MOD = 1e9+7; // 998244353;
const int MX = 2e5+5; 
const ll INF = 1e18; 
const ld PI = acos((ld)-1);
const int xd[4] = {1,0,-1,0}, yd[4] = {0,1,0,-1}; 
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count()); 

template<class T> bool ckmin(T& a, const T& b) { 
	return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { 
	return a < b ? a = b, 1 : 0; } 
constexpr int pct(int x) { return __builtin_popcount(x); } 
constexpr int bits(int x) { return 31-__builtin_clz(x); } // floor(log2(x)) 
constexpr int cdiv(int a, int b) { return a/b+!(a<0||a%b == 0); } // division of a by b rounded up, assumes b > 0 
int fstTrue(function<bool(int)> f, int lo, int hi) {
	hi ++; assert(lo <= hi); // assuming f is increasing
	while (lo < hi) { // find first index such that f is true 
		int mid = (lo+hi)/2; 
		f(mid) ? hi = mid : lo = mid+1; 
	} 
	return lo;
}
template<class T> void remDup(vector<T>& v) { 
	sort(all(v)); v.erase(unique(all(v)),end(v)); }

// INPUT
template<class A> void re(complex<A>& c);
template<class A, class B> void re(pair<A,B>& p);
template<class A> void re(vector<A>& v);
template<class A, size_t SZ> void re(array<A,SZ>& a);

template<class T> void re(T& x) { cin >> x; }
void re(db& d) { str t; re(t); d = stod(t); }
void re(ld& d) { str t; re(t); d = stold(t); }
template<class H, class... T> void re(H& h, T&... t) { re(h); re(t...); }

template<class A> void re(complex<A>& c) { A a,b; re(a,b); c = {a,b}; }
template<class A, class B> void re(pair<A,B>& p) { re(p.f,p.s); }
template<class A> void re(vector<A>& x) { each(a,x) re(a); }
template<class A, size_t SZ> void re(array<A,SZ>& x) { each(a,x) re(a); }

// TO_STRING
#define ts to_string
str ts(char c) { return str(1,c); }
str ts(bool b) { return b ? "true" : "false"; }
str ts(const char* s) { return (str)s; }
str ts(str s) { return s; }
template<class A> str ts(complex<A> c) { 
	stringstream ss; ss << c; return ss.str(); }
str ts(vector<bool> v) { 
	str res = "{"; F0R(i,sz(v)) res += char('0'+v[i]);
	res += "}"; return res; }
template<size_t SZ> str ts(bitset<SZ> b) {
	str res = ""; F0R(i,SZ) res += char('0'+b[i]);
	return res; }
template<class A, class B> str ts(pair<A,B> p);
template<class T> str ts(T v) { // containers with begin(), end()
	bool fst = 1; str res = "{";
	for (const auto& x: v) {
		if (!fst) res += ", ";
		fst = 0; res += ts(x);
	}
	res += "}"; return res;
}
template<class A, class B> str ts(pair<A,B> p) {
	return "("+ts(p.f)+", "+ts(p.s)+")"; }

// OUTPUT
template<class A> void pr(A x) { cout << ts(x); }
template<class H, class... T> void pr(const H& h, const T&... t) { 
	pr(h); pr(t...); }
void ps() { pr("\n"); } // print w/ spaces
template<class H, class... T> void ps(const H& h, const T&... t) { 
	pr(h); if (sizeof...(t)) pr(" "); ps(t...); }

// DEBUG
void DBG() { cerr << "]" << endl; }
template<class H, class... T> void DBG(H h, T... t) {
	cerr << ts(h); if (sizeof...(t)) cerr << ", ";
	DBG(t...); }
#ifdef LOCAL // compile with -DLOCAL
#define dbg(...) cerr << "LINE(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#else
#define dbg(...) 0
#endif

// FILE I/O
void setIn(string s) { freopen(s.c_str(),"r",stdin); }
void setOut(string s) { freopen(s.c_str(),"w",stdout); }
void unsyncIO() { ios_base::sync_with_stdio(0); cin.tie(0); }
void setIO(string s = "") {
	unsyncIO();
	// cin.exceptions(cin.failbit); 
	// throws exception when do smth illegal
	// ex. try to read letter into int
	if (sz(s)) { setIn(s+".in"), setOut(s+".out"); } // for USACO
}

/**
 * Description: Operations on quaternions, useful for totations in 3D
 * Source: https://codeforces.com/blog/entry/46744
 * Verification:
 	* https://codeforces.com/gym/102354/problem/F
	* https://codeforces.com/contest/1375/problem/I
 */

using T = ld; const T EPS = 1e-9;
int sgn(T x) { return (x>0)-(x<0); }
T sq(T x) { return x*x; }
 
/////// DEFINING QUATER
using Q = array<T,4>; using vQ = vector<Q>; // represent quater as (x,y,z,s)
Q vec(T x, T y, T z) { return {x,y,z,0}; } // vector to quater
Q vec(Q a) { a[3] = 0; return a; } // quater to vector
void isVec(const Q& q) { assert(q[3] == 0); } // assert that quater is vector
const Q ex = vec(1,0,0), ey = vec(0,1,0), ez = vec(0,0,1); // unit vectors for each of three axes
Q conj(Q x) { F0R(i,3) x[i] *= -1; // conjugate
	return x; }
Q ortho(const Q& x) { isVec(x); // return any nonzero vector perpendicular to q
	return abs(x[1]) > EPS ? vec(x[1],-x[0],0) : vec(x[2],0,-x[0]); }
Q vrand() { // random vector
	Q q = Q(); F0R(i,3) q[i] = rng()%(2*MOD)-MOD;
	return q; }
T norm(const Q& x) { // sum of squares
	T sum = 0; each(t,x) sum += t*t;
	return sum; }
T abs(const Q& x) { return sqrt(norm(x)); }

/////// BASIC ARITHMETIC
Q& operator+=(Q& l, const Q& r) { F0R(i,4) l[i] += r[i]; 
	return l; }
Q& operator-=(Q& l, const Q& r) { F0R(i,4) l[i] -= r[i]; 
	return l; }
Q& operator*=(Q& l, const T& r) { F0R(i,4) l[i] *= r; 
	return l; }
Q& operator/=(Q& l, const T& r) { F0R(i,4) l[i] /= r; 
	return l; }
Q operator-(Q l) { return l *= -1; }
Q operator+(Q l, const Q& r) { return l += r; }
Q operator-(Q l, const Q& r) { return l -= r; }
Q operator*(Q l, const T& r) { return l *= r; }
Q operator*(const T& r, const Q& l) { return l*r; }
Q operator/(Q l, const T& r) { return l /= r; }
Q unit(Q x) { return x/abs(x); }
Q inv(const Q& x) { return conj(x)/norm(x); }
bool eq(Q a, Q b) { return abs(a-b) < EPS; }

Q operator*(const Q& x, const Q& y) { Q z = Q(); // multiply quaters
	F0R(i,4) F0R(j,4) // i=3 or j=3 -> multiplying by constant, just add product
		z[i^j^3] += ((i==3||j==3||(i+1)%3 == j)?1:-1)*x[i]*y[j];
	return z; }
Q operator/(const Q& l, const Q& r) { return l*inv(r); }
Q& operator*=(Q& l, const Q& r) { return l = l*r; }
Q& operator/=(Q& l, const Q& r) { return l = l/r; }

T dot(const Q& l, const Q& r) { isVec(l), isVec(r); // dot product of vectors
	T res = 0; F0R(i,3) res += l[i]*r[i];
	return res; }
Q cross(const Q& l, const Q& r) { isVec(l), isVec(r); // cross product of vectors
	return vec(l*r); }
T mix(const Q& a, const Q& b, const Q& c) { isVec(a), isVec(b), isVec(c);
	return dot(a,cross(b,c)); } // mixed product

// rotating phi about axis i -> rotation quater is in the form rot=cos(phi/2)+i*sin(phi/2)
Q rotate(const Q& rot, const Q& x) { isVec(x); 
	return vec(rot*x/rot); } // rot doesn't have to be normalized
Q minRotation(const Q& a, const Q& b) { isVec(a), isVec(b); // min rotation from a to b, both a and b should be unit
	return eq(a,-b) ? ortho(b) : (a+b)*a; } // if a == -b then infinitely many possible ...
T getAngle(const Q& a) { return remainder(2*acos(a[3]/abs(a)),2*PI); }  // get phi
Q basisRotation(const Q& a, const Q& b) { isVec(a), isVec(b); // bring ex to a and ey to b
	Q ra = minRotation(ex,a); Q EY = rotate(ra,ey); // first rotate ex to a
	Q rb = eq(EY,-b) ? a : minRotation(EY,b); // then rotate ey to b
	return rb*ra; }
Q basisRotation(const Q& a, const Q& b, const Q& A, const Q& B) { // rotation that brings a to A and b to B
	return basisRotation(A,B)/basisRotation(a,b); } // a -> ex -> A, b -> ey -> B

/////// EIGENBASIS of positive semidefinite matrix, use for PCA
// eigenvectors for different eigenvalues are orthogonal
// https://en.wikipedia.org/wiki/Definite_symmetric_matrix
// https://en.wikipedia.org/wiki/Principal_component_analysis
typedef array<array<T,3>,3> Mat;
Q operator*(const Mat& l, const Q& r) { isVec(r); // multiply matrix by vector
	Q res = Q(); F0R(i,3) F0R(j,3) res[i] += l[i][j]*r[j];
	return res; }
Q flatten(const vQ& basis, Q x) { isVec(x); // reduce x given orthonormal basis
	each(t,basis) x -= t*dot(t,x);
	return unit(x); }
Q findEigenvec(const vQ& basis, const Mat& A) { // if we keep applying it will converge to vector corresponding to largest eigenvalue
	Q x = flatten(basis,vrand());
	F0R(_,1e5) {
		Q X = A*x; if (abs(X) < EPS) return x; // eigenvalue 0?
		x = flatten(basis,X);
	}
	return x;
}
vQ eigenBasis(const Mat& A) { 
	vQ basis; F0R(z,3) basis.pb(findEigenvec(basis,A));
	return basis; }

/////// GCD of Hurwitz Quaternions
// https://en.wikipedia.org/wiki/Hurwitz_quaternion
// all coordinates are integer or all coordinates are half-integer
// multiples of Hurwitz quater a are in the form a*v
Q round(const Q& q) { Q a, b; // get closest Hurwitz quaternion
	F0R(i,4) a[i] = round(q[i]); // try int
	F0R(i,4) b[i] = round(q[i]-0.5)+0.5; // and half-int
	return norm(a-q) < norm(b-q) ? a : b; }
Q operator%(const Q& a, const Q& b) { return a-b*round(inv(b)*a); }
Q gcd(Q a, Q b) { if (norm(a) > norm(b)) swap(a,b);
	return norm(a) == 0 ? b : gcd(b%a,a); }

vQ verts;
str shape;
int n;
Q tot{0,0,0,1};
const T phi = (1+sqrt((ld)5.0))/2;

Q pos(int x) { return rotate(tot,verts[x]); }

// so useful!! http://eusebeia.dyndns.org/4d/dodecahedron

void init() {
	setIO(); re(shape,n);
	if (shape == "tetrahedron") {
		verts.pb(vec(1,1,1));
		verts.pb(vec(-1,-1,1));
		verts.pb(vec(-1,1,-1));
		verts.pb(vec(1,-1,-1));
	} else if (shape == "hexahedron") {
		for (int a:{-1,1}) for (int b:{-1,1}) for (int c:{-1,1})
			verts.pb(vec(a,b,c));
	} else if (shape == "octahedron") {
		for (int a:{-1,1}) {
			verts.pb(vec(a,0,0));
			verts.pb(vec(0,a,0));
			verts.pb(vec(0,0,a));
		}
	} else if (shape == "dodecahedron") {
		for (int a:{-1,1}) for (int b:{-1,1}) for (int c:{-1,1})
			verts.pb({a*phi,b*phi,c*phi});
		for (int a:{-1,1}) for (int b:{-1,1}) {
			T A = 0, B = a*phi*phi, C = b;
			verts.pb({A,B,C});
			verts.pb({B,C,A});
			verts.pb({C,A,B});
		}
	} else if (shape == "icosahedron") {
		for (int a:{-1,1}) for (int b:{-1,1}) {
			T A = 0, B = a, C = b*phi;
			verts.pb({A,B,C});
			verts.pb({B,C,A});
			verts.pb({C,A,B});
		}
	} else exit(5);
	T mag = abs(verts[0]);
	each(t,verts) {
		t /= mag;
		assert(abs(abs(t)-1) < EPS);
	}
	tot = minRotation(verts[0],vec(0,0,1));
	int ind = 1;
	FOR(i,1,sz(verts)) if (abs(verts[i]-verts[0]) < abs(verts[ind]-verts[0])) ind = i;
	swap(verts[1],verts[ind]);
	Q q = pos(1);
	T ang = -atan2(q[1],q[0]);
	tot = Q{0,0,sin(ang/2),cos(ang/2)}*tot;
	F0R(i,2) dbg(i,pos(i));
	//dbg(pos(1));
	// initialize rotation
}

int main() {
	init(); 
	T ans = 0;
	F0R(i,n) {
		T x,y,z; re(x,y,z);
		Q q = vec(x,y,z); q /= abs(q); q *= -1;
		pair<T,int> bes = {INF,-1};
		F0R(i,sz(verts)) {
			T d = abs(pos(i)-q);
			ckmin(bes,{d,i});
		}
		dbg(pos(bes.s),q);
		Q rot = minRotation(pos(bes.s),q);
		T ang = getAngle(rot); 
		if (abs(ang+2*PI) < abs(ang)) ang += 2*PI;
		if (abs(ang-2*PI) < abs(ang)) ang -= 2*PI;
		ans += abs(ang);
		tot = rot*tot;
	}
	cout << fixed << setprecision(5) << ans << "\n";
	// you should actually read the stuff at the bottom
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/

