/*
 * Der Code in dieser Datei dient dazu, die Testfälle mit dem g++ oder clang kompilieren zu können.
 *
 * Ihr Interpreter bzw. Compiler muss diesen Code in dieser Datei nicht verarbeiten können!
 *
 */


#include <iostream>

#define print_int(expr)  std::cout << "print_int("  << #expr << "): " << expr << std::endl;
#define print_char(expr) std::cout << "print_char(" << #expr << "): " << expr << std::endl;
#define print_bool(expr) std::cout << "print_bool(" << #expr << "): " << expr << std::endl;
