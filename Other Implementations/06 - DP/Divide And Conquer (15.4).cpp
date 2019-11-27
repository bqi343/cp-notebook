/**
 * Description: ?
 * Source: Own
 * Verification: CEOI 2004 Two Sawmills
 */

void divide(int lo, int hi, int L, int R) {
    if (lo > hi) return;
    int mid = (lo+hi)/2;
    pair<ll,int> tmp = {1e18,-1};
    FOR(i,max(mid+1,L),R+1) 
    	tmp = min(tmp,{calc(0,mid)+calc(mid+1,i)
    		+calc(i+1,n),i}); // find lowest optimal index
    ans = min(ans,tmp.f);
    divide(lo,mid-1,L,tmp.s); // assume optimal index is non-decreasing
    divide(mid+1,hi,tmp.s,R);
}