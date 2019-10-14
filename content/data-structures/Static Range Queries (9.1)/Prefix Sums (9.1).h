/**
 * Description: calculates rectangle sums in constant time
 * Source: KACTL
 * Verification: POI 16 Ticket Inspector
 */

template<class T> struct PrefixSums {
	vector<vector<T>> sum;
	void init(const vector<vector<T>>& v) {
		int R = sz(v), C = sz(v[0]);
		sum.assign(R+1,vector<T>(C+1));
		F0R(i,R) F0R(j,C) 
			sum[i+1][j+1] = v[i][j]+sum[i+1][j]+sum[i][j+1]-sum[i][j];
	}
	T get(int X1, int X2, int Y1, int Y2) {
		X2 ++, Y2 ++;
		return sum[X2][Y2]-sum[X1][Y2]
			-sum[X2][Y1]+sum[X1][Y1];
	}
};