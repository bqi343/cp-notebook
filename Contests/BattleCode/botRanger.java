import bc.*;
import java.util.*;

public class botRanger extends Attackable {
	static pii snipeTarget;
	static ArrayList<Unit> snipeCandidate = new ArrayList<>();

	static MapLocation select(int x, int y) {
		ArrayList<pii> A = new ArrayList<>();

		for (int i = x-2; i <= x+2; i++) {
			for (int j = y-2; j <= y+2; j++) {
				if (fastGC.valid(i,j)) A.add(new pii(i,j));
			}
		}

		pii ret = A.get(ran.nextInt(A.size()));
		return new MapLocation(cPlanet,ret.f,ret.s);
	}

	static int[][] cFriend = new int[51][51], cOp = new int[51][51];

	static pii getBes() {
		int sum = 0;
		pii bes = null;

		for (int i = 0; i < C.getWidth()-4; ++i) 
			for (int j = 0; j < C.getHeight()-4; ++j) {
				if (CumSum.getSum(CumSum.cFriend,i,i+4,j,j+4) != 0) continue;
				if (CumSum.getSum(CumSum.cOp,i,i+4,j,j+4) > sum) {
					sum = CumSum.getSum(CumSum.cOp,i,i+4,j,j+4);
					bes = new pii(i+2,j+2);
				}
			}

		return bes;
	}

	static void trySnipe() {
		if (cRound % 20 != 0 || re.getLevel(UnitType.Ranger) != 3) return;
		pii x = getBes(); if (x == null) return;

		for (Unit u: snipeCandidate) {
			u = fastGC.upd(u);
			if (u == null) continue;
			gc.beginSnipe(u.id(),select(x.f,x.s));
		}
	}

	static boolean isNearHealer(Unit U) {
		pii M = toPii(U);
		if (nearbyHealer[M.f][M.s] == null) return false;
		for(int i = -5; i <= 5; i++) {
			for(int j = -5; j <= 5; j++) if (i*i + j*j <= 30){
				int x = M.f+i, y = M.s+j;
				if (fastGC.valid(x,y) && fastGC.your(tmp[x][y], UnitType.Healer)) return true;
			}
		}
		pii m = nearbyHealer[M.f][M.s];
		if (getDistGround(M, m) >= 6) return false;
		return true;
	}

	static pii getPri(Unit U) {
		pii cloc = toPii(U);
		Unit bes1 = null, bes2 = null;

		int r = (int)Math.sqrt(50); 
		for (int i = -r; i <= r; ++i) // gen
			for (int j = -r; j <= r; ++j) if (i*i+j*j >= 10 && i*i+j*j <= 50) {
				int X = cloc.f+i, Y = cloc.s+j;
				if (fastGC.onBoard(X,Y) && tmp[X][Y] != null && tmp[X][Y].team() == oteam) {
					if (fastGC.isAttacker(tmp[X][Y])) {
						if (bes1 == null) bes1 = tmp[X][Y];
						else if (tmp[X][Y].health() < bes1.health()) bes1 = tmp[X][Y];
					} else {
						if (bes2 == null) bes2 = tmp[X][Y];
						else if (tmp[X][Y].health() < bes2.health()) bes2 = tmp[X][Y];
					}
				}
			}

		if (bes1 != null) return toPii(bes1);
		return toPii(bes2);
	}

	static Unit retreatAttacker(Unit U, Unit u) {
		int dist = 0;
		if (u.unitType() == UnitType.Ranger) dist = 50;
		else if (badAttacker(u)) dist = 36;
		if (U.health()*2 <= U.maxHealth()) dist *= 2;

		if (mapLoc(U).distanceSquaredTo(mapLoc(u)) <= dist) return tryMoveNaive(U,toPii(u),1);
		return U;
	}

	static void run(Unit U) {
		if (fastGC.isSniping(U)) return;
		attack(U);
		if (cRound % 20 != 0 || re.getLevel(UnitType.Ranger) != 3) return;
		
		U = gc.unit(U.id());
		pii x = firstPriority(U);
		if (U.abilityHeat() >= 10 
			|| toPii(U).distanceSquaredTo(x) <= 50 
			|| getDistGround(toPii(U),x) <= 12) 
			return;

		snipeCandidate.add(U);
	}
}