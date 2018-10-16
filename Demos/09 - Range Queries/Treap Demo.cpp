pt root = NULL;

int main() {
    setIO();
    F0R(i,10) root = ins(root,i);
    vi v; trav(root,v); cout << v << "\n";
    F0R(i,10) {
        int l = rand() % 10, r = rand() % 10; 
        if (l > r) swap(l,r);
        auto a = splitsz(root,l);
        auto b = splitsz(a.s,r-l+1);
        b.f->flip ^= 1;
        root = merge(a.f,merge(b.f,b.s));
        cout << l << " " << r << "\n";
        //if (i == 9) {
            vi v; trav(root,v); cout << v << "\n";
        //}
    }
}