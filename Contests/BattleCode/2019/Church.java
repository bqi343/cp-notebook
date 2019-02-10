package bc19;

import static bc19.Consts.*;

public class Church extends Building {
  public Church(MyRobot z) { super(z); }

  int decideSuperSecret() {
    if (Z.euclidDist(Z.CUR.x, Z.CUR.y, Z.fdiv(Z.destination,64), Z.destination%64) > 100) return MOD;
    int t = Z.mostDangerousPreacher(Z.CUR); if (t == MOD) return MOD;
    return PREACHER;
  }

  boolean closestChurch() {
    if (Z.CUR.unit != CHURCH) return false;
    int d = Z.destination;
    for (int i = -10; i <= 10; ++i) for (int j = -10; j <= 10; ++j)
      if (i*i+j*j <= 100) {
        int x = Z.CUR.x+i, y = Z.CUR.y+j;
        if (Z.yourStruct(x,y) && Z.euclidDist(x,y,Z.fdiv(d,64),d%64) < Z.euclidDist(d)) return false;
      }
    return true;
  }

  Action2 runSuperSecret() {
    // if (Z.CUR.team == 0 && closestChurch()) Z.log("AHA "+Z.CUR.x+" "+Z.CUR.y);
    boolean buildPilgrim = true;
    if (Z.continuedChain && !closestChurch()) buildPilgrim = false;
    if (Z.shouldStopChain()) buildPilgrim = false;

    if (buildPilgrim) return Z.tryBuildSecret(PILGRIM);
    int t = decideSuperSecret();
    Action2 A = (t == MOD) ? null : Z.tryBuildSecret(decideSuperSecret());
    if (A == null) return new Action2();
    return A;
  }

  public Action2 run() {
    if (Z.isSuperSecret && (Z.CUR.turn <= 5 || !Z.continuedChain)) {
      Action2 A = runSuperSecret();
      if (A != null) return A;
    }
    if (Z.patrolcount == 0) initPatrol();
    updateAttackerID(); updatePatrolVars();
    Action2 A = panicBuild(); if (A != null) return A;

    if (Z.isSuperSecret) return null;
    if (Z.shouldSpam) {
      if (Z.lastSpam >= 9 || Z.CUR.turn <= 9) return Z.tryBuildEconSpam(PILGRIM);
      return null;
    }
    if (seenResources() > seenPilgrim()) A = Z.tryBuildNoSignal(PILGRIM);
    // Z.log("HUH "+Z.U.closeAttackers());
    if (A == null && Z.U.closeAttackers() < 20 && Z.karbonite > 200 && Z.fuel > 1800) return safeBuild();
    if (A == null && Z.karbonite > 2000 && Z.fuel > 10000) return safeBuild();
    if (Z.me.turn >= 900 && A == null) A = spamBuild();
    return A;
  }
}
