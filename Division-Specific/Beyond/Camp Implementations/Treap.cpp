// based on http://blog.ruofeidu.com/treap-in-45-lines-of-c/

#include <bits/stdc++.h>
 
using namespace std;
//using namespace __gnu_pbds;
  
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
 
#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
  
#define mp make_pair
#define pb push_back
#define f first
#define s second
 
const int MOD = 1000000007;

class node {
    public:
        int val, pri, sz;
        node *c[2];
        node() {
            pri = -1, sz = 0, val = 0;
        }
        node (int v) {
            pri = rand(), val = v, sz = 1;
        }
};

class treap{
    public:
        node *root, *null;
    
        treap () { 
            null = new node(); 
            null->c[0] = null->c[1] = null; 
            root = null; 
        }
        
        void update(node*& p){ 
            if(p == null) return;
            p->sz = 1;
            
            F0R(t,2) p->sz += p->c[t]->sz;
        }
        
        void rot (node *&p, int d){ 
            node *q = p->c[d]; 
            p->c[d] = q->c[d^1]; 
            q->c[d^1] = p; 
            update(p), update(q); 
            p = q; 
        }
        
        void ins(node *&p, int x){
            if (p == null) {
                p = new node(x); 
                p->c[0] = p->c[1] = null;
            } else {
                int t = (x < p->val) ? 0 : 1;
                ins(p->c[t], x); 
                if (p->c[t]->pri < p->pri) rot(p,t);
            }
            update(p);
        }
        
        void del(node *&p, int x){
            if (p == null) return; 
            if (p->val == x) del(p); 
            else {
                int t = (x < p->val) ? 0 : 1;
                del(p->c[t],x); 
            }
            if (p) update(p);
        }
        
        void del(node *&p){ 
            if (p->c[0] == null && p->c[1] == null) {
                delete p;
                p = null;
                return;
            }
            int t = (p->c[0]->pri > p->c[1]->pri) ? 0 : 1;
            rot(p,t); del(p->c[t^1]);
            update(p); 
        }
        
        bool find(node *&p, int x){
            if(p == null) return false; 
            if (x == p->val) return true; 
            int t = (x < p->val) ? 0 : 1;
            return find(p->c[t],x);
        }
        
        int get(node *&p, int x) {
            if (p->c[0]->sz == x) return p->val; 
            if (p->c[0]->sz < x) return get(p->c[1],x-(p->c[0]->sz)-1);
            return get(p->c[0],x);
        }
        
        void ins(int x){ 
            if (find(root,x)) return;
            ins(root,x); 
        }
        
        void del(int x){ 
            if (!find(root,x)) return;
            del(root,x); 
        }
        
        bool find(int x){ return find(root,x); }
        int get(int x) { return get(root,x);}
}; 

treap T;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int N; cin >> N;
    F0R(i,N) {
        char x; int k;
        cin >> x >> k;
        if (x == 'I') T.ins(k);
        else if (x == 'D') T.del(k);
        else if (x == 'N') cout << T.get(k) << "\n"; // get kth element, starting from 0
    }
}