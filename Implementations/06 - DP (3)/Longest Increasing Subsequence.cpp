/**
 * Description: DP with Binary Search
 * Source: own
 * Verification: https://cses.fi/problemset/task/1145/
 */

vi bes = {INT_MIN}; // min last term of increasing sequence with i terms

void add(int x) { // add terms of sequence one by one
    int lo = lb(all(bes),x)-begin(bes);
    if (lo == sz(bes)) bes.pb(0);
    bes[lo] = x; // sz(bes)-1 is your current answer
}
