#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

using namespace std;

enum TokenType {
	PRINT,			// 0
	VARIABLE,		// 1
	INTEGER,		// 2
	STRING,			// 3
	OPERATOR,		// 4
	PUNCTUATION,	// 5
	END				// 6
};

class Token {
private:
	TokenType type;	
	string lexeme;
	int pos;

public:

	Token() { pos = 0; lexeme = ""; };

	~Token() = default;

	TokenType get_type() { return type; }
	string get_lexeme() { return lexeme; }
	int get_pos() { return pos; }

	void set_type(TokenType p_type) { type = p_type; }
	void set_lexeme(string p_lexeme) { lexeme = p_lexeme; }
	void set_pos(int p_pos) { pos = p_pos; }
};

#endif
