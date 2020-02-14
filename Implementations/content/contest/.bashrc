alias clr="printf '\33c'"
# on mac, add -Wl,-stack_size -Wl,0x10000000 to co
co() { g++-9 -std=c++11 -O2 -Wall -Wextra -o $1 $1.cpp; }
run() { co $1 && ./$1; } 