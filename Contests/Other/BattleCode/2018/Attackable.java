import bc.*;

public class Attackable extends Movable {
	static Unit position(Unit U, Unit u) { // OK
		if (u == null || fastGC.canAttack(U,u) || fastGC.canHeal(U,u)) return U;

		int d = toPii(U).distanceSquaredTo(toPii(u));

		if (U.unitType() == UnitType.Ranger) {
			if (d <= 10) return tryMoveNaive(U,toPii(u),1);
			if (2*U.health() < U.maxHealth()) return U;
		} else if (U.unitType() == UnitType.Mage) {
			if (d <= 2) return tryMoveNaive(U,toPii(u),1);
		}

		if (U.attackHeat() >= 10) {
			if (U.unitType() == UnitType.Ranger && d <= 64) return U;
			if (U.unitType() == UnitType.Mage && d <= 49) return U;
		}

		return tryMove(U,toPii(u),0);
	}

	static void setKillMode() { // OK
		if (cRound > 100 && cRound % 100 < 50) killMode = 1;
		else killMode = 0;
	}

	static void decide(Unit U) { // OK
		if (U.movementHeat() >= 10) return;
		switch(killMode) {
			case 1:	
				pii M = fastGC.closeFactory(U,oteam);
				if (M != null) { U = tryMove(U,M,0); return; } 
				break;
			case 2:
				U = avoidFac(U);
				U = retreat(U,null);
				U = moveRandom(U);
				return;
		}
		U = tryMove(U,closeUnseen(U),0);
	}

	static Unit retreatAttacker(Unit U, Unit u) { // OK
		int d = (int)mapLoc(U).distanceSquaredTo(mapLoc(u));
		if (U.unitType() == UnitType.Ranger) return botRanger.retreatAttacker(U,u);
		if (U.unitType() == UnitType.Mage) {
			if ((u.unitType() == UnitType.Mage && d <= 30) 
				|| (u.unitType() == UnitType.Knight && d <= 16))
				return tryMoveNaive(U,toPii(u),1);
		} else if (U.unitType() == UnitType.Healer) {
			if (d < 8) return tryMoveNaive(U,toPii(u),1);
		}
		return U;
	}

	static Unit shouldOvercharge(Unit U) { // OK
		if (re.getLevel(UnitType.Healer) != 3) return null;
		if (re.getLevel(UnitType.Mage) == 4) {
			if (cRound % 20 != 1) return null;
		} else {
			if (cRound % 10 != 1) return null;
		}
		
		pii u = firstPriority(U); 
		if (toPii(U).distanceSquaredTo(u) > U.attackRange()) return null;
		return tryOvercharge(U);
	}

	static Unit attackNearby(Unit U) { // OK
		if (U.attackHeat() >= 10) return U;
		pii u = firstPriority(U);
		if (u != null) return fastGC.attack(U, tmp[u.f][u.s]);
		return U;
	}

	static Unit attack(Unit U, pii u) { // OK
		if (u != null) return fastGC.attack(U, tmp[u.f][u.s]);
		return U;
	}

	static boolean runSurrounded(Unit U) { // OK
		if (!fastGC.surrounded(U)) return false;
		if (U.attackHeat() < 10) attackNearby(U);
		return true;
	}

	static boolean runHealer(Unit U) { // OK
		pii cloc = toPii(U);
		if ((U.unitType() == UnitType.Ranger || U.unitType() == UnitType.Mage) && !botRanger.isNearHealer(U)) {
			pii h = nearbyHealer[cloc.f][cloc.s];
			if (getDistGround(toPii(U),h) > 12) return false;

			pii u = firstPriority(U); U = attack(U,u);

			if (h != null) U = tryMove(U, h, 0);
			else if (cloc.distanceSquaredTo(u) <= 81) U = tryMoveNaive(U,u,1);
			else if (getDistGround(toPii(U),closeStructure[cloc.f][cloc.s]) > 7) 
				U = tryMove(U, closeStructure[cloc.f][cloc.s], 0);
			else U = moveRandom(U);

			U = attackNearby(U);
			return true;
		}
		return false;
	}

	static void attack(Unit U) {
		while (true) {
			U = structRocket.runRocket(U); if (U == null) return;
			if (runHealer(U)) return;

			if (U.movementHeat() >= 10) {
				if (U.attackHeat() >= 10) return;
				pii u = firstPriority(U); if (u == null) return;
				Unit uu = tmp[u.f][u.s]; fastGC.attack(U,uu); 
				return;
			} 

			pii u = firstPriority(U);
			int d = pii.distanceSquaredTo(U,u);
			if (d > 81) U = findTeammate(U);

			if (killMode == 2 && d > 81) u = null;
			if (u == null || tmp[u.f][u.s] == null) { decide(U); return; }
			Unit uu = tmp[u.f][u.s];

			U = position(U,uu); U = fastGC.attack(U,uu); 

			Unit UU = shouldOvercharge(U);
			if (UU == null) {
				U = retreatAttacker(U,uu);
				return;
			} else U = UU;
		} 
	}

	static boolean badAttacker(Unit u) {
		if (u.unitType() == UnitType.Knight || u.unitType() == UnitType.Mage) return true;
		return false;
	}	
}