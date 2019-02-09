package bc19;

import static bc19.Consts.*;

public class Movable {
  public MyRobot Z;
  public Movable (MyRobot z) { Z = z; }

  public boolean containsConfident(int x, int y) {
    for (int i = x-1; i <= x+1; ++i) for (int j = y-1; j <= y+1; ++j)
    if (Z.enemyRobot(i,j) && Z.lastTurn[j][i] >= Z.CUR.turn-1) return true;
    return false;
  }
  Action2 moveClose(int x, int y) {
    int bestDist = Z.euclidDist(Z.CUR,x,y); Action2 bestMove = null;
    for (int i = -3; i <= 3; ++i) for (int j = -3; j <= 3; ++j)
    if (Z.canMove(Z.CUR,i,j)) {
      int dist = Z.sq(Z.CUR.x+i-x)+Z.sq(Z.CUR.y+j-y);
      if (dist < bestDist) {
        bestDist = dist;
        bestMove = Z.moveAction(i,j);
      }
    }
    return bestMove;
  }
  Action2 moveAway(int x, int y) {
    int farthest = Z.euclidDist(Z.CUR,x,y); Action2 best = null;
    for (int i = -3; i <= 3; i++) for (int j = -3; j <= 3; j++)
    if (Z.canMove(Z.CUR,i,j)) {
      int dis = Z.sq(x - Z.CUR.x - i) + Z.sq(y - Z.CUR.y - j);
      if (dis > farthest) {
        farthest = dis;
        best = Z.moveAction(i, j);
      }
    }
    return best;
  }
  Action2 moveAway(int t) { return t == MOD ? null : moveAway(Z.fdiv(t,64),t%64); }
  Action2 moveAway(Robot2 R) { return R == null ?  null : moveAway(R.x, R.y); }

  // GIVE
  boolean enoughResources() {
    if (Z.CUR.karbonite <= 5 && Z.CUR.fuel <= 25) return false;
    return true;
  }
  boolean enoughResourcesGive(Robot2 R) {
    int karb = Math.min(Z.CUR.karbonite,20-R.karbonite);
    int fuel = Math.min(Z.CUR.fuel,100-R.fuel);
    if (karb <= 5 && fuel <= 25) return false;
    if (Z.CUR.unit == PILGRIM && Z.danger[Z.CUR.y][Z.CUR.x] == 0) {
      if (Z.karboniteMap[Z.CUR.y][Z.CUR.x] && Z.CUR.karbonite < 20) return false;
      if (Z.fuelMap[Z.CUR.y][Z.CUR.x] && Z.CUR.fuel < 100) return false;
    }
    return true;
  }
  Action2 give(Robot2 R) {
    int karb = Math.min(Z.CUR.karbonite,20-R.karbonite);
    int fuel = Math.min(Z.CUR.fuel,100-R.fuel);
    return Z.giveAction(R.x-Z.CUR.x,R.y-Z.CUR.y,karb,fuel);
  }
  boolean canGive(Robot2 R) {
    return R.team == Z.CUR.team && Z.adjacent(Z.CUR,R) && enoughResourcesGive(R);
  }
  Action2 tryGive() {
    int bestVal = -MOD; Action2 bestGive = null;
    int t = Z.bfs.closestStruct(true);
    for (Robot2 R: Z.robots) if (canGive(R)) {
      int val = 0;
      if (R.isStructure()) val += MOD;
      val -= Z.euclidDist(Z.fdiv(t,64),t%64,R.x,R.y);
      if (val > bestVal) {
        bestVal = val;
        bestGive = give(R);
      }
    }
    return bestGive;
  }

  Action2 returnHome() {
    if (Z.CUR.unit == PILGRIM) return Z.safe.moveYourStruct();
    return Z.bfs.moveYourStruct();
  }
  Action2 giveHomeNoMove() {
    int t = Z.bfs.closestStruct(true), d;
    if (Z.CUR.unit == PILGRIM) d = Z.safe.giveDist(t);
    else d = Z.bfs.giveDist(t);
    if (Z.euclidDist(t) <= 2 || (Z.euclidDist(t) <= 9 && d > churchThreshold)) {
      Action2 A = tryGive();
      /*if (Z.euclidDist(t) > 2 && A != null) {
        Z.log("WHAT GIVE "+t+" "+Z.euclidDist(t)+" "+d+" "+churchThreshold+" "+Z.CUR.x+" "+Z.CUR.y);
      }*/
      if (A != null) return A;
    }
    return null;
  }
  Action2 giveHome() {
    Action2 A = giveHomeNoMove(); if (A != null) return A;
    return returnHome();
      /*if (A == null && Z.euclidDist(t) <= 2) {
        Z.log("WHAT "+Z.CUR.x+" "+Z.CUR.y);
        for (Robot2 R: Z.robots) if (Z.adjacent(Z.CUR,R) && R.isStructure()) {
          Z.log("HUH "+enoughResourcesGive(R)+" "+Z.CUR.karbonite+" "+Z.CUR.fuel);
          Z.log("ZZ "+Math.min(Z.CUR.karbonite,20-R.karbonite)+" "+Math.min(Z.CUR.fuel,100-R.fuel));
        }
      }*/
  }
}
