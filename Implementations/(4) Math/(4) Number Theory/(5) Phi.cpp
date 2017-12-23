/**
 * Source: Own
 * the number of operations needed s.t. phi(phi(...phi(n)...))=1 is O(log n)
 */
 
int phi(int x) {
    if (x == 1) return 1;
    int X = x; 
    
    vi pri;
    for (int i = 2; i*i <= x; ++i) if (x % i == 0) {
        while (x % i == 0) x /= i;
        pri.pb(i);
    }
    
    if (x > 1) pri.pb(x);
    for (int i: pri) { X /= i; X *= i-1; }
    return X;
}