/**
* Source: http://codeforces.com/blog/entry/51275?#comment-351413
* Unused
*/

const int N = 100000 + 5;

int n, m;
int vis[N << 1];
char op[100];

struct line {
    double k, b;
    line(double _k = 0, double _b = 0) { k = _k; b = _b; }
    double get(double x) { return k * x + b; }
} c[N << 1];

void modify(int x, int l, int r, line v) {
    if (!vis[x]) { vis[x] = 1, c[x] = v; return; }
    if (c[x].get(l) > v.get(l) && c[x].get(r) > v.get(r)) return;
    if (c[x].get(l) < v.get(l) && c[x].get(r) < v.get(r)) { c[x] = v; return;}
    int m = (l + r) >> 1;
    if (c[x].get(l) < v.get(l)) swap(c[x], v);
    if (c[x].get(m) > v.get(m)) modify(x<<1|1, m + 1, r, v);
    else {swap(c[x], v); modify(x<<1, l, m, v);}
}

double get(int x, int l, int r, int pos) {
    if (l == r) return c[x].get(l);
    int m = (l + r) >> 1; double ans = c[x].get(pos);
    if (pos <= m) ans = max(ans, get(x<<1, l, m, pos));
    else ans = max(ans, get(x<<1|1, m + 1, r, pos));
    return ans;
}

int main() {
    cin >> n;
    F0R(i,n) {
        cin >> op;
        if (op[0] == 'Q') {
            int x; cin >> x;
            cout << get(1, 1, n, x) << "\n";
        } else {
            double k, b; cin >> b >> k;
            line l = line(k, b);
            modify(1, 1, n, l);
        }
    }
}