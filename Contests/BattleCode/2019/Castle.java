package bc19;

import static bc19.Consts.*;
import java.util.*;

public class Castle extends Building {
  boolean[] isOccupiedKarb, isOccupiedFuel;
  int numKarb, numFuel;

  public Castle(MyRobot z) { super(z); }

  void dumpRound() {
      Z.log("================ ROUND " + Z.CUR.turn + " ================ ");
      if (Z.CUR.turn == 3) Z.log("H: "+Z.h+" W: "+Z.w);
      Z.log("SHOULD SAVE: "+Z.shouldSave);
      Z.log("TIME: "+Z.me.time);
      Z.log("KARBONITE: "+Z.karbonite);
      Z.log("FUEL: "+Z.fuel);
      String T = "UNITS "; for (int i = 0; i < 6; ++i) T += " "+Z.U.totUnits[i];
      Z.log(T);
  }

  void determineCastleLoc() {
    if (Z.me.turn > 3) return;
    if (Z.me.turn == 1)
      for (Robot2 R: Z.robots) if (R.team == Z.me.team) {
        if (!Z.myStructID.contains(R.id)) Z.myStructID.add(R.id);
        if (!Z.myCastleID.contains(R.id)) Z.myCastleID.add(R.id);
      }

    for (Robot2 R: Z.robots) if (Z.myCastleID.contains(R.id) && R.castle_talk > 0) {
      int z = R.castle_talk;
      if (Z.me.turn <= 2 && z <= 64) Z.canRush = false;
      if (z > 64) z -= 128;
      z --;

      if (!Z.castleX.containsKey(R.id)) Z.castleX.put(R.id,z);
      else if (!Z.castleY.containsKey(R.id)) {
        Z.castleY.put(R.id,z);
        Z.addStruct(Z.makeRobot(R.id,0,Z.CUR.team,Z.castleX.get(R.id),Z.castleY.get(R.id)));
      }
    }
    int message = 128 * (Z.canRush ? 1 : 0);  message ++;
    if (Z.CUR.turn == 1) message += Z.CUR.x;
    else if (Z.CUR.turn == 2) message += Z.CUR.y;
    else message = 0;
    Z.castle_talk = message;
  }

  int cat(double x) {
    if (x < 0) return -1;
    if (x > 0) return 1;
    return 0;
  }
  boolean ourSide(int pos) {
    int x = Z.fdiv(pos,64); int y = pos%64;
    if (Z.hsim) return (2*y+1-Z.h)*(2*Z.me.y+1-Z.h) >= 0;
    return (2*x+1-Z.w)*(2*Z.me.x+1-Z.w) >= 0;
  }
  double countAssigned(int pos) { // how many pilgrims assigned to vicinity?
	  int x = Z.fdiv(pos,64); int y = pos%64;
	  double res = 0;
	  for(int dx = -5; dx <= 5; dx++) for(int dy = -5; dy <= 5; dy++)
	   if(Z.valid(x+dx, y+dy) && Z.assigned[y+dy][x+dx]) res += 1.0;
	  return res;
  }
  double crowdedFactor(int pos) {
	  double val = Math.pow(countAssigned(pos)+1.0, 3);
	  return val;
  }
  double sideFactor(int pos) { // decreases gradually from our side, steep incline on other side
  	if (Z.wsim) {
  	  int x = Z.fdiv(pos,64);
  	  int disMid = Math.abs(x - Z.fdiv(Z.w,2));
  	  if(ourSide(pos)) return disMid;
  	  else return 4*disMid;
  	} else {
  	  int y = pos%64;
  	  int disMid = Math.abs(y - Z.fdiv(Z.h,2));
  	  if (ourSide(pos)) return disMid;
  	  else return 4*disMid;
  	}
  }

