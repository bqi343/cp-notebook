Dijkstra<100> D;

int main() {
	F0R(i,100) F0R(j,100) if (rand() % 10 == 0) D.adj[i].pb({j,rand() % 10+1});
	D.gen();
	F0R(i,100) cout << D.dist[i] << "\n";
}