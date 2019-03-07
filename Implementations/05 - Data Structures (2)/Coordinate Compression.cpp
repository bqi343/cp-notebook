/**
 * Description: demonstrates use of map
 * Source: Own
 * Verification: POI 12 - The Bus
 */

void compress(vector<vi>& x, int ind) {
    map<int,int> m; 
    trav(a,x) m[a[ind]] = 0;
    int co = 0; trav(a,m) a.s = co++;
    trav(a,x) a[ind] = m[a[ind]];
}