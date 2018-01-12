//uses about 34 MB
const int MAXN = 100100;
int N = 100000;
struct Node { 
	ll val;
} SEG[20*MAXN];
int e = 0;
int LFT[20*MAXN], RGT[20*MAXN];

int roots[MAXN];
    
int build(int l = 0, int r = N - 1) {
	//build from L to R inclusive. 
	int x = ++e;
	if (l == r){
		SEG[x].val = 0;
		LFT[x] = -1;
		RGT[x] = -1;
		return x;
	}
	int mid = (l + r)/2;
	LFT[x] = build(l, mid);
	RGT[x] = build(mid + 1, r);
	return x;
}

int upd(int cur, int pos, int set, int l = 0, int r = N - 1) {
	//set a[pos] = set in the root cur
	if (r < pos || pos < l) return cur;
	int x = ++e;
	//we're creating a new node
	if (l == r){
		SEG[x].val = set;
		return x;
	}
	int m = (l+r)/2;
	LFT[x] = upd(LFT[cur], pos, set, l, m);
	RGT[x] = upd(RGT[cur], pos, set, m + 1, r);
	SEG[x].val = SEG[LFT[x]].val + SEG[RGT[x]].val;
	return x;
}

ll query(int cur, int L, int R, int l = 0, int r = N - 1){
	if (r < L || R < l) return 0LL;
	int m = (l + r)/2;
	if (L <= l && r <= R) return SEG[cur].val;
	return query(LFT[cur], L, R, l, m) + query(RGT[cur], L, R, m + 1, r);
}
