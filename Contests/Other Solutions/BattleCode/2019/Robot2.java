package bc19;

import java.util.*;
import java.math.*;

import static bc19.Consts.*;

public class Robot2 {
	int id = -1, unit = -1, health = -1, team = -1, x = -1, y = -1;
	int fuel = -1, karbonite= -1, turn= -1;
	int signal = -1, signal_radius = -1, castle_talk = -1;

	public Robot2(Robot R) {
        if (R != null) {
    		if (R.id >= 0) id = R.id;
    		if (R.unit >= 0) unit = R.unit;
    		if (R.health >= 0) health = R.health;
    		if (R.team >= 0) team = R.team;
    		if (R.x >= 0) x = R.x;
    		if (R.y >= 0) y = R.y;
    		if (R.fuel >= 0) fuel = R.fuel;
    		if (R.karbonite >= 0) karbonite = R.karbonite;
    		if (R.turn >= 0) turn = R.turn;
    		if (R.signal >= 0) signal = R.signal;
    		if (R.signal_radius >= 0) signal_radius = R.signal_radius;
    		if (R.castle_talk >= 0) castle_talk = R.castle_talk;
        }
	}
    
    boolean isStructure() { 
        return unit != -1 && unit <= 1; 
    }

    boolean isAttacker(int t) {
    	return team == t && unit != -1 && CAN_ATTACK[unit];
    }

    String coordinates() {
        return "("+x+", "+y+")";
    }

    String getInfo() {
    	String res = "";
    	res += id+" ";
    	res += unit+" ";
    	res += team+" ";
    	res += coordinates()+" ";
    	res += castle_talk+" ";
    	res += signal+" ";
    	res += "|\n";
        return res;
    }
};