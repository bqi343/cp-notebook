import bc.*;
import java.util.*;

public class genBFS extends Globals {
	static void genCloseFriendGround() {
		ArrayDeque<pii> L = new ArrayDeque<>(totsz);

		for (int i = 0; i < C.getWidth(); ++i)
			for (int j = 0; j < C.getHeight(); ++j)
				if (tmp[i][j] != null && tmp[i][j].team() == cteam) 
					L.add(closeFriendGround[i][j] = new pii(i,j));
				else closeFriendGround[i][j] = null;

		while (!L.isEmpty()) {
			pii t = L.poll();
			for (int i = 1; i < 9; ++i) {
				int X = t.f+xdir[i], Y = t.s+ydir[i];
				if (fastGC.passable(X,Y) && closeFriendGround[X][Y] == null) {
					closeFriendGround[X][Y] = closeFriendGround[t.f][t.s];
					L.add(new pii(X,Y));
				}
			}
		}
	}
	
	static boolean worth(int i, int j) {
		return karboniteCount[i][j] > 2 && fastGC.valid(i,j) && ok[comp[i][j]] && !bad[i][j] && notCloseWorker(i,j);
	}
	
	static void initCloseToKarbonite(ArrayDeque<pii> q, boolean b) {
		ArrayList<pii> tmp = new ArrayList<>(totsz);
		for(int i = 0; i < C.getWidth(); i++) 
			for(int j = 0; j < C.getHeight(); j++) {
				if (worth(i,j)) tmp.add(new pii(i,j));
				bfsFrom[i][j] = null;
			}
		
		Collections.shuffle(tmp);
		if (b) {
			Collections.sort(tmp,new PiiComparator());
			for (int i = tmp.size()-1; i >= Math.max(0,tmp.size()-10); --i) {
				bfsFrom[tmp.get(i).f][tmp.get(i).s] = Direction.Center;
				q.add(tmp.get(i));
			}
		} else {
			for (int i = 0; i < tmp.size(); ++i) {
				bfsFrom[tmp.get(i).f][tmp.get(i).s] = Direction.Center;
				q.add(tmp.get(i));
			}
		}
	}
	
	static ArrayList<Unit> genCloseToKarbonite(boolean b) { // sorted arraylist of workers closest to karbonite
		ArrayList<Unit> ans = new ArrayList<>();
		ArrayDeque<pii> q = new ArrayDeque<>(totsz);
		initCloseToKarbonite(q,b);
		shuffleArray(dir);

		while (q.size() > 0) {
			pii cloc = q.poll();
			for(int i = 0; i < 9; i++) {
				int x = cloc.f + xdir[dir[i]], y = cloc.s + ydir[dir[i]];
				if (fastGC.passable(x, y) && bfsFrom[x][y] == null) {
					pii next = new pii(x,y);
					q.add(next);
					bfsFrom[x][y] = directions[opposite(dir[i])];

					Unit u = tmp[next.f][next.s];
					if (b && fastGC.activeWorker(u)) ans.add(u);
				}
			}
		}

		return ans;
	}

	static void genDist(int initx, int inity) {
		for (int i = 0; i < C.getWidth(); ++i)
			for (int j = 0; j < C.getHeight(); ++j) 
				distGround[initx][inity][i][j] = INF;

		if (!fastGC.valid(initx,inity)) return;

		distGround[initx][inity][initx][inity] = 0;
		ArrayDeque<pii> L = new ArrayDeque<>(totsz); L.add(new pii(initx,inity));

		while (L.size() > 0) {
			pii t = L.poll();
			for (int i = 1; i < 9; ++i) {
				int X = t.f+xdir[i], Y = t.s+ydir[i];
				if (fastGC.valid(X,Y) && distGround[initx][inity][X][Y] == INF) {
					distGround[initx][inity][X][Y] = distGround[initx][inity][t.f][t.s]+1;
					L.add(new pii(X,Y));
				}
			}
		}
	}
	
	static void genCloseEnemyEuclid() { 
		ArrayDeque<pii> L = new ArrayDeque<>(totsz);

		for (int i = 0; i < C.getWidth(); ++i)
			for (int j = 0; j < C.getHeight(); ++j)
				if (fastGC.opAttacker(tmp[i][j])) 
					L.add(closeEnemyEuclid[i][j] = new pii(i,j));
				else closeEnemyEuclid[i][j] = null;

		while (!L.isEmpty()) {
			pii t = L.poll();
			for (int i = 1; i < 9; i += 2) {
				int X = t.f+xdir[i], Y = t.s+ydir[i];
				if (fastGC.onBoard(X,Y) && closeEnemyEuclid[X][Y] == null) {
					closeEnemyEuclid[X][Y] = closeEnemyEuclid[t.f][t.s];
					L.add(new pii(X,Y));
				}
			}
		}
	}
	
