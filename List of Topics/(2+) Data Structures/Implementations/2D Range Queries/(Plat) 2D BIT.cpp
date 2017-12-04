const int SZ = 1000;

struct BIT2D { 
    int bit[SZ+1][SZ+1];
    void upd(int X, int Y, int val) {
        for (; X <= SZ; X += (X&-X))
            for (int Y1 = Y; Y1 <= SZ; Y1 += (Y1&-Y1))
                bit[X][Y1] += val;
    }
    int query(int X, int Y) {
        int ans = 0;
        for (; X > 0; X -= (X&-X))
            for (int Y1 = Y; Y1 > 0; Y1 -= (Y1&-Y1))
                ans += bit[X][Y1];
        return ans;
    }
    int query(int X1, int X2, int Y1, int Y2) {
        return query(X2,Y2)-query(X1-1,Y2)-query(X2,Y1-1)+query(X1-1,Y1-1);
    }
};
 
int main() {
	BIT2D x; 
	x.upd(2,5,7);
	x.upd(3,6,8);
	x.upd(4,6,9);
	cout << x.query(2,3,5,6);
}
