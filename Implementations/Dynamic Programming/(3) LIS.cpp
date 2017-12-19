/**
* Source: own
*/

vi bes = {0};
int n;

void ad(int x) {
    int lo = 0, hi = sz(bes)-1;
    while (lo < hi) {
        int mid = (lo+hi+1)/2;
        if (bes[mid] < x) lo = mid;
        else hi = mid-1;
    }
    if (lo == sz(bes)-1) bes.pb(0);
    bes[lo+1] = x;
}

int main() {
    cin >> n;
    F0R(i,n) {
        int x; cin >> x;
        ad(x);
    }
    cout << sz(bes)-1;
}