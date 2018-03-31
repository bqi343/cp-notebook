#include <bits/stdc++.h>

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

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

struct cow {
    int type;
    double slope;
    int x;
    int y;
    cow(int t, double s, int X, int Y) {
        type = t;
        slope = s;
        x = X;
        y = Y;
    }
};

struct cmp {
    bool operator()(const cow& a, const cow& b) {
        if (a.type+b.type == 0) {
            if (a.x != b.x) return a.x<b.x;
            return a.y<b.y;
        }
        return a.slope>b.slope;
    }
};

bool below(pi x, pi a1, pi a2) {
    return (ll)x.s*(a2.f-a1.f) <= (ll)a1.s*(a2.f-x.f)+(ll)a2.s*(x.f-a1.f); 
}

struct hull {
    set<cow,cmp> cows;
    
    bool rem(int x, int y) {
        cow tmp(0,0,x,-MOD);
        auto it = cows.lb(tmp);
        if (it != cows.end() && it->x == x) {
            if (it->y < y) cows.erase(it);
            else return 0;
        }
        return 1;
    }
    
    bool ir(int x, int y) {
        cow tmp(0,0,x,y);
        auto it = cows.lb(tmp);
        if (it == cows.end()) return 0;
        if (it == cows.begin()) return 0;
        if (below({x,y},{prev(it)->x,prev(it)->y},{it->x,it->y})) return 1;
        return 0;
    }
    
    void getslope(cow C) {
        if (next(cows.find(C)) == cows.end()) {
            cows.erase(C);
            C.slope = -1e18;
            cows.insert(C);
            return;
        }
        cow D = *next(cows.find(C));
        cows.erase(C);
        C.slope = double(D.y-C.y)/(D.x-C.x);
        cows.insert(C);
    }
    
    void ins(int x, int y) {
        if (!rem(x,y)) return;
        if (ir(x,y)) return;
        
        cow tmp(0,0,x,y);
        cows.insert(tmp);
        
        while (1) {
            auto it = cows.find(tmp);
            if (it == cows.begin() || prev(it) == cows.begin()) break;
            if (below({prev(it)->x,prev(it)->y},{prev(prev(it))->x,prev(prev(it))->y},{x,y})) cows.erase(prev(it));
            else break;
        }
        
        while (1) {
            auto it = cows.find(tmp);
            if (next(it) == cows.end() || next(next(it)) == cows.end()) break;
            if (below({next(it)->x,next(it)->y},{x,y},{next(next(it))->x,next(next(it))->y})) cows.erase(next(it));
            else break;
        }
        
        auto it = cows.find(tmp);
        if (it != cows.begin()) getslope(*prev(it));
        getslope(tmp);
    }
    
    pi get(double slope) {
        cow tmp(1,slope,0,0);
        auto it = cows.lb(tmp);
        return {it->x,it->y};
    }
} top, bottom;

int N,Q;

void ins(int x, int y) {
    top.ins(x,y);
    bottom.ins(-x,-y);
}

bool query(ll A, ll B, ll C) {
    double slope;
    if (B != 0) slope = (double)-A/B;
    else slope = 1e17;
    
    pi a = top.get(slope);
    pi b = bottom.get(slope);
    
    b.f *= -1, b.s *= -1;
    ll lo = a.f*A+a.s*B, hi = b.f*A+b.s*B;
    
    if (lo > hi) swap(lo,hi);
    if (lo <= C && C <= hi) return 0;
    return 1;
}

int main() {
    ifstream cin ("fencing.in");
    ofstream cout ("fencing.out");
    
	ios_base::sync_with_stdio(0);
	cin >> N >> Q;
	F0R(i,N) {
	    int x,y; cin >> x >> y;
	    ins(x,y);
	}
	
	F0R(i,Q) {
	    int t; cin >> t;
	    if (t == 1) {
	        int x,y; cin >> x >> y;
	        ins(x,y);
	    } else {
	        ll A,B,C; cin >> A >> B >> C;
	        if (query(A,B,C)) cout << "YES\n";
	        else cout << "NO\n";
	    }
	}
}

// read!
// ll vs. int!
