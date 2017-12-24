/**
 * Description: Calculates rectangle sums in constant time
 */

template<class T, int SZ> struct sums {
    ll sum[SZ][SZ];
    sums () { memset(sum,0,sizeof sum); }
    void init() {
        FOR(i,1,SZ) FOR(j,1,SZ) 
            sum[i][j] += sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1];
    }
    ll get(int X1, int X2, int Y1, int Y2) {
        return sum[X2][Y2]-sum[X1-1][Y2]
        		-sum[X2][Y1-1]+sum[X1-1][Y1-1];
    }
};