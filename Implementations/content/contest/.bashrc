alias clr="printf '\33c'"
co() { g++ -std=c++11 -O2 -Wall -Wextra -DLOCAL -o $1 $1.cpp; }
run() { co $1 && ./$1; }