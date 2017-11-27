void compress(vi& x) {
    map<int,int> m;
    for (int i: x) m[i] = 0;

    int co = 0;
    for (auto& a: m) a.s = co++;
    
    for (int& i: x) i = m[i];
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    vi z = {2,4,3,6};
    compress(z);
    for (int i: z) cout << i << " ";
}
