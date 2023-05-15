#include <iostream>
#include <string>

#include "Lexer.hpp"

using namespace std;

int main() {
	cout << "Enter file path: ";
	string file_path;
	cin >> file_path;

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

