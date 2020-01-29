# Snippets

## TC

```
struct Name {
	void gen(int seed) {
		ll state = seed;
		while (1) {
			state = (state * 1103515245 + 12345) % (1LL<<31);
			
		}
	}
	int method() {
		return 5;
	}
};

int main() {
	Name c; ps(c.method());
}
```

## FHC

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