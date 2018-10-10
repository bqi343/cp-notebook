/**
* Description: DP with Binary Search
*/

vi bes = {INT_MIN}; // last term of increasing sequence with i terms

void ad(int x) { // add terms of sequence one by one
    int lo = lb(all(bes),x)-bes.begin();
    if (lo == sz(bes)) bes.pb(0);
    bes[lo] = x; // sz(bes)-1 is your current answer
}