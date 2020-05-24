class BIT() {
    val v = LongArray(SZ)
    fun upd(_a: Int, b: Long) {
        var a = _a
        while (a < SZ) {
            v[a] += b
            a += (a and -a)
        }
    }
    fun query(_a: Int): Long {
        var a = _a
        var ans: Long = 0
        while (a > 0) {
            ans += v[a]
            a -= (a and -a)
        }
        return ans
    }
}