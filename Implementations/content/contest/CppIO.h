/**
 * Description: convenient functions for input / output
 * Source: 
	* https://codeforces.com/blog/entry/65311
	* https://codeforces.com/blog/entry/68809 (tests)
	* https://codeforces.com/blog/entry/5217 (input speed)
	* https://codeforces.com/contest/1305/submission/72346555 (tourist)
 * Verification: http://codeforces.com/contest/1045/problem/D
 */

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
template<class A> void re(vector<A>& x) { trav(a,x) re(a); }
template<class A, size_t SZ> void re(array<A,SZ>& x) { trav(a,x) re(a); }

// TO_STRING
#define ts to_string
template<class A, class B> str ts(pair<A,B> p);
template<class A> str ts(complex<A> c) { return ts(mp(c.real(),c.imag())); }
str ts(bool b) { return b ? "true" : "false"; }
str ts(char c) { str s = ""; s += c; return s; }
str ts(str s) { return s; }
str ts(const char* s) { return (str)s; }
str ts(vector<bool> v) { 
	bool fst = 1; str res = "{";
	F0R(i,sz(v)) {
		if (!fst) res += ", ";
		fst = 0; res += ts(v[i]);
	}
	res += "}"; return res;
}
template<size_t SZ> str ts(bitset<SZ> b) {
	str res = ""; F0R(i,SZ) res += char('0'+b[i]);
	return res; }
template<class T> str ts(T v) {
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
	cerr << to_string(h); if (sizeof...(t)) cerr << ", ";
	DBG(t...); }
#ifdef LOCAL // compile with -DLOCAL
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#else
#define dbg(...) 42
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