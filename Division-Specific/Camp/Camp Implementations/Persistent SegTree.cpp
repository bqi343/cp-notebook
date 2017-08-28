#include <bits/stdc++.h>
 
#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define pb push_back
#define f first
#define s second
 
using namespace std;
 
typedef pair<int,int> pii;

struct pers {
    int loc[100001], nex = 1<<18;
    pair<int,pii> seg[3000000];
    
    pers() {}
    
    void upd(int pre, int ne, int L, int R, int val) {
        seg[ne].f = seg[pre].f+1;
        if (L == R) return;
        
        int M = (L+R)/2;
        if (val <= M) {
            seg[ne].s.f = nex++;
            seg[ne].s.s = seg[pre].s.s;
            upd(seg[pre].s.f,seg[ne].s.f,L,M,val);
        } else {
            seg[ne].s.f = seg[pre].s.f;
            seg[ne].s.s = nex++;
            upd(seg[pre].s.s,seg[ne].s.s,M+1,R,val);
        }
    }
    
    void build() {
        F0R(i,1<<17) seg[i].s = {2*i,2*i+1};
    }
    
    int query(int L, int R, int k, int x1, int x2, int y1, int y2) {
        if (L == R) return L;
        int num = seg[seg[x1].s.f].f+seg[seg[x2].s.f].f-seg[seg[y1].s.f].f-seg[seg[y2].s.f].f;
        
        int M = (L+R)/2;
        
        if (k > num) return query(M+1,R,k-num,seg[x1].s.s,seg[x2].s.s,seg[y1].s.s,seg[y2].s.s);
        return query(L,M,k,seg[x1].s.f,seg[x2].s.f,seg[y1].s.f,seg[y2].s.f);
    }
};

int main() {
    
}
