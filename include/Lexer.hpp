#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "Token.hpp"

using namespace std;

class Lexer {
public:

	Lexer() = default;

	~Lexer() = default;

private:

	unordered_set<string> keywords = {"print"};

	bool is_digit(char c) { return c >= '0' && c <= '9'; }

	bool is_alpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

	bool is_operator(char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '='; }
	
	bool is_punctuation(char c) { return c == '(' || c == ')'; }

	bool is_semicolon(char c) { return c == ';'; }

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
					token.set_lexeme(token.get_lexeme() += input[pos]);
					pos++;
				}
				
				token.set_type(STRING);
				token.set_pos(pos - (int)lexeme.size());
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

				token.set_type(INTEGER);
				token.set_lexeme(lexeme);
				token.set_pos(pos - (int)lexeme.size());
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
					token.set_type(PRINT);
				} else token.set_type(VARIABLE);

				token.set_lexeme(lexeme);
				token.set_pos(pos - (int)lexeme.size());
				return token;
			}

			if (is_operator(c)) {
				lexeme += c;
				pos++;

				while (pos < (int)input.length() && is_operator(input[pos])) {
					lexeme += input[pos];
					pos++;
				}

				token.set_type(OPERATOR);
				token.set_lexeme(lexeme);
				token.set_pos(pos - (int)lexeme.size());
				return token;
			}

			if (is_punctuation(c)) {
				lexeme += c;
				pos++;

				token.set_type(PUNCTUATION);
				token.set_lexeme(lexeme);
				token.set_pos(pos - (int)lexeme.size());
				return token;
			}

			if (is_semicolon(c)) {
				lexeme += c;
				pos++;

				token.set_type(SEMICOLON);
				token.set_lexeme(lexeme);
				token.set_pos(pos - (int)lexeme.size());
				return token;
			}

			pos++;

			if (!is_alpha(c) && !is_digit(c) && !is_operator(c) && !is_punctuation(c)) {
				string msg = "Error on position: " + to_string(pos) + ", unknown Token: " + input[pos-1] + "\n";
				syntax_errors.push_back(msg);
			}
		}

		token.set_type(END);
		token.set_lexeme("");
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

		Token token;
		int pos = 0;

		do {
			token = next_token(file_contents, pos);
			grammar.push_back(token);
		} while (token.get_lexeme() != "");

		grammar.pop_back();
	}

	void lexer_output() {
		if (syntax_errors.empty()) {
			for (Token &i : grammar)
				cout << "[Pos: " << i.get_pos() 
					<< ", Type: " << i.get_type()
					<< ", Lexeme: " << i.get_lexeme() << "]\n";
		} else {
			cout << "Token Error(s)!\n";
			for (string &i : syntax_errors)
				cout << i;
		}
	}

	vector<Token> get_grammar() { return grammar; }
	vector<string> get_syntax_errors() { return syntax_errors; }

private:
	vector<Token> grammar;
	vector<string> syntax_errors;
};

#endif