  double val(int pos) {
    double ret = Z.bfs.dist(pos)*crowdedFactor(pos);
    if (!ourSide(pos)) ret += MOD;
    return ret;
  }
  double valAgg(int pos) {
    return (double)Z.bfs.dist(pos)*sideFactor(pos)*crowdedFactor(pos);
  }
  Comparator<Integer> getComp(int x, int[] y) {
    if (x == 0) {
      return new Comparator<Integer>() {
        public int compare(Integer a, Integer b) {
         double A = val(y[a]), B = val(y[b]);
         return cat(A-B);
        }
      };
    } else {
      return new Comparator<Integer>() {
        public int compare(Integer a, Integer b) {
         double A = valAgg(y[a]), B = valAgg(y[b]);
         return cat(A-B);
        }
      };
    }
  }

  void sortKarb(int x) {
    ArrayList<Integer> temp = new ArrayList<Integer>();
    for(int i = 0; i < Z.karbcount; i++) temp.add(Z.sortedKarb[i]);
    Collections.sort(temp, getComp(x,Z.karbPos));
    for(int i = 0; i < Z.karbcount; i++) Z.sortedKarb[i] = temp.get(i);
  }
  void sortFuel(int x) {
    ArrayList<Integer> temp = new ArrayList<Integer>();
    for (int i = 0; i < Z.fuelcount; i++) temp.add(Z.sortedFuel[i]);
    Collections.sort(temp, getComp(x,Z.fuelPos));
    for(int i = 0; i < Z.fuelcount; i++) Z.sortedFuel[i] = temp.get(i);
  }

  void initVars() {
    for (int x = 0; x < Z.w; x++) for(int y = 0; y < Z.h; y++){
      if (Z.karboniteMap[y][x]) Z.karbcount ++;
      if (Z.fuelMap[y][x]) Z.fuelcount ++;
    }

    Z.sortedKarb = new int[Z.karbcount]; Z.sortedFuel = new int[Z.fuelcount];
    Z.pilToKarb = new int[4097]; Z.pilToFuel = new int[4097];
    for (int i = 0; i < 4097; ++i) Z.pilToKarb[i] = Z.pilToFuel[i] = -1;

    Z.karbPos = new int[Z.karbcount]; Z.fuelPos = new int[Z.fuelcount];
    Z.assigned = new boolean[Z.h][Z.w];

    Z.karbcount = 0; Z.fuelcount = 0;

    for(int x = 0; x < Z.w; x++) for (int y = 0; y < Z.h; y++) {
      if (Z.karboniteMap[y][x]){
        Z.sortedKarb[Z.karbcount] = Z.karbcount;
        Z.karbPos[Z.karbcount] = 64*x + y;
        Z.karbcount ++;
      }
      if (Z.fuelMap[y][x]){
        Z.sortedFuel[Z.fuelcount] = Z.fuelcount;
        Z.fuelPos[Z.fuelcount] = 64*x + y;
        Z.fuelcount ++;
      }
    }

    /*for (int i = 0; i < Z.karbcount; ++i) {
      int p = Z.karbPos[Z.sortedKarb[i]];
      Z.log("AA "+Z.karbPos[Z.sortedKarb[i]]+" "+Z.coordinates(p)+" "+ourSide(p)+" "+Z.bfs.dist(p));
    }*/

    initPatrol();
  }

  void updateVars() {
    shouldBuild = true;
    isOccupiedKarb = new boolean[Z.karbcount];
    isOccupiedFuel = new boolean[Z.fuelcount];
    Z.assigned = new boolean[Z.h][Z.w];

    // find current assignments
    for (Robot2 R: Z.robots) if (R.team == Z.CUR.team && Z.type[R.id] == 2) {
      if (R.castle_talk == 30) shouldBuild = false;
      if (Z.pilToKarb[R.id] != -1) {
        isOccupiedKarb[Z.pilToKarb[R.id]] = true;
        int pos = Z.karbPos[Z.pilToKarb[R.id]];
        Z.assigned[pos%64][Z.fdiv(pos,64)] = true;
      }
      if (Z.pilToFuel[R.id] != -1) {
        isOccupiedFuel[Z.pilToFuel[R.id]] = true;
        int pos = Z.fuelPos[Z.pilToFuel[R.id]];
        Z.assigned[pos%64][Z.fdiv(pos,64)] = true;
      }
    }

    for (int i = 0; i < Z.karbcount; i++) if (isOccupiedKarb[i]) numKarb ++;
    for (int i = 0; i < Z.fuelcount; i++) if (isOccupiedFuel[i]) numFuel ++;
    updatePatrolVars();

    if (Z.CUR.unit == CASTLE && Z.min(Z.myCastleID) == Z.CUR.id && Z.CUR.turn%10 == 0)
      dumpRound();
  }

