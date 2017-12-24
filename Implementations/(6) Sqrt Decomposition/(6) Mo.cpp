/**
* Source: Codeforces
* Description: Answers queries offline in (N+Q)sqrt(N)
* Also see Mo's on trees
*/

int block = 300; // set ~sqrt(N)

bool cmp(vi a, vi b) {
    if (a[0]/block != b[0]/block) return a[0] < b[0];
    return a[1] < b[1];
}