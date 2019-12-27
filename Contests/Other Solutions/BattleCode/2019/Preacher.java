package bc19;

import static bc19.Consts.*;

public class Preacher extends Attackable {
    public Preacher(MyRobot z) { super(z); }
    Action2 run() { 
    	// Z.dumpCastles();
    	return runDefault(); 
    }
}