  int getMessage(int x) { return x+2000; }

  void assignKarb(int i) {
    // Z.log(Z.CUR.turn+" assigned smth to karbonite at " + Z.coordinates(Z.karbPos[i]));
    Z.nextSignal = new pi(getMessage(Z.karbPos[i]), 2);
    Z.assignedPilgrimPos = new pi(0,i);
  }
  void assignFuel(int i) {
    // Z.log(Z.CUR.turn+" assigned smth to fuel at " + Z.coordinates(Z.fuelPos[i]));
    Z.nextSignal = new pi(getMessage(Z.fuelPos[i]), 2);
    Z.assignedPilgrimPos = new pi(1,i);
  }
  void assignRand() { // assign to random if all positions have been filled
    int tot = Z.karbcount+Z.fuelcount;
    int i = (int)(Math.random()*tot);
    if(i < Z.karbcount) assignKarb(i);
    else assignFuel(i-Z.karbcount);
  }

  boolean assignCloseUnexplored() {
    sortKarb(0);
    for (int i = 0; i < Z.karbcount; i++)
      if (!isOccupiedKarb[Z.sortedKarb[i]]
          && !Z.badResource[Z.karbPos[Z.sortedKarb[i]]]
          && countAssigned(Z.karbPos[Z.sortedKarb[i]]) == 0
          && ourSide(Z.sortedKarb[i])) {
            assignKarb(Z.sortedKarb[i]);
            return true;
          }
    sortFuel(0);
    for (int i = 0; i < Z.fuelcount; i++)
      if (!isOccupiedKarb[Z.sortedFuel[i]]
          && !Z.badResource[Z.fuelPos[Z.sortedFuel[i]]]
          && countAssigned(Z.fuelPos[Z.sortedFuel[i]]) == 0
          && ourSide(Z.sortedFuel[i])) {
            assignFuel(Z.sortedFuel[i]);
            return true;
          }
    return false;
  }

  boolean tryAssignKarb() {
	  sortKarb(0);
    for (int i = 0; i < Z.karbcount; i++)
      if (!isOccupiedKarb[Z.sortedKarb[i]] && !Z.badResource[Z.karbPos[Z.sortedKarb[i]]]) {
        assignKarb(Z.sortedKarb[i]); return true;
      }
    return false;
  }
  boolean tryAssignFuel() {
	  sortFuel(0);
    for (int i = 0; i < Z.fuelcount; i++)
      if (!isOccupiedFuel[Z.sortedFuel[i]] && !Z.badResource[Z.fuelPos[Z.sortedFuel[i]]]) {
        assignFuel(Z.sortedFuel[i]); return true;
      }
    return false;
  }
  boolean tryAssignAggressive() {
    sortKarb(1); sortFuel(1);
    int tot = Z.karbcount+Z.fuelcount;
    int x = (int)(Math.random()*tot);
    if (x < Z.karbcount) {
      for(int i = 0; i < Z.karbcount; i++)
        if (!isOccupiedKarb[Z.sortedKarb[i]] && !Z.badResource[Z.karbPos[Z.sortedKarb[i]]]) {
          assignKarb(Z.sortedKarb[i]);
          return true;
        }
    } else {
      for (int i = 0; i < Z.fuelcount; i++)
        if (!isOccupiedFuel[Z.sortedFuel[i]] && !Z.badResource[Z.fuelPos[Z.sortedFuel[i]]]) {
          assignFuel(Z.sortedFuel[i]);
          return true;
        }
    }
    return false;
  }

