/**
* Description: Use when atan2 does not suffice
* Source: Own
* Verification: ?
*/

int half(pi x) { return mp(x.s,x.f) > mp(0,0); }

ll area(pi a, pi b) { return (ll)a.f*b.s-(ll)a.s*b.f; }

ll area(pi a, pi b, pi c) {
    b.f -= a.f, b.s -= a.s;
    c.f -= a.f, c.s -= a.s;
    return area(b,c);
}

bool cmp(pi a, pi b) {
    int A = half(a), B = half(b);
    if (A != B) return A < B;
    return area(a,b) > 0;
}