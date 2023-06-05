#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <vector>

using namespace std;

enum TokenType {
	PRINT,			// 0
	VARIABLE,		// 1
	INTEGER,		// 2
	STRING,			// 3
	OPERATOR,		// 4
	PUNCTUATION,	// 5
	SEMICOLON,		// 6
	END				// 7
};

vector<string> TokenType_array = {"PRINT", "VARIABLE", "INTEGER", "STRING", "OPERATOR", "PUNCTUATION", "SEMICOLON", "END"};

class Token {
private:
	TokenType type;	
	string lexeme;
	int pos;
	int line;

public:

	Token() { pos = 0; lexeme = ""; line = 0; };

	Token(TokenType p_token_type) { type = p_token_type; }

	~Token() = default;

	TokenType get_type() const { return type; }
	string get_lexeme() const { return lexeme; }
	int get_pos() const { return pos; }
	int get_line() const { return line; }

	void set_type(TokenType p_type) { type = p_type; }
	void set_lexeme(string p_lexeme) { lexeme = p_lexeme; }
	void set_pos(int p_pos) { pos = p_pos; }
	void set_line(int p_line) { line = p_line; }
};

#endif
