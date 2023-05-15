#include <iostream>
#include <string>

#include "Lexer.hpp"

using namespace std;

int main(int argc, char** argv) {
	if (argc > 2) {
		cout << "too many arguments!\n";
		return -1;
	}
	if (argc == 1) {
		cout << "no arguments!\n";
		return -1;
	}
	
	string file_path = argv[1];

	Lexer lex;
	
	lex.generate_grammar(file_path);  

	lex.lexer_output();
    
    return 0;
}

// input:
/*
int a
a = 4
int b
b = 7
a = b + 7
print a
*/

// output:
/*
[Type: -1, Value: int]
[Type: 0, Value: a]
[Type: 0, Value: a]
[Type: 3, Value: =]
[Type: 1, Value: 5]
[Type: -1, Value: int]
[Type: 0, Value: b]
[Type: 0, Value: b]
[Type: 3, Value: =]
[Type: 1, Value: 8]
[Type: 0, Value: a]
[Type: 3, Value: =]
[Type: 0, Value: b]
[Type: 3, Value: +]
[Type: 1, Value: 8]
[Type: -1, Value: print]
[Type: 0, Value: a]
*/

