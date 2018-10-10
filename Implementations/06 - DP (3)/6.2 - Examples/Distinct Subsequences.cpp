/**
* Description: DP eliminates overcounting
* Verification: https://cses.fi/problemset/task/1149/
*/

using namespace modOp;

int distinct(string S) {
    vi tot(26);
    int ans = 1;
    for (char c: S) {
        int t = sub(ans,tot[c-'a']);
        AD(tot[c-'a'],t), AD(ans,t);
    }
    return ans;
}