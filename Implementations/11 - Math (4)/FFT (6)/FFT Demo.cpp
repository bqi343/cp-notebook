int main() {
    int N; cin >> N;
    vl a(N+1), b(N+1);
    F0R(j,N+1) cin >> a[N-j];
    F0R(j,N+1) cin >> b[N-j];
    vl x = FFT::convll(a,b);
    F0Rd(j,sz(x)) cout << x[j] << " ";
    cout << "\n";
}