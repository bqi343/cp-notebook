/**
 * Description: DP with Binary Search
 * Source: own
 * Verification: ?
 */

vi bes = {INT_MIN}; // min last term of increasing sequence with i terms

void ad(int x) { // add terms of sequence one by one
    int lo = lb(all(bes),x)-beg(bes);
    if (lo == sz(bes)) bes.pb(0);
    bes[lo] = x; // sz(bes)-1 is your current answer
}