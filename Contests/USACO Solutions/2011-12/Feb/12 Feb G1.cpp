/*#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>*/
#include <bits/stdc++.h>

using namespace std;
//using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int MOD = 1000000007;
double PI = 4*atan(1);

int N,K;
ll M;
vector<pi> cow;
set<pi> cou, pri;
pi p1, p2;
ll c1, c2;
int num = 0, ans = 0;

bool comp(pi a, pi b) {
    return a.f-a.s > b.f-b.s;
}

void init() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> N >> K >> M;
	F0R(i,N) {
	    int P,C; cin >> P >> C;
	    cow.pb({P,C});
	}
	sort(cow.begin(),cow.end(),comp);
	F0R(i,N) cou.insert({cow[i].s,i});
}

void rem(int ind) {
    pi tmp = {cow[ind].s,ind};
    if (tmp <= p1) {
        c1 -= tmp.f;
        p1 = *next(cou.find(p1));
        c1 += p1.f;
    }
    cou.erase(tmp);
}

void ad(int ind) {
    pi tmp = {cow[ind].f,ind};
    if (tmp <= p2) c2 += tmp.f, num ++;
    pri.insert(tmp);
    while (c1+c2 > M) {
        c2 -= p2.f;
        p2 = *prev(pri.find(p2));
        num --;
    }
    while (c1+c2 < M && next(pri.find(p2)) != pri.end()) {
        pi tmp = *next(pri.find(p2));
        if (c1+c2+tmp.f > M) break;
        num ++;
        c2 += tmp.f;
        p2 = tmp;
    }
}

int main() {
    init();
	int co = 0;
	for (auto a: cou) {
	    c1 += a.f, co++, p1 = a;
	    if (co == K) break;
	    if (c1 > M) {
	        cout << co-1;
	        return 0;
	    }
	}
	ans = K;
	
	pri.insert({0,0});
	for (int i = N-1; i >= K; --i) {
	    rem(i);
	    if (c1 > M) break;
	    ad(i);
	    ans = max(ans,num+K);
	}
	cout << ans;
}
