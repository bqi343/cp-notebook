// Don't place your source in a package
import java.util.*;
import java.lang.*;
import java.io.*;

class BinaryIndexedTree {
	int SZ = 100000;
	int[] bit = new int[SZ+1];
	
	BinaryIndexedTree() {}
	
	void upd(int k, int val) {
		for( ;k <= SZ; k += (k&-k)) bit[k] += val;
	}
	 
	int query(int k) {
		int temp = 0;
		for (;k > 0;k -= (k&-k)) temp += bit[k];
		return temp;
	}
	
	int query(int l, int r) {
		return query(r)-query(l-1);
	}
}

class Main {
	public static void main(String args[]) {
		BinaryIndexedTree b = new BinaryIndexedTree();
		b.upd(5,2);
		b.upd(4,1);
		System.out.println(b.query(3,5));
	}
}
 