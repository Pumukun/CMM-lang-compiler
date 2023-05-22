#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "trio.hpp"

using namespace std;

class Lexer {
public:

	Lexer() = default;

	~Lexer() = default;

private:
	 
	enum TokenType {
		PRINT,			// 0
		VARIABLE,		// 1
		INTEGER,		// 2
		STRING,			// 3
		OPERATOR,		// 4
		PUNCTUATION,	// 5
		END				// 6
	};

	struct Token {
		TokenType type;
		string lexeme;
		int pos;
	};

	unordered_set<string> keywords = {"print"};

	bool is_digit(char c) { return c >= '0' && c <= '9'; }

	bool is_alpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

	bool is_operator(char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '='; }
	
	bool is_punctuation(char c) { return c == '(' || c == ')'; }

	Token next_token(const string &input, int &pos) {
		Token token;
		string lexeme;

		while (pos < (int)input.length()) {
			char c = input[pos];

			if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
				pos++;
				continue;
			}

			if (c == '\"') {
				pos++;

				while (pos < (int)input.length() && input[pos] != '\"') {
					token.lexeme += input[pos];
					pos++;
				}
				
				token.type = STRING;
				token.pos = pos - (int)lexeme.size();
				pos++;
				return token;
			}

			if (is_digit(c)) {
				lexeme += c;
				pos++;

				while (pos < (int)input.length() && is_digit(input[pos])) {
					lexeme += input[pos];
					pos++;
				}

				token.type = INTEGER;
				token.lexeme = lexeme;
				token.pos = pos - (int)lexeme.size();
				return token;
			}

			if (is_alpha(c)) {
				lexeme += c;
				pos++;

				while (pos < (int)input.length() && (is_alpha(input[pos]) || is_digit(input[pos]))) {
					lexeme += input[pos];
					pos++;
				}

				if (keywords.find(lexeme) != keywords.end()) {
					token.type = PRINT;
				} else token.type = VARIABLE;

				token.lexeme = lexeme;
				token.pos = pos - (int)lexeme.size();
				return token;
			}

			if (is_operator(c)) {
				lexeme += c;
				pos++;

				while (pos < (int)input.length() && is_operator(input[pos])) {
					lexeme += input[pos];
					pos++;
				}

				token.type = OPERATOR;
				token.lexeme = lexeme;
				token.pos = pos - (int)lexeme.size();
				return token;
			}

			if (is_punctuation(c)) {
				lexeme += c;
				pos++;

				while (pos < (int)input.length() && is_punctuation(input[pos])) {
					lexeme += input[pos];
					pos++;
				}

				token.type = PUNCTUATION;
				token.lexeme = lexeme;
				token.pos = pos - (int)lexeme.size();
				return token;
			}
			pos++;

			if (!is_alpha(c) && !is_digit(c) && !is_operator(c) && !is_punctuation(c)) {
				string msg = "Error on position: " + to_string(pos) + "\n";
				syntax_errors.push_back(msg);
			}
		}

		token.type = END;
		token.lexeme = "";
		return token;
	}

public:

	void generate_grammar(string path) {
		ifstream file(path);
		stringstream buffer;
		string line;
    
		if (file.is_open()) {
			while (getline(file, line))
				buffer << line << "\n";

			file.close();
		} else cout << "Unable to open file\n";
    
		string file_contents = buffer.str();

		int pos = 0;
		Token token;

		string cur_type;

		do {
			token = next_token(file_contents, pos);
			switch (token.type) {
			case PRINT:
				cur_type = "PRINT";
				break;
			case VARIABLE:
				cur_type = "VARIABLE";
				break;
			case INTEGER:
				cur_type = "INTEGER";
				break;
			case STRING:
				cur_type = "STRING";
				break;
			case OPERATOR:
				cur_type = "OPERATOR";
				break;
			case PUNCTUATION:
				cur_type = "PUNCTUATION";
				break;
			case END:
				cur_type = "END";
				break;
			default:
				cur_type = "NONE";
				break;
			}

			grammar.push_back({token.pos, cur_type, token.lexeme});
		} while (token.lexeme != "");

		grammar.pop_back();
	}

	void lexer_output() {
		if (syntax_errors.empty()) {
			for (trio<int, string, string> &i : grammar)
				cout << "[Pos: " << i.first 
					<< ", Type: " << i.second 
					<< ", Lexeme: " << i.third << "]\n";
		} else {
			cout << "Token Error(s)!\n";
			for (string &i : syntax_errors)
				cout << i;
		}
	}

	vector<trio<int, string, string>> get_grammar() { return grammar; }
	vector<string> get_syntax_errors() { return syntax_errors; }

private:
	vector<trio<int, string, string>> grammar;
	vector<string> syntax_errors;
};

#endif
