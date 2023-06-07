#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <typeinfo>
#include <map>

#include "AST.hpp"
#include "Token.hpp"
#include "Formula_Parser.hpp"

using namespace std;

class Parser {
public:

	Parser(vector<Token> p_tokens):
		tokens(move(p_tokens)), 
		pos(0)  
	{ }

	~Parser() = default;

private:

	vector<Token> tokens;
	int pos;
	map<string, int> scope_int;
	map<string, string> scope_str;

private:

	Token match(TokenType p_expected) {
		if (pos < (int)tokens.size()) {
			const Token cur_Token = tokens[pos];
			if (p_expected == cur_Token.get_type()) {
				pos++;
				return cur_Token;
			}
		}

		return Token(END);
	}

	Token require(TokenType p_expected) {
		const Token token = match(p_expected);
		if (token.get_type() == END) { 
			throw runtime_error("expected: " + TokenType_array[p_expected] + " on position: " + to_string(tokens[pos].get_pos()) + "\n");
		}
		return token;
	}
	
	AST_Node* parse_formula() {
		Token tmp_Token = tokens[pos];
		int tmp_type = tmp_Token.get_type();
		
		string formula = "";

		while (tmp_type == OPERATOR || tmp_type == VARIABLE || tmp_type == INTEGER || tmp_type == PUNCTUATION) {
			tmp_Token = tokens[pos]; 
			tmp_type = tmp_Token.get_type();
			if (tmp_type == SEMICOLON) break;
			formula = formula + tmp_Token.get_lexeme();
			pos++;
		}

		cout << formula << "\n" << pos << endl;
		pos++;
		
		for (auto const &i : scope_int) {
			int tmp_find = formula.find(i.first);
			if (tmp_find != -1) {
				formula[tmp_find] = static_cast<char>(i.second);
			}
		}

		Token res_token(INTEGER);
		res_token.set_lexeme(formula);

		return new AST_Node(res_token);
	}

	AST_Node* parse_print() {
		cout << "print " + tokens[pos].get_lexeme() << endl;
		pos++;
		require(SEMICOLON);
		return new AST_Node(tokens[pos]);
	}

	AST_Node* parse_var() {
		if (tokens[pos].get_type() == OPERATOR && tokens[pos].get_lexeme() != "-")
			throw runtime_error("expected \"-\" on pos: " +  to_string(tokens[pos].get_pos()));
		AST_Node* res = new AST_Node(tokens[pos]);
		pos++;
		return res;
	}

public:

	AST_Node* parse_code() {
		AST_Node* root = new AST_Node();

		while (pos < (int)tokens.size()) {
			if (match(VARIABLE).get_type() != END) {
				string tmp_var = tokens[pos - 1].get_lexeme();

				require(OPERATOR);
				
				
				if (tokens[pos - 1].get_lexeme() != "=")
					throw runtime_error("expected: = after variable! on position: " + to_string(tokens[pos].get_pos()));

				if (tokens[pos].get_type() == INTEGER) {
					string tmp_str = tokens[pos].get_lexeme();

					AST_Node* f_node = new AST_Node();
					if ((int)tmp_str.find("-") != -1 || (int)tmp_str.find("-") == 0 || (int)tmp_str.find("/") != -1 || (int)tmp_str.find("*") != -1) {
						f_node = parse_var();
						scope_int[tmp_var] = stoi(f_node->get_token().get_lexeme());
					} else { f_node = parse_formula(); }

					scope_int[tmp_var] = stoi(f_node->get_token().get_lexeme());
					insert_right(root, f_node);
				} else if (tokens[pos].get_type() == STRING) {
					pos++;
					scope_str[tmp_var] = tokens[pos].get_lexeme();
				}
			}
			
			if (match(PRINT).get_type() != END) {
				if (tokens[pos].get_type() == VARIABLE || tokens[pos].get_type() == INTEGER || tokens[pos].get_type() == STRING)
					parse_print();
				else throw runtime_error("expected: VAR || INT || STR after print!");
			}

			if (tokens[pos].get_type() == END) return root;
		}

		return root;
	}
};

#endif

