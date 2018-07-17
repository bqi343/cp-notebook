/**
* Description: Example of greedy algorithm
* Verification: https://open.kattis.com/problems/intervalcover
    * actually, you need to account for A=B and add epsilons but w/e
*/

double A,B; // interval to be covered, assuming A<B
vector<pair<pd,int>> in; // intervals 
int N; // # of intervals 

vi solve() {
    pair<double,int> mx = {A,-1};
    vi ans;
    int nex = 0;
    
    sort(all(in));
    while (mx.f < B) {
        double cur = mx.f;
        while (nex < sz(in) && in[nex].f.f <= cur) 
            mx = max(mx,{in[nex].f.s,in[nex].s}), nex++;
        if (mx.f == cur) return {};
        ans.pb(mx.s);
    }
    
    return ans;
}
