#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int SZ = 1<<17;

struct SegTree2D {
	vector<pair<int,pii>> node;
	
	SegTree2D () {
		node.resize(2*SZ);
	}
	
	void u(int ind, int x, int L = 1, int R = SZ) {
	    node[ind].f ++;
	    if (L == R) return;
	
	    int M = (L+R)/2;
	    if (x <= M) {
	        if (node[ind].s.f == 0) {
	            node[ind].s.f = node.size();
	            node.pb({0,{0,0}});
	        }
	        u(node[ind].s.f,x,L,M);
	    } else {
	        if (node[ind].s.s == 0) {
	            node[ind].s.s = node.size();
	            node.pb({0,{0,0}});
	        }
	        u(node[ind].s.s,x,M+1,R);
	    }
	} 
	
	int q(int ind, int lowx, int highx, int L = 1, int R = SZ) {
	    if (lowx <= L && R <= highx) return node[ind].f;
	    if (R < lowx || highx < L) return 0;
	    int z = 0, M = (L+R)/2;
	    
	    if (node[ind].s.f != 0) z += q(node[ind].s.f,lowx,highx,L,M);
	    if (node[ind].s.s != 0) z += q(node[ind].s.s,lowx,highx,M+1,R);
	    return z;
	} 
	
	void upd(int y, int x, int ind = 1, int L = 1, int R = SZ) {
	    u(ind,x);
	    if (L == R) return;
	    
	    int M = (L+R)/2;
	    if (y <= M) upd(y,x,2*ind,L,M);
	    else upd(y,x,2*ind+1,M+1,R);
	} 
	
	int query(int lowy, int highy, int lowx, int highx, int ind = 1, int L = 1, int R = SZ) {
	    if (highy < L || R < lowy) return 0;
	    if (lowy <= L && R <= highy) return q(ind,lowx,highx);
	    int M = (L+R)/2;
	    return query(lowy,highy,lowx,highx,2*ind,L,M)+query(lowy,highy,lowx,highx,2*ind+1,M+1,R);
	}
};

int main() {
	SegTree2D S;
	S.upd(7,5);
	cout << S.query(1,3,2,4) << " " << S.query(6,8,2,7);
}