	static void genCloseRocket() {
		ArrayDeque<pii> L = new ArrayDeque<>(totsz);

		for (int i = 0; i < C.getWidth(); ++i)
			for (int j = 0; j < C.getHeight(); ++j)
				if (yourRocket(tmp[i][j]) && tmp[i][j].structureGarrison().size() < tmp[i][j].structureMaxCapacity()) 
					L.add(closeRocket[i][j] = new pii(i,j));
				else closeRocket[i][j] = null;

		while (!L.isEmpty()) {
			pii t = L.poll();
			for (int i = 1; i < 9; ++i) {
				int X = t.f+xdir[i], Y = t.s+ydir[i];
				if (fastGC.passable(X,Y) && closeRocket[X][Y] == null) {
					closeRocket[X][Y] = closeRocket[t.f][t.s];
					L.add(new pii(X,Y));
				}
			}
		}
	}

	static void genCloseDamageStructure() {
		ArrayDeque<pii> L = new ArrayDeque<>(totsz);

		for (int i = 0; i < C.getWidth(); ++i)
			for (int j = 0; j < C.getHeight(); ++j)
				closeDamageStructure[i][j] = null;

		for (int i = 0; i < C.getWidth(); ++i)
			for (int j = 0; j < C.getHeight(); ++j)
				if (fastGC.yourUnbuiltStructure(tmp[i][j])) 
					L.add(closeDamageStructure[i][j] = new pii(i,j));

		for (int i = 0; i < C.getWidth(); ++i)
			for (int j = 0; j < C.getHeight(); ++j)
				if (fastGC.yourDamageStructure(tmp[i][j])) 
					L.add(closeDamageStructure[i][j] = new pii(i,j));

		while (!L.isEmpty()) {
			pii t = L.poll();
			for (int i = 1; i < 9; ++i) {
				int X = t.f+xdir[i], Y = t.s+ydir[i];
				if (fastGC.passable(X,Y) && closeDamageStructure[X][Y] == null) {
					closeDamageStructure[X][Y] = closeDamageStructure[t.f][t.s];
					if (!fastGC.your(tmp[X][Y],UnitType.Worker)) L.add(new pii(X,Y));
				}
			}
		}
	}
	
	static void genCloseStructure() {
		ArrayDeque<pii> L = new ArrayDeque<>(totsz);

		for (int i = 0; i < C.getWidth(); ++i)
			for (int j = 0; j < C.getHeight(); ++j)
				if (fastGC.yourStructure(tmp[i][j])) 
					L.add(closeStructure[i][j] = new pii(i,j));
				else closeStructure[i][j] = null;

		while (!L.isEmpty()) {
			pii t = L.poll();
			for (int i = 1; i < 9; ++i) {
				int X = t.f+xdir[i], Y = t.s+ydir[i];
				if (fastGC.passable(X,Y) && closeStructure[X][Y] == null) {
					closeStructure[X][Y] = closeStructure[t.f][t.s];
					if (!fastGC.your(tmp[X][Y],UnitType.Worker)) L.add(new pii(X,Y));
				}
			}
		}
	}
	
	static void genCloseEnemyGround() {
		ArrayDeque<pii> L = new ArrayDeque<>(totsz);

		for (int i = 0; i < C.getWidth(); ++i)
			for (int j = 0; j < C.getHeight(); ++j)
				if (tmp[i][j] != null && tmp[i][j].team() == oteam) {
					L.add(closeEnemyGround[i][j] = new pii(i,j));
					distCloseEnemyGround[i][j] = 0;
				} else {
					closeEnemyGround[i][j] = null;
					distCloseEnemyGround[i][j] = INF;
				}

		while (!L.isEmpty()) {
			pii t = L.poll();
			for (int i = 1; i < 9; ++i) {
				int X = t.f+xdir[i], Y = t.s+ydir[i];
				if (fastGC.passable(X,Y) && closeEnemyGround[X][Y] == null) {
					closeEnemyGround[X][Y] = closeEnemyGround[t.f][t.s];
					distCloseEnemyGround[X][Y] = distCloseEnemyGround[t.f][t.s]+1;
					L.add(new pii(X,Y));
				}
			}
		}
	}
	
	static void genCloseLastSense() {
		ArrayDeque<pii> L = new ArrayDeque<>(totsz);
		for (int i = 0; i < C.getWidth(); ++i)
			for (int j = 0; j < C.getHeight(); ++j)
				if (fastGC.passable(i,j) && lastSense[i][j] < cRound-10) {
					closeLastSense[i][j] = new pii(i,j);
					L.add(new pii(i,j));
				} else closeLastSense[i][j] = null;

		while (!L.isEmpty()) {
			pii t = L.poll();
			for (int i = 1; i < 9; ++i) {
				int X = t.f+xdir[i], Y = t.s+ydir[i];
				if (fastGC.passable(X,Y) && closeLastSense[X][Y] == null) {
					closeLastSense[X][Y] = closeLastSense[t.f][t.s];
					L.add(new pii(X,Y));
				}
			}
		}
	}
	
