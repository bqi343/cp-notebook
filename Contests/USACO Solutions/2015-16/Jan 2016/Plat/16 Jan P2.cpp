#include <iostream>
#include <fstream>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace __gnu_pbds;
using namespace std;
 
typedef pair<int,int> pi;
 
#define F0R(i, a) for (int i=0; i<a; i++)
#define f first
#define s second
#define pb push_back
 
int N,T,nex=0;
tree<pi,null_type,less<pi>,rb_tree_tag,tree_order_statistics_node_update> s[100001];
long long ans = 0;
vector<pair<pi,pi>> vquery, hseg;
// x-coordinate, time, low y, high y
// x-coordinate, insert/delete, time, y

void updb (int num, int pos, int inc) {
    while (num <= N) {
        if (inc == 1) s[num].insert({pos,nex++});
        else s[num].erase(s[num].lower_bound({pos,0}));
        num += (num & -num);
    }
}

int queryb(int mnum, int mpo) {
    int z = 0;
    while (mnum) {
        z += s[mnum].order_of_key({mpo+1,0});
        mnum -= (mnum & -mnum);
    }
    return z;
}
 
void init() {
    // ifstream cin ("mowing.in");
    cin >> N >> T;
    int x0, y0;
    F0R(i,N) {
    	int x,y; cin >> x >> y;
    	if (i) {
    		if (x == x0) vquery.pb({{x,i},{min(y,y0)+1,max(y,y0)-1}});
    		else if (min(x,x0)+1 != max(x,x0)) {
    			hseg.pb({{min(x,x0)+1,1},{i,y}});
    			hseg.pb({{max(x,x0),-1},{i,y}});
    		}
    	}
    	x0 = x, y0 = y;
    }
    sort(hseg.begin(),hseg.end());
    sort(vquery.begin(),vquery.end());
}
 
int main() {
    //ofstream cout ("mowing.out");
    init();
    int ind = -1;
    for (auto a: vquery) {
    	while ((ind+1) < hseg.size() && hseg[ind+1].f.f <= a.f.f) {
    		ind++;
    		updb(hseg[ind].s.f,hseg[ind].s.s,hseg[ind].f.s);
    	}
    	if (a.f.s+T<N) {
    		ans += (queryb(N-1,a.s.s)-queryb(N-1,a.s.f-1));
    		ans -= (queryb(a.f.s+T-1,a.s.s)-queryb(a.f.s+T-1,a.s.f-1));
    	}
    	if (a.f.s>T)
    		ans += (queryb(a.f.s-T,a.s.s)-queryb(a.f.s-T,a.s.f-1));
    }
    cout << ans;
}
