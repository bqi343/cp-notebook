# Template Notes

- The header files will not compile with clang; use gcc instead.
- If you don't know what the following line does, see Range Queries --> README --> C++ STL for more information.

```cpp
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
```

# Pragma Optimization

  * [Explanation](https://codeforces.com/blog/entry/54682?#comment-387553)
  * Problems
    * [Nagini](https://codeforces.com/contest/855/submission/47823825)
    * [Welcome home, Chtholly](https://codeforces.com/contest/896/submission/47824007)

# Snippets

TopCoder:

[New Java Applet](https://codeforces.com/blog/entry/64597) (use ctrl-c instead of command-c on mac ...)

```
class C {
    public:
        int m() {

        }
};

int main() {
    setIO();
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
