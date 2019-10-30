FILE="$1"
echo "TEST COMPILE "$FILE
echo "
#include \"../content/contest/template.cpp\"
#include \"../$FILE\"
" >build/temp.cpp
g++ -Wall -Wextra -Wfatal-errors -Wconversion -std=c++14 build/temp.cpp && rm a.out build/temp.cpp
# g++ -std=c++14 build/temp.cpp && rm a.out build/temp.cpp