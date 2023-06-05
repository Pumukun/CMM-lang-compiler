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
			throw runtime_error("expected: " + TokenType_array[p_expected] + " on position: " + to_string(pos) + "\n");
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
		pos += 2;	
		return new AST_Node();
	}

	AST_Node* parse_print() {
		cout << "print " + tokens[pos].get_lexeme() << endl;
		return new AST_Node(tokens[pos]);
	}

	AST_Node* parse_var() {
		
	}

public:

	AST_Node* parse_code() {
		AST_Node* root = new AST_Node();

		while (pos < (int)tokens.size()) {
			if (match(VARIABLE).get_type() != END) {
				require(OPERATOR);
				
				pos--;
				if (tokens[pos].get_lexeme() != "=")
					throw runtime_error("expected: = after variable! on position: " + to_string(pos));
				pos++;

				if (tokens[pos].get_lexeme() == "-")
					pos++;
				
				parse_formula();
			}
			
			if (match(PRINT).get_type() != END) {
				if (tokens[pos].get_type() == VARIABLE || tokens[pos].get_type() == INTEGER || tokens[pos].get_type() == STRING)
					parse_print();
				throw runtime_error("expected: VAR || INT || STR after print!");
			}
		}

		return root;
	}
	/*	
	AST_Node* run_code(auto p_node) {
		ifstream in("prog.txt");
		string result;
		if (in.is_open()) {
			if(typeid(p_node) == typeid(Number_Node)) {
				in << p_node << endl;
			}
			if (typeid(p_node) == typeid(Unar_oper_Node)) {
				switch (p_node.oper.get_type()) {
					case PRINT: 
						in << "std::cout << "<< (p_node.oper.get_lexeme());
					default:
						break;
				}
			} 
			if (typeid(p_node) == typeid(Binary_oper_Node)) {
				string cur_lex = p_node.oper.get_lexeme();
				AST_Node result;
				if (cur_lex == "+") {
					result = run_code(p_node.left_node + p_node.right_node);
					in << result << endl;
				}
				if (cur_lex == "-") {
					result = run_code(p_node.left_node - p_node.right_node);
					in << result << endl;
				}
				if (cur_lex == "=") {
					const AST_Node* right_result = run_code(p_node.right_node);
					const AST_Node* variablenode = p_node.get_left_node();
					result = right_result = variablenode;
					in << result << endl;
				}
				if (scope(cur_lex)) {
					scope(cur_lex);
				} else cout << "variable not exist" << endl;

				for (auto&i:p_node.MyNode) { run_code(i); }
			}

		in.close();
		}
	}
	*/
};

#endif

