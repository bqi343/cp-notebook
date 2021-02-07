# Snippets

for sublime text 3

## TC

[ifdef](https://codeforces.com/blog/entry/50312?#comment-342457)

```
// make sure to INITIALIZE ARRAYS TO ZERO

struct ${1:Name} {
	void gen(int seed) {
		ll state = seed;
		while (1) {
			state = (state * 1103515245 + 12345) % (1LL<<31);
			
		}
	}
	int ${2:method}() {
		return 5;
	}
};

#ifdef LOCAL
int main() {
	clock_t beg = clock();
	${1:Name} c; ps(c.${2:method}());
	dbg((db)(clock()-beg)/CLOCKS_PER_SEC);
}
#endif
```

## FHC

```
// make sure to 
// * clear ALL GLOBAL VARS between tcs!
// * generate input correctly LOL

clock_t beg = clock();
int N,K;

// void inp(vi& v) {
// 	v.rsz(1); ll A,B,C; re(v,A,B,C);
// 	while (sz(v) < N) v.pb((A*v.bk+B)%C+1);
// }
void inp(vi& v) {
	v.rsz(K); ll A,B,C,D; re(v,A,B,C,D);
	while (sz(v) < N) v.pb(int((A*v[sz(v)-2]+B*v.bk+C)%D));
}

void solve(int tc) {
	cerr << "Doing TC #" << tc << " " << (db)(clock()-beg)/CLOCKS_PER_SEC << "\n";
	${0}
}

int main() {
	// setIO("A");
	int TC; re(TC);
	FOR(i,1,TC+1) {
		pr("Case #",i,": ");
		solve(i);
	}
}
```

## GCJ

```
// make sure to intialize ALL GLOBAL VARS between tcs!

clock_t beg = clock();

void solve(int tc) {
	// cerr << "Doing TC #" << tc << " " << (db)(clock()-beg)/CLOCKS_PER_SEC << "\n";
	${0}
}

int main() {
	setIO();
	int TC; re(TC);
	FOR(i,1,TC+1) {
		pr("Case #",i,": ");
		solve(i);
	}
}
```

## InG

```
re(N,M);
F0R(i,M) {
	int a,b; re(a,b);
	adj[a].pb(b), adj[b].pb(a);
}
```

## InT

```
re(N);
F0R(i,N-1) {
	int a,b; re(a,b);
	adj[a].pb(b), adj[b].pb(a);
}
```

## TS

```
// make sure to intialize ALL GLOBAL VARS between tcs!

void solve(int tc) {
	${0}
}

int main() {
	setIO();
	int TC; re(TC);
	FOR(i,1,TC+1) solve(i);
}
```

## lam

```
auto ${1:name} = [&](${2}) {
	${3}
};
```