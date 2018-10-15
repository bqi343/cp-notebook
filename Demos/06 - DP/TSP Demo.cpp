int main() {
	int T; cin >> T;
	F0R(i,T) {
	    cin >> N; N++;
	    F0R(j,N) F0R(k,N) if (j != k) cin >> dist[j][k];
	    cout << solve() << "\n";
	}
}
