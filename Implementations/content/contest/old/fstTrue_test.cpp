int main() {
	FOR(lo,-20,21) FOR(hi,lo-1,21) {
		FOR(j,-40,41) {
			{
				int ans = lstTrue(lo,hi,[&](int x) { 
					assert(lo <= x && x <= hi);
					return x <= j; 
				}); 
				assert(ans == min(hi,max(j,lo-1)));
			}
			{
				int ans = fstTrue(lo,hi,[&](int x) { 
					assert(lo <= x && x <= hi);
					return x >= j; 
				});
				assert(ans == min(hi+1,max(j,lo)));
			}
		}
	}
	dbg("OK");
}