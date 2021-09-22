alias clr="printf '\33c'"
co() { g++ -std=c++17 -O2 -Wall -Wextra -Wshadow -Wconversion -o $1 $1.cpp; }
run() { co $1 && ./$1; }