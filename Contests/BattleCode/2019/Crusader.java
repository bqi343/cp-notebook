package bc19;

import static bc19.Consts.*;

public class Crusader extends Attackable {
    public Crusader(MyRobot z) { super(z); }
    Action2 run() {
        return runDefault(); 
        /*Z.sendToCastle();
        Action2 A = react(); 
        if (A != null) {
        	Z.log("REACT (" +Z.CUR.x+", "+Z.CUR.y+") "+A.type+" "+A.dx+" "+A.dy);
        	return A;
        }
    	Z.log("PATROL (" +Z.CUR.x+", "+Z.CUR.y+")");
        return patrol();*/
        // return aggressive();
    }
}