  int nearbyResources() {
  	int res = 0;
  	for(int dx = -5; dx <= 5; dx++) for(int dy = -5; dy <= 5; dy++)
		  if (Math.abs(dx) + Math.abs(dy) <= 5)
		    if (Z.containsResource(Z.CUR.x+dx, Z.CUR.y+dy)) res++;
  	return res;
  }


  Action2 makeClosePilgrim() {
    double a = Z.karbonite, b = (Z.fuel-Z.FUEL_RATIO*Z.U.totAttackers())/5.0;
    boolean assigned = false;

    pi bes = null;
    int bestDist = MOD;
    for(int i = 0; i < Z.karbcount; i++)
      if (!isOccupiedKarb[Z.sortedKarb[i]] && !Z.badResource[Z.karbPos[Z.sortedKarb[i]]]) {
        int d = Z.euclidDist(Z.karbPos[Z.sortedKarb[i]]);
        if (d < bestDist) {
          bestDist = d;
          bes = new pi(0,i);
        }
      }

    for (int i = 0; i < Z.fuelcount; i++)
      if (!isOccupiedFuel[Z.sortedFuel[i]] && !Z.badResource[Z.fuelPos[Z.sortedFuel[i]]]) {
        int d = Z.euclidDist(Z.fuelPos[Z.sortedFuel[i]]);
        if (d < bestDist) {
          bestDist = d;
          bes = new pi(1,i);
        }
      }

    if (bes == null) return null;
    if (bes.f == 0) assignKarb(Z.sortedKarb[bes.s]);
    else assignFuel(Z.sortedFuel[bes.s]);
    return Z.tryBuild(PILGRIM);
  }

  Action2 makePilgrim() {
    double a = Z.karbonite, b = (Z.fuel-Z.FUEL_RATIO*Z.U.totAttackers())/5.0;
    boolean assigned = false;

    if (Z.CUR.turn <= 30) { // take karbonite, expand
      if (closeKarb() > closePilgrim()) assigned = tryAssignKarb();
      else assigned = tryAssignAggressive();
    } else {
      if (closeResources() > closePilgrim()) return makeClosePilgrim();
      if (2*numKarb <= numFuel) assigned = tryAssignKarb();
      else if (2*numFuel <= numKarb) assigned = tryAssignFuel();
      else if (a < b) assigned = tryAssignKarb();
      else assigned = tryAssignFuel();
    }
    if (!assigned) return null; // assignRand();
    return Z.tryBuild(PILGRIM);
  }

  Action2 fillResources() {
    boolean assigned = assignCloseUnexplored();
    if (!assigned) return null;
    return Z.tryBuild(PILGRIM);
  }

  Robot2 newPilgrim() { // closest pilgrim with signal PILGRIM, within distance 3
    int bestDist = MOD; Robot2 P = null;
    for (int dx = -3; dx <= 3; ++dx) for (int dy = -3; dy <= 3; ++dy) {
      int d = dx*dx+dy*dy; if (d > bestDist) continue;
      int x = Z.me.x+dx, y = Z.me.y+dy;
      if (Z.yourRobot(x,y)) {
        Robot2 R = Z.robotMap[y][x];
        if (R.unit == PILGRIM && R.castle_talk == PILGRIM) {
          bestDist = d;
          P = R;
        }
      }
    }
    return P;
  }

  void checkEscort(int t) {
    if (Z.euclidDist(t) <= 100) return;
    int x = Z.fdiv(t,64), y = t%64;
    for (int i = -5; i <= 5; ++i) for (int j = -5; j <= 5; ++j) if (i*i+j*j <= 25) {
      int X = x+i, Y = y+j;
      if (Z.valid(X,Y) && Z.sentEscort[X][Y]) return;
    }
    /*if (Z.hsim) {
      if (Math.abs(2*y+1-Z.h) > 16) return;
    } else {
      if (Math.abs(2*x+1-Z.w) > 16) return;
    }*/
    int bestDist = MOD;
    for (int i = -4; i <= 4; ++i) for (int j = -4; j <= 4; ++j) if (i*i+j*j <= 16) {
      int X = x+i, Y = y+j;
      if (Z.valid(X,Y) && !Z.containsResource(X,Y)) {
        int d;
        if (Z.hsim) d = Math.abs(2*Y+1-Z.h);
        else d = Math.abs(2*X+1-Z.w);
        if (d < bestDist) {
          bestDist = d;
          Z.escortPos = new pi(X,Y);
        }
      }
    }
  }

