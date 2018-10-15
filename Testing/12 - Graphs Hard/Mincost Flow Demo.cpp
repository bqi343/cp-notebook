mcf<100> m;

int main() {
    m.addEdge(0, 1, 16, 5);
    m.addEdge(1, 2, 13, 7);
    m.addEdge(1, 2, 13, 8);
    
    pi x = m.mincostflow(0,2);
    cout << x.f << " " << x.s;
}
