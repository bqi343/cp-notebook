

int main() {
    vi x = z("abcababcabcaba");
    for (int i: x) cout << i << " ";
    cout << "\n";
    
    x = get("abcab","uwetrabcerabcab");
    for (int i: x) cout << i << " ";
}
