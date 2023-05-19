#include <iostream>

#include "Parser.hpp"
#include "Lexer.hpp"

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
