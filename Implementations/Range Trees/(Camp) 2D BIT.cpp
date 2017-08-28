/*#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>*/
#include <bits/stdc++.h>
 
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
 
const int MOD = 1000000007, SZ = 1000;

struct BIT2D { 
    int bitXY[SZ+1][SZ+1], bitX[SZ+1][SZ+1], bitY[SZ+1][SZ+1], bit[SZ+1][SZ+1];
    
    void updXY(int a, int b, int inc) {
        for (;a <= SZ; a += (a&-a))
            for (int b1 = b; b1 <= SZ; b1 += (b1&-b1))
                bitXY[a][b1] += inc;
    }
     
    void updX(int a, int b, int inc) {
        for (;a <= SZ; a += (a&-a))
            for (int b1 = b; b1 <= SZ; b1 += (b1&-b1))
                bitX[a][b1] += inc;
    }
     
    void updY(int a, int b, int inc) {
        for (;a <= SZ; a += (a&-a))
            for (int b1 = b; b1 <= SZ; b1 += (b1&-b1))
                bitY[a][b1] += inc;
    }
     
    void up(int a, int b, int inc) {
        for (;a <= SZ; a += (a&-a))
            for (int b1 = b; b1 <= SZ; b1 += (b1&-b1))
                bit[a][b1] += inc;
    }
     
    void upd(int a, int b, int inc) {
        updXY(1,1,inc), updXY(1,b+1,-inc), updXY(a+1,1,-inc), updXY(a+1,b+1,inc);
        updX(1,b+1,b*inc), updX(a+1,b+1,-b*inc);
        updY(a+1,1,a*inc), updY(a+1,b+1,-a*inc);
        up(a+1,b+1,a*b*inc);
    }
     
    void upd(int a, int b, int c, int d) {
        upd(b,d,1);
        upd(a-1,d,-1);
        upd(b,c-1,-1);
        upd(a-1,c-1,1);
    }
     
    int qXY(int a, int b) {
        int ans = 0;
        for (; a > 0; a -= (a&-a))
            for (int b1 = b; b1 > 0; b1 -= (b1&-b1))
                ans += bitXY[a][b1];
        return ans;
    }
     
    int qX(int a, int b) {
        int ans = 0;
        for (; a > 0; a -= (a&-a))
            for (int b1 = b; b1 > 0; b1 -= (b1&-b1))
                ans += (int)bitX[a][b1];
        return ans;
    }
     
    int qY(int a, int b) {
        int ans = 0;
        for (; a > 0; a -= (a&-a))
            for (int b1 = b; b1 > 0; b1 -= (b1&-b1))
                ans += (int)bitY[a][b1];
        return ans;
    }
     
    int q(int a, int b) {
        int ans = 0;
        for (; a > 0; a -= (a&-a))
            for (int b1 = b; b1 > 0; b1 -= (b1&-b1))
                ans += (int)bit[a][b1];
        return ans;
    }
     
    int query(int a, int b) {
        return (qXY(a,b)*(a*b)+qX(a,b)*a+qY(a,b)*b+q(a,b));
    }
     
    int query(int a, int b, int c, int d) {
        return query(b,d)-query(a-1,d)-query(b,c-1)+query(a-1,c-1);
    }
};
 
int main() {
	BIT2D x; x.upd(1,2,5,6);
	cout << x.query(2,3,5,6);
}