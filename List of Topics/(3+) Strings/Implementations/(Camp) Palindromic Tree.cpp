// http://codeforces.com/blog/entry/13959

const int maxn = 1e5, sigma = 26;
 
int s[maxn], len[maxn], link[maxn], to[maxn][sigma];
 
int n, last, sz;
 
void init() {
    s[n++] = -1;
    link[0] = 1;
    len[1] = -1;
    sz = 2;
}
 
int get_link(int v) {
    while(s[n-len[v]-2] != s[n-1]) v = link[v];
    return v;
}
 
void add_letter(int c) {
    s[n++] = c;
    last = get_link(last);
    if (!to[last][c]) {
        len[sz] = len[last]+2;
        link[sz] = to[get_link(link[last])][c];
        to[last][c] = sz++;
    }
    last = to[last][c];
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	
}

// read!
// ll vs. int!