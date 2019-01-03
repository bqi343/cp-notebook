/**
 * Description: Interval min modifications
 * Source: CF tutorial?
 * Verification: http://acm.hdu.edu.cn/showproblem.php?pid=5306
 */

template<int SZ> struct SegTreeBeats {
    int N;
    ll sum[2*SZ];
    int mx[2][2*SZ], maxCnt[2*SZ];

    void pull(int ind) {
        mx[0][ind] = max(mx[0][2*ind],mx[0][2*ind+1]);
        mx[1][ind] = max(mx[1][2*ind],mx[1][2*ind+1]);
        maxCnt[ind] = 0;
        
        F0R(i,2) {
            if (mx[0][2*ind^i] == mx[0][ind]) maxCnt[ind] += maxCnt[2*ind^i];
            else mx[1][ind] = max(mx[1][ind],mx[0][2*ind^i]);
        }
        
        sum[ind] = sum[2*ind]+sum[2*ind+1];
    }
    
    void build(vi& a, int ind = 1, int L = 0, int R = -1) {
        if (R == -1) R += N;
        if (L == R) {
            mx[0][ind] = sum[ind] = a[L];
            maxCnt[ind] = 1; mx[1][ind] = -1;
            return;
        } 
        
        int M = (L+R)/2;
        build(a,2*ind,L,M); build(a,2*ind+1,M+1,R); pull(ind);
    }
    
    void push(int ind, int L, int R) {
        if (L == R) return;
        F0R(i,2) 
            if (mx[0][2*ind^i] > mx[0][ind]) {
                sum[2*ind^i] -= (ll)maxCnt[2*ind^i]*
                                (mx[0][2*ind^i]-mx[0][ind]);
                mx[0][2*ind^i] = mx[0][ind];
            }
    }
    
    void upd(int x, int y, int t, int ind = 1, int L = 0, int R = -1) { // set a_i = min(a_i,t)
        if (R == -1) R += N;
        if (R < x || y < L || mx[0][ind] <= t) return;
        push(ind,L,R);
        if (x <= L && R <= y && mx[1][ind] < t) {
            sum[ind] -= (ll)maxCnt[ind]*(mx[0][ind]-t);
            mx[0][ind] = t;
            return;
        }
        if (L == R) return;
        int M = (L+R)/2;
        upd(x,y,t,2*ind,L,M); upd(x,y,t,2*ind+1,M+1,R); pull(ind);
    }
    
    ll qsum(int x, int y, int ind = 1, int L = 0, int R = -1) {
        if (R == -1) R += N;
        if (R < x || y < L) return 0;
        push(ind,L,R);
        if (x <= L && R <= y) return sum[ind];
        
        int M = (L+R)/2;
        return qsum(x,y,2*ind,L,M)+qsum(x,y,2*ind+1,M+1,R);
    }
    
    int qmax(int x, int y, int ind = 1, int L = 0, int R = -1) {
        if (R == -1) R += N;
        if (R < x || y < L) return -1;
        push(ind,L,R);
        if (x <= L && R <= y) return mx[0][ind];
        
        int M = (L+R)/2;
        return max(qmax(x,y,2*ind,L,M), qmax(x,y,2*ind+1,M+1,R));
    }
};