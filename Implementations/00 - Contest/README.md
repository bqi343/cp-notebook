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

TopCoder (testing from web arena is inconvenient):

```
class C {
    public:
        int m() {

        }
};

int main() {
    C c; ps(c.m());
}
```

Google Kickstart

```
void solve(int caseNum) {

    cerr << "Solved #" << caseNum << "\n";
}

int main() {
    // setIO("A");
    int T; re(T);
    FOR(i,1,T+1) {
        pr("Case #",i,": ");
        solve(i);
        ps();
    }
}
```
