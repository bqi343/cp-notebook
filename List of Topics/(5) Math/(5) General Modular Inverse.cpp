int inv(int a, int b) { // 0 < a < b, gcd(a,b) = 1
    if (a == 1) return 1;
    ll i = inv(b%a,a);
    ll tmp = -((b/a)*i+((b%a)*i)/a) % b;
    while (tmp < 0) tmp += b;
    return tmp;
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    cout << inv(25,43); // 31
}