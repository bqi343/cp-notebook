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

const int SZ = 100000;

struct SegTree2D {
	vector<pair<int,pii>> node;
	
	SegTree2D () {
		node.resize(SZ+1);
	}
	
	void u(int ind, int L, int R, int x) {
	    node[ind].f ++;
	    if (L == R) return;
	
	    int M = (L+R)/2;
	    if (x <= M) {
	        if (node[ind].s.f == 0) {
	            node[ind].s.f = node.size();
	            node.pb({0,{0,0}});
	        }
	        u(node[ind].s.f,L,M,x);
	    } else {
	        if (node[ind].s.s == 0) {
	            node[ind].s.s = node.size();
	            node.pb({0,{0,0}});
	        }
	        u(node[ind].s.s,M+1,R,x);
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
	
	void upd(int x, int y) {
	    for (; y <= SZ; y += (y&-y)) u(y,1,SZ,x);
	} 
	
	int query(int y, int lowx, int highx) {
	    int z = 0;
	    for (; y > 0; y -= (y & -y)) z += q(y,lowx,highx);
	    return z;
	} 
	
	int query(int lowy, int highy, int lowx, int highx) {
		return query(highy,lowx,highx)-query(lowy-1,lowx,highx);
	}
};

int main() {
	
}