	static void genDamageFriend() {
		ArrayDeque<pii> L = new ArrayDeque<>(totsz);
		
		for (int i = 0; i < C.getWidth(); ++i)
			for (int j = 0; j < C.getHeight(); ++j)
				if (fastGC.passable(i,j) && fastGC.yourDamagedAttacker(tmp[i][j])) {
					damageFriend[i][j] = new pii(i,j);
					distDamageFriend[i][j] = 0;
					L.add(new pii(i,j));
				} else {
					damageFriend[i][j] = null;
					distDamageFriend[i][j] = INF;
				}

		while (!L.isEmpty()) {
			pii t = L.poll();
			for (int i = 1; i < 9; ++i) {
				int X = t.f+xdir[i], Y = t.s+ydir[i];
				if (fastGC.passable(X,Y) && damageFriend[X][Y] == null) {
					damageFriend[X][Y] = damageFriend[t.f][t.s];
					distDamageFriend[X][Y] = distDamageFriend[t.f][t.s]+1;
					L.add(new pii(X,Y));
				}
			}
		}
		
		for (int i = 0; i < C.getWidth(); ++i)
			for (int j = 0; j < C.getHeight(); ++j)
				if (fastGC.passable(i,j) && fastGC.yourAttacker(tmp[i][j]) && damageFriend[i][j] == null) {
					damageFriend[i][j] = new pii(i,j);
					distDamageFriend[i][j] = 0;
					L.add(new pii(i,j));
				} 
		
		while (!L.isEmpty()) {
			pii t = L.poll();
			for (int i = 1; i < 9; ++i) {
				int X = t.f+xdir[i], Y = t.s+ydir[i];
				if (fastGC.passable(X,Y) && damageFriend[X][Y] == null) {
					damageFriend[X][Y] = damageFriend[t.f][t.s];
					distDamageFriend[X][Y] = distDamageFriend[t.f][t.s]+1;
					L.add(new pii(X,Y));
				}
			}
		}
	}
	
	static void genDamageFriendWeighted() {
		PriorityQueue<pii> todo = new PriorityQueue<>(Collections.reverseOrder());
		for (int i = 0; i < C.getWidth(); ++i)
			for (int j = 0; j < C.getHeight(); ++j) if (fastGC.passable(i,j)) {
				todo.add(new pii(CumSum.weight[i][j],50*i+j));
				distDamageFriend[i][j] = CumSum.weight[i][j];
				damageFriend[i][j] = new pii(i,j);
			}
		
		while (todo.size() > 0) {
			pii x = todo.poll();
			pii t = new pii(x.s/50,x.s%50);
			if (x.f != distDamageFriend[t.f][t.s]) continue;

			for (int i = 1; i < 9; ++i) {
				int X = t.f+xdir[i], Y = t.s+ydir[i];
				if (fastGC.passable(X,Y) && x.f-1 > distDamageFriend[X][Y]) {
					damageFriend[X][Y] = damageFriend[t.f][t.s];
					distDamageFriend[X][Y] = x.f-1;
					todo.add(new pii(distDamageFriend[X][Y],50*X+Y));
				}
			}
		}
		
	}
	
	static void genNearbyHealer() {
		ArrayDeque<pii> L = new ArrayDeque<>(totsz);
		for(int i = 0; i < C.getWidth(); i++) {
			for(int j = 0; j < C.getHeight(); j++) {
				if(fastGC.passable(i,j) && fastGC.your(tmp[i][j], UnitType.Healer)) {
					nearbyHealer[i][j] = new pii(i, j);
					L.add(new pii(i, j));
				} else {
					nearbyHealer[i][j] = null;
				}
			}
		}
		while(!L.isEmpty()) {
			pii t = L.poll();
			for (int i = 1; i < 9; ++i) {
				int X = t.f+xdir[i], Y = t.s+ydir[i];
				if (fastGC.passable(X,Y) && nearbyHealer[X][Y] == null) {
					nearbyHealer[X][Y] = nearbyHealer[t.f][t.s];
					L.add(new pii(X,Y));
				}
			}
		}
	}
	
	static void gen() {
		CumSum.gen();
		
		genOpposingFac();
		genCloseLastSense();
		genCloseEnemyGround();
		genCloseEnemyEuclid();
		genCloseFriendGround();
		genCloseRocket();
		genCloseDamageStructure();
		genDamageFriendWeighted();
		genCloseStructure();
		genNearbyHealer();
		
		closestWorkers = genCloseToKarbonite(cPlanet == Planet.Mars || cRound <= rushRounds);
	}
}
