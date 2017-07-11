/*#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;
//using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
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

const int SZ = 100000;

// 100000 by 100000 table

vector<pair<int,pii>> node(SZ+1);
int ans = 0;

void u(int ind, int low, int high, int x) {
    if (high < x || x < low) return;
    node[ind].f ++;
    if (low == high) return;

    int mid = (low+high)/2;
    if (x <= mid) {
        if (node[ind].s.f == 0) {
            node[ind].s.f = node.size();
            node.pb({0,{0,0}});
        }
        u(node[ind].s.f,low,mid,x);
    } else {
        if (node[ind].s.s == 0) {
            node[ind].s.s = node.size();
            node.pb({0,{0,0}});
        }
        u(node[ind].s.s,mid+1,high,x);
    }
} 

int q(int ind, int low, int high, int lowx, int highx) {
    if (lowx <= low && high <= highx) return node[ind].f;
    if (high<lowx || highx<low) return 0;
    int z = 0, mid = (low+high)/2;
    if (node[ind].s.f != 0) z += q(node[ind].s.f,low,mid,lowx,highx);
    if (node[ind].s.s != 0) z += q(node[ind].s.s,mid+1,high,lowx,highx);
    return z;
} 

void upd(int x, int y) {
    for (;y <= SZ; y += (y&-y)) u(y,1,SZ,x);
} 

int query(int y, int lowx, int highx) {
    int z = 0;
    for (; y>0; y -= (y & -y)) z += q(y,1,SZ,lowx,highx);
    return z;
} 

int main() {
	
}
