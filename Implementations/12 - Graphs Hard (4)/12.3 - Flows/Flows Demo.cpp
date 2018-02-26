/**
* Link: http://www.spoj.com/problems/FASTFLOW/
* Use with Dinic, Push-Relabel, Edmonds-Karp
*/

int N,M;
PushRelabel<5001> D; 

int main() {
    cin >> N >> M;
    F0R(i,M) {
        int a,b,c; cin >> a >> b >> c;
        D.addEdge(a,b,c);
        D.addEdge(b,a,c);
    }
    cout << D.maxFlow(1,N);
}