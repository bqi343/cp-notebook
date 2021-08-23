int main() {
	setIO();
	FOR(i,-21,21) FOR(j,-21,21) if (j != 0) {
		db d = (db)i/j;
		assert(ceil(d) == cdiv(i,j));
		assert(floor(d) == fdiv(i,j));
	}
} // test floor, ceiling division