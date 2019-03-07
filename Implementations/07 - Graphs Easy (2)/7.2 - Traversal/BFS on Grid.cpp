/**
 * Description: BFS through grid with fixed xdir and ydir arrays
 * Source: Own
 */

const int xdir[4] = {0,1,0,-1}, ydir[4] = {1,0,-1,0};
int dist[21][21];

bool valid(pi y) {
	return !(y.f < 0 || y.f > 20 || y.s < 0 || y.s > 20); // this point is outside of grid
}

void bfs() {
	F0R(i,21) F0R(j,21) dist[i][j] = MOD;
	dist[10][10] = 0; 

	queue<pi> todo; todo.push({10,10}); // initialize queue, distances
	while (sz(todo)) {
		pi x = todo.front(); todo.pop(); // pop point from queue
		F0R(i,4) { 
			pi y = {x.f+xdir[i],x.s+ydir[i]};
			if (!valid(y)) continue;
			if (dist[y.f][y.s] == MOD) { // test whether point has been visited or not
			    dist[y.f][y.s] = dist[x.f][x.s]+1;
			    todo.push(y); // push point to queue
			}
		}
	}
	
    assert(dist[4][5] == 11);
}
