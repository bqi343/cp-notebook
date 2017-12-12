template<class T> pair<T,T> operator+(const pair<T,T>& l, const pair<T,T>& r) {
    return {l.f+r.f,l.s+r.s};
}
 
template<class T> pair<T,T> operator-(const pair<T,T>& l, const pair<T,T>& r) {
    return {l.f-r.f,l.s-r.s};
}
 
template<class T> pair<T,T> operator*(const pair<T,T>& l, T r) {
    return {l.f*r,l.s*r};
}
 
template<class T> pair<T,T> operator/(const pair<T,T>& l, T r) {
    return {l.f/r,l.s/r};
}

template<class T> double mag(pair<T,T> p) {
    return sqrt(p.f*p.f+p.s*p.s);
}

template<class T> pair<T,T> operator*(const pair<T,T>& l, const pair<T,T>& r) {
    // l.f+l.s*i, r.f+r.s*i
    return {l.f*r.f-l.s*r.s,l.s*r.f+l.f*r.s};
}
 
template<class T> pair<T,T> operator/(const pair<T,T>& l, const pair<T,T>& r) {
    // l.f+l.s*i, r.f+r.s*i
    pair<T,T> z = {r.f/(r.f*r.f+r.s*r.s),-r.s/(r.f*r.f+r.s*r.s)};
    return l*z;
}
 
template<class T> double area(pair<T,T> a, pair<T,T> b, pair<T,T> c) {
    b = b-a, c = c-a;
    return (b.f*c.s-b.s*c.f)/2;
}
 
template<class T> double dist(pair<T,T> l, pair<T,T> r) {
    return mag(r-l);
}
 
template<class T> double dist(pair<T,T> o, pair<T,T> x, pair<T,T> d) { // signed distance
    return 2*area(o,x,x+d)/mag(d);
}
