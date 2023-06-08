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

using namespace std;

class Parser {
public:

	Parser(vector<Token> p_tokens):
		tokens(move(p_tokens)), 
		index(0)  
	{ }

	~Parser() = default;

private:

	vector<Token> tokens;
	int index;
	map<string, int> scope_int;
	map<string, string> scope_str;

private:

	Token match(TokenType p_expected) {
		if (index < (int)tokens.size()) {
			const Token cur_Token = tokens[index];
			if (p_expected == cur_Token.get_type()) {
				index++;
				return cur_Token;
			}
		}
		return Token(END);
	}

	Token require(TokenType p_expected) {
		const Token token = match(p_expected);
		if (token.get_type() == END) { 
			throw runtime_error("expected: " + TokenType_array[p_expected] + " on position: " + to_string(tokens[index].get_pos()) + "\n");
		}
		return token;
	}
	
	AST_Node* parse_formula() {
		Token tmp_Token = tokens[index];
		int tmp_type = tmp_Token.get_type();
		
		string formula = "";

		while (tmp_type == OPERATOR || tmp_type == VARIABLE || tmp_type == INTEGER || tmp_type == PUNCTUATION) {
			tmp_Token = tokens[index]; 
			tmp_type = tmp_Token.get_type();
			if (tmp_type == SEMICOLON) break;
			formula = formula + tmp_Token.get_lexeme();
			index++;
		}

		cout << formula << "\n" << index << endl;
		index++;
		
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
		cout << "print " + tokens[index].get_lexeme() << endl;
		index++;
		require(SEMICOLON);
		return new AST_Node(tokens[index]);
	}

	AST_Node* parse_var() {
		if (tokens[index].get_type() == OPERATOR && tokens[index].get_lexeme() != "-")
			throw runtime_error("expected \"-\" on index: " +  to_string(tokens[index].get_pos()));
		AST_Node* res = new AST_Node(tokens[index]);
		index++;
		return res;
	}

public:

	AST_Node* parse_code() {
		AST_Node* root = new AST_Node();

		while (index < (int)tokens.size()) {
			if (match(VARIABLE).get_type() != END) {
				string tmp_var = tokens[index - 1].get_lexeme();

				require(ASSIGN);
				
				
				if (tokens[index - 1].get_lexeme() != "=")
					throw runtime_error("expected: = after variable! on position: " + to_string(tokens[index].get_pos()));

				if (tokens[index].get_type() == INTEGER) {
					string tmp_str = tokens[index].get_lexeme();

					AST_Node* f_node = new AST_Node();
					if ((int)tmp_str.find("-") != -1 || (int)tmp_str.find("-") == 0 || (int)tmp_str.find("/") != -1 || (int)tmp_str.find("*") != -1) {
						f_node = parse_var();
						scope_int[tmp_var] = stoi(f_node->get_token().get_lexeme());
					} else { f_node = parse_formula(); }

					scope_int[tmp_var] = stoi(f_node->get_token().get_lexeme());
					insert_right(root, f_node);
				} else if (tokens[index].get_type() == STRING) {
					index++;
					scope_str[tmp_var] = tokens[index].get_lexeme();
				}
			}
			
			if (match(PRINT).get_type() != END) {
				if (tokens[index].get_type() == VARIABLE || tokens[index].get_type() == INTEGER || tokens[index].get_type() == STRING)
					parse_print();
				else throw runtime_error("expected: VAR || INT || STR after print!");
			}

			if (tokens[index].get_type() == END) return root;
		}
		return root;
	}
};

#endif

