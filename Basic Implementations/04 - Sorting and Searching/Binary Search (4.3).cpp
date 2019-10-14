/**
 * Description: Basic example of binary search
 * Guess the Number
 * https://open.kattis.com/problems/guess
 */

void binarySearch() {
    int lo = 1, hi = 1000;
    while (1) {
        int mid = (lo+hi)/2;
        cout << mid << endl;
        string res; cin >> res;
        if (res == "correct") return 0;
        else if (res == "lower") hi = mid-1;
        else lo = mid+1;
    }
}