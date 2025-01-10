#include <iostream>

#define print_int(expr)  std::cout << "print_int("  << #expr << "): " << expr << std::endl;
#define print_char(expr) std::cout << "print_char(" << #expr << "): " << expr << std::endl;
#define print_bool(expr) std::cout << "print_bool(" << #expr << "): " << expr << std::endl;


// vars.cpp: g++ driver.cpp -Dvars
#ifdef vars
#include "vars.cpp"
#endif

// refs.cpp: g++ driver.cpp -Drefs
#ifdef refs
#include "refs.cpp"
#endif

// expr.cpp: g++ driver.cpp -Dexpr
#ifdef expr
#include "expr.cpp"
#endif
