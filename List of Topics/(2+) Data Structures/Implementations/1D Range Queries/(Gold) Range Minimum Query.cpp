template<class T, int SZ> struct RMQ {
    T stor[SZ][31-__builtin_clz(SZ)];
    
    T comb(T a, T b) {
        return min(a,b);
    }
    
    void build(vector<T>& x) {
        F0R(i,x.size()) stor[i][0] = x[i];
        FOR(j,1,31-__builtin_clz(SZ)) F0R(i,SZ-(1<<(j-1))) 
            stor[i][j] = comb(stor[i][j-1],stor[i+(1<<(j-1))][j-1]);
    }
    
    T query(int l, int r) {
        int x = 31-__builtin_clz(r-l+1);
        return comb(stor[l][x],stor[r-(1<<x)+1][x]);
    }
};

RMQ<int,100000> R;

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	vi x; F0R(i,10) x.pb(rand()%100);
	F0R(i,10) cout << x[i] << " ";
	cout << "\n";
	R.build(x);
	F0R(i,10) {
	    int a = rand() % 10, b = rand() % 10; if (a > b) swap(a,b);
	    cout << a << " " << b << " " << R.query(a,b) << "\n";
	}
}
