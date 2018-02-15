/**
* Description: Demonstrates use of map
* Verification: POI 12 - The Bus
*/

void compress(vector<array<int,3>>& x, int ind) {
    map<int,int> m; 
    for (auto& a: x) m[a[ind]] = 0;
    int co = 0; for (auto& a: m) a.s = co++;
    for (auto& a: x) a[ind] = m[a[ind]];
}
