co() {
    g++ -std=c++11 -O2 -Wall -Wl,-stack_size -Wl,0x10000000 -o $1 $1.cc
}
run() {
    co $1 && ./$1
}