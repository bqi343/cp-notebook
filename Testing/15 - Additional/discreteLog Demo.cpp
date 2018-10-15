int main() {
    discreteLog D = discreteLog(); D.gen(67,11);
    FOR(i,1,67) {
        int x = D.query(i);
        assert(i == po(11,x,67));
    }
}