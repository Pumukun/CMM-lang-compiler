#ifndef LEXER_HPP
#define LEXER_HPP
#pragma once

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
		KEYWORD,		// 0
		IDENTIFIER,		// 1
		INTEGER,		// 2
		STRING,			// 3
		OPERATOR,		// 4
		PUNCTUATION,	// 5
		END				// 6
	};

	struct Token {
		TokenType type;
		string lexeme;
	};

	unordered_set<string> keywords = {"print", "int", "string"};

	bool is_digit(char c) { return c >= '0' && c <= '9'; }

	bool is_alpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

	bool is_operator(char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '='; }
	
	bool is_punctuation(char c) { return c == '(' || c == ')'; }

	Token next_token(const string &input, int &pos) {
		Token token;
		string lexeme;

		while (pos < input.length()) {
			char c = input[pos];

			if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
				pos++;
				continue;
			}

			if (c == '\"') {
				pos++;

				while (pos < input.length() && input[pos] != '\"') {
					token.lexeme += input[pos];
					pos++;
				}
				
				token.type = STRING;
				pos++;
				return token;
			}

			if (is_digit(c)) {
				lexeme += c;
				pos++;

				while (pos < input.length() && is_digit(input[pos])) {
					lexeme += input[pos];
					pos++;
				}

				token.type = INTEGER;
				token.lexeme = lexeme;
				return token;
			}

			if (is_alpha(c)) {
				lexeme += c;
				pos++;

				while (pos < input.length() && (is_alpha(input[pos]) || is_digit(input[pos]))) {
					lexeme += input[pos];
					pos++;
				}

				if (keywords.find(lexeme) != keywords.end()) {
					token.type = KEYWORD;
				} else token.type = IDENTIFIER;

				token.lexeme = lexeme;
				return token;
			}

			if (is_operator(c)) {
				lexeme += c;
				pos++;

				while (pos < input.length() && is_operator(input[pos])) {
					lexeme += input[pos];
					pos++;
				}

				token.type = OPERATOR;
				token.lexeme = lexeme;
				return token;
			}

			if (is_punctuation(c)) {
				lexeme += c;
				pos++;

				while (pos < input.length() && is_punctuation(input[pos])) {
					lexeme += input[pos];
					pos++;
				}

				token.type = PUNCTUATION;
				token.lexeme = lexeme;
				return token;
			}
			pos++;
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
			case KEYWORD:
				cur_type = "KEYWORD";
				break;
			case IDENTIFIER:
				cur_type = "IDENTIFIER";
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

			grammar.push_back({token.type, cur_type, token.lexeme});
		} while (token.lexeme != "");

		grammar.pop_back();
	}

	void lexer_output() {
		for (trio<int, string, string> &i : grammar)
			cout << "[Type: " << i.first 
				 << ", Type_str: " << i.second 
				 << ", Lexeme: " << i.third << "]\n";
	}

	vector<trio<int, string, string>> get_grammar() { return grammar; }

private:
	vector<trio<int, string, string>> grammar;
};

#endif