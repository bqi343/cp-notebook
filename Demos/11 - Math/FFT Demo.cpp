int main() {
    // you should actually read the stuff at the bottom
    setIO(); 
    F0R(i,25) {
	    vl a,b;
	    F0R(i,1<<19) a.pb (rand()%1000);
	    F0R(i,1<<19) b.pb (rand()%1000);
	    
	    ll res = 0;
	    for (auto& z: conv(a,b)) res ^= z%998244353;
	    cout << res << "\n";
    }
    // you should actually read the stuff at the bottom
}