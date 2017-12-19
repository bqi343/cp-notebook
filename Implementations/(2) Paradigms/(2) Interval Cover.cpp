/**
* Source: own
* Usage: https://open.kattis.com/problems/intervalcover
*/

double A,B,cur;
vector<pair<pdd,int>> in;
int N,nex;
vi ans;

void solve() {
    nex = 0; ans.clear();
    cin >> N; in.resize(N);
    F0R(i,N) {
        cin >> in[i].f.f >> in[i].f.s;
        in[i].s = i;
    }
    
    sort(all(in));
    pair<double,int> mx = {-DBL_MAX,-1};
    
    while (nex < in.size() && in[nex].f.f <= A) {
        mx = max(mx,{in[nex].f.s,in[nex].s});
        nex++;
    }
    if (nex == 0) {
        cout << "impossible\n";
        return;
    }
    ans.pb(mx.s);
    
    while (mx.f < B) {
        cur = mx.f;
        while (nex < in.size() && in[nex].f.f <= cur) {
            mx = max(mx,{in[nex].f.s,in[nex].s});
            nex++;
        }
        if (mx.f == cur) {
            cout << "impossible\n";
            return;
        }
        ans.pb(mx.s);
    }
    cout << ans.size() << "\n";
    for (int i: ans) cout << i << " ";
    cout << "\n";
}