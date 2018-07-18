int main() {
    string _S = "abacaba";
    hsh h; h.gen(_S);
    F0R(i,sz(_S)) FOR(j,i,sz(_S)) cout << i << " " << j << " " << h.get(i,j).f << " " << h.get(i,j).s << "\n";
    
    hsh H; H.gen("abadaba");
    cout << h.lcp(H);
}