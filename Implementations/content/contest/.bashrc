alias clr="printf '\33c'"
co() { # on mac, add -Wl,-stack_size -Wl,0x10000000
    g++ -std=c++11 -O2 -Wall -Wextra -o $1 $1.cpp
}
run() {
    co $1 && ./$1
}