  void updatePilgrimID() {
    if (Z.assignedPilgrimPos == null) return;
    Robot2 R = newPilgrim();
    if (R == null) {
      Z.log("NO PILGRIM?");
      Z.assignedPilgrimPos = null;
      return;
    }
    if (Z.assignedPilgrimPos.f == 0) {
      Z.pilToKarb[R.id] = Z.assignedPilgrimPos.s;
      Z.log(R.id+" IS KARB PILGRIM "+Z.pilToKarb[R.id]);
      checkEscort(Z.karbPos[Z.pilToKarb[R.id]]);
    } else {
      Z.pilToFuel[R.id] = Z.assignedPilgrimPos.s;
      Z.log(R.id+" IS FUEL PILGRIM "+Z.pilToFuel[R.id]);
      checkEscort(Z.fuelPos[Z.pilToFuel[R.id]]);
    }

    Z.assignedPilgrimPos = null;
  }

  void dumpTroopInfo() {
    String T = "";
    T += Z.CUR.turn+" "+Z.toString(Z.myCastle);
    T += "| ";
    for (int i = 0; i < 6; ++i) T += Z.U.totUnits[i]+" ";
    Z.log(T);
  }

  boolean shouldPilgrim() {
    if (Z.nextSignal != null || !Z.canBuild(PILGRIM)) return false;
    int totResource = Z.fuelcount+Z.karbcount;
    if (Z.U.totUnits[PILGRIM] >= totResource/2) return false;
    if (Z.CUR.turn <= 20 && Z.U.totUnits[PILGRIM] < Math.min(Z.fdiv(totResource,2),4)) return true;
    if (Z.euclidDist(Z.CUR,Z.closestAttacker(Z.CUR,1-Z.CUR.team)) <= 64) return false;
    return Z.myPilgrim <= Z.U.closeAttackers() && 20*Z.U.totUnits[PILGRIM] <= Z.fuel;
  }

  Action2 castleBuild() {
    // if (Z.CUR.team == 1) return Z.tryBuild(CRUSADER);
    if (Z.CUR.turn == 1) return null;
    Action2 A = panicBuild(); if (A != null) return A;
    if (Z.escortPos != null) return tryBuildEscort();
    // Z.log("WHAT "+Z.shouldSave+" "+Z.U.closeAttackers()+" "+shouldBuild);
    if (!shouldBuild && (Z.karbonite < 80 || Z.fuel < 250)) return null;
    if (Z.U.closeAttackers() < 20 && Z.karbonite > 195 && Z.fuel > 1800) {
      // Z.log("SAFE??");
      return safeBuild();
    }
    if (shouldPilgrim()) return makePilgrim();
    if (Z.me.turn >= 920 && Z.fuel >= 6000-50*(1000-Z.me.turn)) return spamBuild();
    if (Z.canBuild(PILGRIM) && closeResources() > closePilgrim()) return makePilgrim();
    if (Z.canBuild(PILGRIM) && Z.CUR.turn > 100) {
      A = fillResources();
      // Z.log("HA "+(A == null));
    }
    if (A != null) return A;
    if (Z.shouldSave || Z.lastSecretAttack >= Z.CUR.turn-30) return null;
    return safeBuild();
  }

  Action2 run() {
    if (Z.me.turn == 1) initVars();
    determineCastleLoc(); updatePilgrimID(); updateAttackerID(); updateVars();
    if (Z.isSuperSecret && !Z.continuedChain) return Z.tryBuildSecret(PILGRIM);
    Action2 A = castleBuild(); if (A != null && A.type != -1) return A;
    return tryAttack();
  }
}
