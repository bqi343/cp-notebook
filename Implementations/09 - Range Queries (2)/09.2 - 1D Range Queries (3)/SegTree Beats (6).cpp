/**
 * Description: Interval min modifications
 * Verification: http://acm.hdu.edu.cn/showproblem.php?pid=5306
 */

const int MX = 1<<20;

int N,M, a[MX];

struct Seg {
    ll sum[2*MX];
    int mx1[2*MX], mx2[2*MX], maxCnt[2*MX];

    void pull(int ind) {
        mx1[ind] = max(mx1[2*ind],mx1[2*ind+1]);
        mx2[ind] = max(mx2[2*ind],mx2[2*ind+1]);
        maxCnt[ind] = 0;
        
        if (mx1[2*ind] == mx1[ind]) maxCnt[ind] += maxCnt[2*ind];
        else mx2[ind] = max(mx2[ind],mx1[2*ind]);
        
        if (mx1[2*ind+1] == mx1[ind]) maxCnt[ind] += maxCnt[2*ind+1];
        else mx2[ind] = max(mx2[ind],mx1[2*ind+1]);
        
        sum[ind] = sum[2*ind]+sum[2*ind+1];
    }
    
    void build(int ind = 1, int L = 0, int R = N-1) {
        if (L == R) {
            mx1[ind] = sum[ind] = a[L];
            maxCnt[ind] = 1;
            mx2[ind] = -1;
            return;
        } 
        
        int M = (L+R)/2;
        build(2*ind,L,M); build(2*ind+1,M+1,R);
        pull(ind);
    }
    
    void push(int ind, int L, int R) {
        if (L == R) return;
        if (mx1[2*ind] > mx1[ind]) {
            sum[2*ind] -= (ll)maxCnt[2*ind]*(mx1[2*ind]-mx1[ind]);
            mx1[2*ind] = mx1[ind];
        }
        if (mx1[2*ind+1] > mx1[ind]) {
            sum[2*ind+1] -= (ll)maxCnt[2*ind+1]*(mx1[2*ind+1]-mx1[ind]);
            mx1[2*ind+1] = mx1[ind];
        }
    }
    
    void modify(int x, int y, int t, int ind = 1, int L = 0, int R = N-1) {
        if (R < x || y < L || mx1[ind] <= t) return;
        push(ind,L,R);
        if (x <= L && R <= y && mx2[ind] < t) {
            sum[ind] -= (ll)maxCnt[ind]*(mx1[ind]-t);
            mx1[ind] = t;
            return;
        }
        if (L == R) return;
        int M = (L+R)/2;
        modify(x,y,t,2*ind,L,M);
        modify(x,y,t,2*ind+1,M+1,R);
        pull(ind);
    }
    
    ll qsum(int x, int y, int ind = 1, int L = 0, int R = N-1) {
        if (R < x || y < L) return 0;
        push(ind,L,R);
        if (x <= L && R <= y) return sum[ind];
        
        int M = (L+R)/2;
        return qsum(x,y,2*ind,L,M)+qsum(x,y,2*ind+1,M+1,R);
    }
    
    int qmax(int x, int y, int ind = 1, int L = 0, int R = N-1) {
        if (R < x || y < L) return -1;
        push(ind,L,R);
        if (x <= L && R <= y) return mx1[ind];
        
        int M = (L+R)/2;
        return max(qmax(x,y,2*ind,L,M),qmax(x,y,2*ind+1,M+1,R));
    }
};

Seg S = Seg();
    
void solve() {
	cin >> N >> M;
	F0R(i,N) cin >> a[i];
	S.build();
	
	F0R(i,M) {
	    int t; cin >> t;
	    if (t == 0) {
	        int x,y,z; cin >> x >> y >> z;
	        S.modify(x-1,y-1,z);
	    } else if (t == 1) {
	        int x,y; cin >> x >> y;
	        cout << S.qmax(x-1,y-1) << "\n";
	    } else {
	        int x,y; cin >> x >> y;
	        cout << S.qsum(x-1,y-1) << "\n";
	    }
	}
}