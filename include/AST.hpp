#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Token.hpp"

using namespace std;

class AST_Node {
private:

	Token token;
	AST_Node* left_node;
	AST_Node* right_node;	

public:

	AST_Node() = default;
	
	AST_Node(Token p_token) {
	 	token = p_token;
	}

	AST_Node(Token p_token, AST_Node* p_left_node, AST_Node* p_right_node) {
		token = p_token;
		left_node = p_left_node;
		right_node = p_right_node;
	}

	~AST_Node() = default;

	vector<AST_Node*> nodes;
	void add_node(AST_Node* p_node) {
		nodes.push_back(p_node);
	}
	
	void set_token(Token p_token) { p_token = token; }
	void set_left_node(AST_Node* p_left_node) { p_left_node = left_node; }
	void set_right_node(AST_Node* p_right_node) { p_right_node = right_node; }

	Token get_token() { return token; }
	AST_Node* get_left_node() { return left_node; }
	AST_Node* get_right_node() { return right_node; }	

	friend ostream &operator<< (ostream& out, AST_Node& node) {
		out << node.token.get_lexeme() << endl;
		return out;
	}
};

void print_tree(AST_Node* root, string prefix = "", bool is_left = true) {
	if (root == nullptr) {
		return;
	}

	cout << prefix;
	cout << (is_left ? "|-- " : "`-- ");
	cout << *root << endl;

	print_tree(root->get_left_node(), prefix + (is_left ? "|   " : "    "), true);
	print_tree(root->get_right_node(), prefix + (is_left ? "|   " : "    "), false);
}

#endif
