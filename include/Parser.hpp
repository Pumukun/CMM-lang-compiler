#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <string>
#include <cstdlib>
#include <typeinfo>

#include "AST.hpp"
#include "Token.hpp"

using namespace std;

class Parser {
public:

	Parser(vector<Token> p_tokens) {
		tokens = move(p_tokens);
		pos = 0;
	};

	~Parser() = default;

private:

	vector<Token> tokens;
	int pos;
	pair<string, int> scope;

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
			throw runtime_error("expected: " + to_string(p_expected) + " on position" + to_string(pos) + "\n");
		}
		return token;
	}

	Expression_Node pasre_var_or_num() {
		const Token number = match(INTEGER);

		if (number.get_type() != END) {
			return Number_Node(number);
		}
		const Token variable = match(VARIABLE);
		if (variable.get_type() != END) {
			return Variable_Node(variable);
		}

		throw runtime_error("expected num or var on pos: " + to_string(pos));
	}
	
	Expression_Node parse_print() {
		const Token token = match(PRINT);
		if (token.get_type() != END) {
			Expression_Node operand = parse_formula();
			return Unar_oper_Node(token, operand);
		}
		throw runtime_error("expected print {var || expr} on pos: " + to_string(pos));
	}

	Expression_Node parse_parentheses() {
		Token cur_token = match(PUNCTUATION);
		if (cur_token.get_type() != END && cur_token.get_lexeme() == "(") {
			const auto node = parse_formula();
			Token req_token = require(PUNCTUATION);
			if (req_token.get_lexeme() == ")")
				return node;
			else throw runtime_error("expected: ) on pos: " + to_string(pos));
		} else {
			return pasre_var_or_num();
		}
	}

	Expression_Node parse_formula() {
		auto left_node = parse_parentheses();
		auto oper = match(OPERATOR);
		while (oper.get_type() != END) {
			const auto right_node = parse_parentheses();
			const Binary_oper_Node left_node = Binary_oper_Node(oper, left_node, right_node);
			oper = match(OPERATOR);
		}
		return left_node;
	}

	Expression_Node parse_expression() {
		if (match(VARIABLE).get_type() == END) {
			const auto print_node = parse_print();
			return print_node;
		}
		pos--;
		auto var_node = pasre_var_or_num();
		const Token assign_oper = match(OPERATOR);
		if (assign_oper.get_type() != END && assign_oper.get_lexeme() == "=") {
			const auto right_formula_node = parse_formula();
			const auto binary_node = Binary_oper_Node(assign_oper, var_node, right_formula_node);
			return binary_node;
		}
		throw runtime_error("expected assing operator on pos" + to_string(pos));
	}
public:
	Expression_Node parse_code() {
		Statesment_Node root;
		
		while (pos < (int)tokens.size()) {
			const Expression_Node code_str_node = parse_expression();
			require(SEMICOLON);
			root.add_node(code_str_node);
		}

		return root;
	}
	
	Expression_Node run_code(auto p_node) {
		if(typeid(p_node) == typeid(Number_Node)) {
			return ;
		}
		if (typeid(p_node) == typeid(Unar_oper_Node)) {
			switch (p_node.oper.get_type()){
			case PRINT: 
				cout << (p_node.oper.get_lexeme());
			default:
				break;
			}
		} 
		if (typeid(p_node) == typeid(Binary_oper_Node)){
			string cur_lex = p_node.oper.get_lexeme();
			if (cur_lex == "+") {
				return run_code(p_node.left_node + p_node.right_node);
			}
			if (cur_lex == "-") {
				return run_code(p_node.left_node - p_node.right_node);
			}
			if (cur_lex == "=") {
				Expression_Node result = run_code(p_node.right_node);
				return result;
			}
			if (scope(cur_lex)) {
				return scope(cur_lex);
			} else cout << "variable not exist" << endl;

			for (auto&i:node.MyNode) { run_code(i); }
		}
	}
};

#endif

