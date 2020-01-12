# Template Notes

- The header files will not compile with clang; use gcc instead.

# Snippets

TopCoder:

[New Java Applet](https://codeforces.com/blog/entry/64597) (use ctrl-c instead of command-c on mac ...)

```
class C {
	public:
		void gen(int seed) {
			ll state = seed;
			while (1) {
				state = (state * 1103515245 + 12345) % (1LL<<31);
				
			}
		}
		int m() {
			
		}
};

int main() {
	C c; ps(c.m());
}
```

Google Kickstart / Facebook Hacker Cup

```
int N;

void inp(vi& v) { // common way to reduce amount of input
	v.rsz(1); ll A,B,C; re(v,A,B,C);
	while (sz(v) < N) v.pb((A*v.back()+B)%C+1);
}

void solve(int caseNum) {
	cerr << "Doing #" << caseNum << "\n";

}

int main() {
	// setIO("A");
	int T; re(T);
	FOR(i,1,T+1) {
		pr("Case #",i,": ");
		solve(i);
	}
}
```
